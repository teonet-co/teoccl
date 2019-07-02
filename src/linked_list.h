/**
 * \file list.h
 * \brief linked-list module
 * \author max <mpano91@gmail.com>
 *
 * linked-list container
 *
 * Created on Tue Jul 2 13:48:30 2019
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ccl_linked_list ccl_linked_list_t;

ccl_linked_list_t *cclLinkedListInit(const size_t data_size);


int cclLinkedListAddAt(ccl_linked_list_t *llist, void *const data, const int idx);
int cclLinkedListGetAt(ccl_linked_list_t *llist, const int idx, void *const data);
int cclLinkedListUpdateAt(ccl_linked_list_t *llist, const int idx, void *const data);
int cclLinkedListRemoveAt(ccl_linked_list_t *llist, const int idx);

/*
void cclSortLinkedListAdd(ccl_linked_list_t **, void *, int (*)(void *, void *));

void *cclLinkedListRemove(ccl_linked_list_t **, void *, int (*)(void *, void *, void *), void *);

void cclLinkedListFree(ccl_linked_list_t *, void (*)(void *, void *), void *);

void *cclLinkedListFind(ccl_linked_list_t *, void *, int (*)(void *, void *));
void *cclLinkedListFirst(ccl_linked_list_t *);

int cclLinkedListIter(ccl_linked_list_t *, int (*)(void *, void *), void *);
int cclLinkedListCount(ccl_linked_list_t *);
int cclLinkedListEmpty(ccl_linked_list_t *);

void cclLinkedListConcat(ccl_linked_list_t **, ccl_linked_list_t *);
void cclSortLinkedListMerge(ccl_linked_list_t **, ccl_linked_list_t *, int (*)(void *, void *));
*/
#ifdef __cplusplus
}
#endif

#endif
