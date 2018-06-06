#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "list.h"

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

teoArrayList *teoArrayListNew(array_list_free_fn *free_fn) {
    
    teoArrayList *tal;
    
    tal = (teoArrayList *)calloc(1, sizeof(teoArrayList));
    if (!tal) return NULL;

    tal->size = ARRAY_LIST_DEFAULT_SIZE;
    tal->length = 0;
    tal->free_fn = free_fn;
    if (!(tal->array = (void **)calloc(sizeof(void *), tal->size))) {
        free(tal);
        return NULL;
    }

    return tal;
}


int teoArrayListFree(teoArrayList *tal) {
    
    if (tal->free_fn) {
        size_t i;
        for (i = 0; i < tal->length; i++) {
            if (tal->array[i]) tal->free_fn(tal->array[i]);
        }
    }
    TEO_FREE(tal->array);
    TEO_FREE(tal);

    return 0;
}


void *teoArrayListGetIdx(teoArrayList *tal, size_t i) {
    
    if (i >= tal->length) return NULL;
    return tal->array[i];
}


static
int array_list_expand_internal(teoArrayList *tal, size_t max) {
  
    void *t;
    size_t new_size;

    if(max < tal->size) return 0;
    /* Avoid undefined behaviour on size_t overflow */
    if(tal->size >= SIZE_T_MAX / 2)
        new_size = max;
    else {
        new_size = tal->size << 1;
        if (new_size < max) new_size = max;
    }
    
    if (new_size > (~((size_t)0)) / sizeof(void*)) return -1;
    if (!(t = realloc(tal->array, new_size*sizeof(void*)))) return -1;
    tal->array = (void**)t;
    (void)memset(tal->array + tal->size, 0, (new_size - tal->size)*sizeof(void*));
    tal->size = new_size;
    
    return 0;
}

static
int teoArrayListPutIdx(teoArrayList *tal, size_t i, void *data/*, size_t data_len*/) {
    
//    void *cp_data = NULL;
//    cp_data = malloc(data_len);
//    if (!cp_data) return -1;
//    memcpy(cp_data, data, data_len);
    if (i > SIZE_T_MAX -1 ) return -1;
    if(array_list_expand_internal(tal, i+1)) return -1;
    if(i < tal->length && tal->array[i])
        tal->free_fn(tal->array[i]);
    tal->array[i] = data;//cp_data;
    if(tal->length <= i) tal->length = i + 1;
  return 0;
}


int teoArrayListDelIdx(teoArrayList *tal, size_t i, size_t count) {

    size_t j, stop;

    stop = count+i;
    if (i >= tal->length || stop > tal->length) return -1;
    for (j = i; j < stop; ++j) {
        if (tal->array[j]) {
            if (tal->free_fn)
                tal->free_fn(tal->array[j]);
            else
                tal->array[j] = NULL;
        }
    }

    memmove(tal->array + i, tal->array + stop, (tal->length - stop) * sizeof(void *));
    tal->length -= count;
    return 0;
}


int teoArrayListAdd(teoArrayList *tal, void *data/*, size_t data_len*/) {

    return teoArrayListPutIdx(tal, tal->length, data/*, data_len*/);
}


size_t teoArrayListLength(teoArrayList *tal) {

    return tal->length;
}


void teoArrayListSort(teoArrayList *tal, int(*compar)(const void *, const void *)) {

    qsort(tal->array, tal->length, sizeof(tal->array[0]), compar);
}


void *teoArrayListBSearch(teoArrayList *tal, const void **key,
    int(*compar)(const void *, const void *)) {

    return bsearch(key, tal->array, tal->length, sizeof(tal->array[0]), compar);
}
