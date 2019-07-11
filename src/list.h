/**
 * \file list.h
 * \brief double linked list module
 * \author max <mpano91@gmail.com>
 *
 * double linked list container
 *
 * Created on Tue Jul 11 19:55:30 2019
 */

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ccl_list ccl_list_t;

typedef struct node iter_list_t;

ccl_linked_list_t *cclListInit(const size_t data_size);
int cclListCount(const ccl_list_t *dllist);
int cclListEmpty(const ccl_list_t *dllist);

iter_list_t *cclListGetIter(const ccl_list_t *dllist);
iter_list_t *cclListIterNext(iter_list_t *it);
void *cclListIterData(iter_list_t *it);

int cclListAddFirst(ccl_list_t *bllist, void *const data);
int cclListAddLast(ccl_list_t *bllist, void *const data);
int cclListAddAt(ccl_list_t *bllist, void *const data, const int idx);

int cclListGetFirst(ccl_list_t *bllist, void *const data);
int cclListGetLast(ccl_list_t *bllist, void *const data);
int cclListGetAt(ccl_list_t *bllist, const int idx, void *const data);

int cclListUpdateFirst(ccl_list_t *bllist, void *const data);
int cclListUpdateLast(ccl_list_t *bllist, void *const data);
int cclListUpdateAt(ccl_list_t *bllist, const int idx, void *const data);

int cclListRemoveFirst(ccl_list_t *bllist);
int cclListRemoveLast(ccl_list_t *bllist);
int cclListRemoveAt(ccl_list_t *bllist, const int idx);

void cclListClear(ccl_list_t *bllist);
void cclListDestroy(ccl_list_t *bllist);

void cclSortListAdd(ccl_list_t *bllist, void *data, int (*cmp)(const void *, const void *));
/*
void cclListConcat(ccl_list_t **, ccl_list_t *);
void cclSortListMerge(ccl_list_t **, ccl_list_t *, int (*)(void *, void *));
*/
#ifdef __cplusplus
}
#endif

#endif
