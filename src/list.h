/**
* \file list.h
* \author max <mpano91@gmail.com> 
*
*
* Created on Fri Jun  1 17:01:30 2018
*/

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_LIST_DEFAULT_SIZE 32


typedef void (array_list_free_fn) (void *data);

typedef struct teoArrayList {

    void **array;
    size_t length;
    size_t size;
    array_list_free_fn *free_fn;

} teoArrayList;

teoArrayList *teoArrayListNew(array_list_free_fn *free_fn);
int teoArrayListFree(teoArrayList *tal);

void *teoArrayListGetIdx(teoArrayList *tal, size_t i);
int teoArrayListPutIdx(teoArrayList *tal, size_t i, void *data, size_t data_len);
int teoArrayListDelIdx(teoArrayList *tal, size_t idx, size_t count);
int teoArrayListAdd(teoArrayList *tal, void *data, size_t data_len);
size_t teoArrayListLength(teoArrayList *tal);

void teoArrayListSort(teoArrayList *tal, int(*compar)(const void *, const void *));
void *teoArrayListBSearch(teoArrayList *tal, const void **key,
    int(*compar)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif
