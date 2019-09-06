/**
 * \file que.h
 * \brief 
 * \author max <mpano91@gmail.com>
 *
 * 
 *
 * Created on Tue Jul 11 19:55:30 2019
 */

#ifndef QUE_H
#define QUE_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ccl_queue ccl_queue_t;

ccl_queue_t *cclQueInit(const size_t data_size);

int cclQueSize(ccl_queue_t *que);
int cclQueEmpty(ccl_queue_t *que);
int cclQueTrim(ccl_queue_t *que);

int cclQuePush(ccl_queue_t *que, void *const data);
int cclQuePop(ccl_queue_t *que, void *const data);

int cclQueFront(ccl_queue_t *que, void *data);
int cclQueBack(ccl_queue_t *que, void *data);

int cclQueClear(ccl_queue_t *que);
void cclQueDestroy(ccl_queue_t *que);

#ifdef __cplusplus
}
#endif

#endif
