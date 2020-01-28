/**
* \file lru_cache.c
* \author max
* Created on Tue Jan 21 18:27:55 2020
*/

#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ccl_lru_cache ccl_lru_cache_t;

ccl_lru_cache_t *cclLruInit(const size_t size);
void cclLruDestroy(ccl_lru_cache_t *lru);
void refer(ccl_lru_cache_t *lru, void *data, size_t data_len);
void display(ccl_lru_cache_t *lru, void (*dis)(const void *const data));

#ifdef __cplusplus
}
#endif

#endif
