/**
 * \file linked_list.h
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

typedef struct node iter_llist_t;

ccl_linked_list_t *cclLinkedListInit(const size_t data_size);
int cclLinkedListCount(const ccl_linked_list_t *llist);
int cclLinkedListEmpty(const ccl_linked_list_t *llist);

iter_llist_t *cclLinkedListGetIter(const ccl_linked_list_t *llist);
iter_llist_t *cclLinkedListIterNext(iter_llist_t *it);
void *cclLinkedListIterData(iter_llist_t *it);

int cclLinkedListAddFirst(ccl_linked_list_t *llist, void *const data);
int cclLinkedListAddLast(ccl_linked_list_t *llist, void *const data);
int cclLinkedListAddAt(ccl_linked_list_t *llist, void *const data, const int idx);

int cclLinkedListGetFirst(ccl_linked_list_t *llist, void *const data);
int cclLinkedListGetLast(ccl_linked_list_t *llist, void *const data);
int cclLinkedListGetAt(ccl_linked_list_t *llist, const int idx, void *const data);

int cclLinkedListUpdateFirst(ccl_linked_list_t *llist, void *const data);
int cclLinkedListUpdateLast(ccl_linked_list_t *llist, void *const data);
int cclLinkedListUpdateAt(ccl_linked_list_t *llist, const int idx, void *const data);

int cclLinkedListRemoveFirst(ccl_linked_list_t *llist);
int cclLinkedListRemoveLast(ccl_linked_list_t *llist);
int cclLinkedListRemoveAt(ccl_linked_list_t *llist, const int idx);

void cclLinkedListClear(ccl_linked_list_t *llist);
void cclLinkedListDestroy(ccl_linked_list_t *llist);

void cclSortLinkedListAdd(ccl_linked_list_t *, void *, int (*)(const void *, const void *));
/*
void cclLinkedListConcat(ccl_linked_list_t **, ccl_linked_list_t *);
void cclSortLinkedListMerge(ccl_linked_list_t **, ccl_linked_list_t *, int (*)(void *, void *));

*/
#ifdef __cplusplus
}
#endif

#endif
