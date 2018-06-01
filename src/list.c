#include <stdlib.h>

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

teoArrayList *teoArrayListNew() {
    
    teoArrayList *tal;
    
    tal = (teoArrayList *)calloc(1, sizeof(teoArrayList));
    if (!tal) return NULL;

    tal->size = ARRA_LIST_DEFAULT_SIZE;
    tal->length = 0;
//    tal->free_fn = free_fn
    if (!(tal->array = (void **)calloc(sizeof(void *), tal->size))) {
        free(tal);
        return NULL;
    }

    return tal;
}

void teoArrayListFree(teoArrayList *tal) {
    
    size_t i;
//  for (i = 0; i < tal->length; i++)
//    if (tal->array[i]) tal->free_fn(tal->array[i]);
    free(tal->array);
    free(tal);
}

void *teoArrayListGetIdx(teoArrayList *tal, size_t i) {
    
    if (i >= arr->length) return NULL;
    return tal->array[i];
}

int teoArrayListPutIdx(teoArrayList *tal, size_t i, void *data) {

    
}

int teoArayListDelIdx(teoArrayList *tal, size_t idx, size_t count);

int teoArrayListAdd(teoArrayList *tal, void *data);

size_t teoArrayListLength(teoArrayList *tal);

void teoArrayListSort(teoArrayList *tal, int(*compar)(const void *, const void *));

void *teoArrayListBSearch(teoArrayList *tal, const void **key,
    int(*compar)(const void *, const void *));


