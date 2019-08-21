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
int cclDequeTrim(ccl_deque_t *deq);

int cclDequePushFront(ccl_deque *deq, void *const data);
int cclDequePushBack(ccl_deque *deq, void *const data);
#ifdef __cplusplus
}
#endif

#endif
