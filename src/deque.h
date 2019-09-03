/**
 * \file deque.h
 * \brief 
 * \author max <mpano91@gmail.com>
 *
 * deque container
 *
 * Created on Tue Jul 11 19:55:30 2019
 */

#ifndef DEQUE_H
#define DEQUE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ccl_deque ccl_deque_t;

//typedef struct node iter_list_t;

ccl_deque_t *cclDequeInit(const size_t data_size);
int cclDequeSize(ccl_deque_t *deq);
int cclDequeEmpty(const ccl_deque_t *deq);
int cclDequeTrim(ccl_deque_t *deq);

int cclDequePushFront(ccl_deque_t *deq, void *const data);
int cclDequePushBack(ccl_deque_t *deq, void *const data);

int cclDequePopFront(ccl_deque_t *deq, void *const data);
int cclDequePopBack(ccl_deque_t *deq, void *const data);

int cclDequeSetFirst(ccl_deque_t *deq, void *const data);
int cclDequeSetAt(ccl_deque_t *deq, int index, void *const data);
int cclDequeSetLast(ccl_deque_t *deq, void *const data);

int cclDequeGetFirst(ccl_deque_t *deq, void *data);
int cclDequeGetAt(ccl_deque_t *deq, int idx, void *data);
int cclDequeGetLast(ccl_deque_t *deq, void *data);

int cclDequeClear(ccl_deque_t *deq);
void cclDequeDestroy(ccl_deque_t *deq);
#ifdef __cplusplus
}
#endif

#endif
