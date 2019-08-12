#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "teoccl/array_list.h"

#ifndef SIZE_T_MAX
  #if SIZEOF_SIZE_T == SIZEOF_INT
    #define SIZE_T_MAX UINT_MAX
  #elif SIZEOF_SIZE_T == SIZEOF_LONG
    #define SIZE_T_MAX ULONG_MAX
  #elif SIZEOF_SIZE_T == SIZEOF_LONG_LONG
    #define SIZE_T_MAX ULLONG_MAX
  #else
    #error Unable to determine size of size_t
  #endif
#endif

#define TEO_FREE( ptr ) if( ptr ){ free( ptr ); ptr = 0; }


ccl_array_list_t *cclArrayListNew(array_list_free_fn *free_fn)
{
    ccl_array_list_t *tal = (ccl_array_list_t *)calloc(1, sizeof(ccl_array_list_t));
    if (!tal) {
        return NULL;
    }

    tal->size = ARRAY_LIST_DEFAULT_SIZE;
    tal->length = 0;
    tal->free_fn = free_fn;

    if (!(tal->array = (void **)calloc(sizeof(void *), tal->size))) {
        free(tal);
        return NULL;
    }

    return tal;
}


int cclArrayListFree(ccl_array_list_t *tal)
{
    if (tal->free_fn) {
        int i = 0;
        for (i = 0; i < tal->length; ++i) {
            if (tal->array[i]) tal->free_fn(tal->array[i]);
        }
    }

    TEO_FREE(tal->array);
    TEO_FREE(tal);

    return 0;
}


void *cclArrayListGetIdx(ccl_array_list_t *tal, size_t i)
{
    if (i >= tal->length) {
        return NULL;
    }

    return tal->array[i];
}


static
int array_list_expand_internal(ccl_array_list_t *tal, size_t max)
{
    void *t = NULL;
    size_t new_size;

    if (max < tal->size) return 0;
    /* Avoid undefined behaviour on size_t overflow */
    if (tal->size >= SIZE_T_MAX / 2) {
        new_size = max;
    } else {
        new_size = tal->size << 1;
        if (new_size < max) {
            new_size = max;
        }
    }

    if (new_size > (~((size_t)0)) / sizeof(void*)) return -1;
    if (!(t = realloc(tal->array, new_size*sizeof(void*)))) return -1;
    tal->array = (void**)t;
    (void)memset(tal->array + tal->size, 0, (new_size - tal->size)*sizeof(void*));
    tal->size = new_size;

    return 0;
}

static
int cclArrayListPutIdx(ccl_array_list_t *tal, size_t i, void *data)
{
    if ((i > SIZE_T_MAX -1 ) || (array_list_expand_internal(tal, i+1))) {
        return -1;
    }

    if (i < tal->length && tal->array[i]) {
        tal->free_fn(tal->array[i]);
    }

    tal->array[i] = data;
    if (tal->length <= i) {
        tal->length = i + 1;
    }
  return 0;
}


int cclArrayListDelIdx(ccl_array_list_t *tal, size_t i, size_t count)
{
    size_t stop = count + i;
    if (i >= tal->length || stop > tal->length) {
        return -1;
    }

    size_t j = 0;
    for (j = i; j < stop; ++j) {
        if (tal->array[j]) {
            if (tal->free_fn) {
                tal->free_fn(tal->array[j]);
            } else {
                tal->array[j] = NULL;
            }
        }
    }

    memmove(tal->array + i, tal->array + stop, (tal->length - stop) * sizeof(void *));
    tal->length -= count;
    return 0;
}


int cclArrayListAdd(ccl_array_list_t *tal, void *data)
{
    return cclArrayListPutIdx(tal, tal->length, data);
}


size_t cclArrayListLength(ccl_array_list_t *tal)
{
    return tal->length;
}


void cclArrayListSort(ccl_array_list_t *tal, int(*compar)(const void *, const void *))
{
    qsort(tal->array, tal->length, sizeof(tal->array[0]), compar);
}


void *cclArrayListBSearch(ccl_array_list_t *tal, const void **key,
    int(*compar)(const void *, const void *))
{
    return bsearch(key, tal->array, tal->length, sizeof(tal->array[0]), compar);
}
