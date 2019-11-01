/**
 * \file stack.h
 * \brief 
 * \author max <mpano91@gmail.com>
 *
 * 
 *
 * Created on Sut Sep 4 19:55:30 2019
 */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ccl_stack ccl_stack_t;

ccl_stack_t *cclStackInit(size_t data_size);

int cclStackSize(ccl_stack_t *s);
int cclStackEmpty(ccl_stack_t *s);
int cclStackTrim(ccl_stack_t *s);

int cclStackPush(ccl_stack_t *s, void *const data);

int cclStackPop(ccl_stack_t *s, void *data);

int cclStackTop(ccl_stack_t *s, void *data);

int cclStackClear(ccl_stack_t *s);
void cclStackDestroy(ccl_stack_t *s);

#ifdef __cplusplus
}
#endif

#endif
