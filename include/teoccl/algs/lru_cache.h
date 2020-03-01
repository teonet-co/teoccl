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
void cclLruRefer(ccl_lru_cache_t *lru, void *data, size_t data_len);
void cclLruForeach(ccl_lru_cache_t *lru, void (*fn)(const void *const data));

#ifdef __cplusplus
}
#endif

#endif
