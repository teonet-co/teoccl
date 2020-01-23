/**
* \file lru_cache.c
* \author max
* Created on Tue Jan 21 18:27:55 2020
*/

#include "teoccl/algs/lru_cache.h"
#include "teoccl/queue.h"
#include "teoccl/map.h"

struct ccl_lru_cache {
    size_t cache_size;
    teoQueue *lru_que;
    teoMap *lru_hash;
};


typedef struct ccl_lru_hash {
    int capacity; 
    teoQueueData** array; 
} ccl_lru_hash_t;


ccl_lru_cache_t *cclLruInit(const size_t size)
{
    ccl_lru_cache_t *lru = malloc(sizeof(ccl_lru_cache_t));
    lru->cache_size = size;
    lru->lru_que = teoQueueNew();
    lru->lru_hash = teoMapNew(size, 1);

    return lru;
}

void refer(ccl_lru_cache_t *lru, int *x)
{
    if (teoMapGet(lru->lru_hash, x, sizeof(*x), NULL) == (void *)-1) {
        if (teoQueueSize(lru->lru_que) == lru->cache_size) {
            teoQueueData *last = teoQueueRemove(lru->lru_que, lru->lru_que->last);
            teoMapDelete(lru->lru_hash, last->data, last->data_length);
            free(last);
        }
    } else {
        void *data = teoMapGet(lru->lru_hash, x, sizeof(*x), NULL);
        teoQueueRemove(lru->lru_que, (teoQueueData *)data);
    }

    teoQueueAddTop(lru->lru_que, x, sizeof(*x));
    teoMapAdd(lru->lru_hash, x, sizeof(*x), lru->lru_que->first, sizeof(lru->lru_que->first));
}

void cclLruDestroy(ccl_lru_cache_t *lru)
{
    teoQueueDestroy(lru->lru_que);
    free(lru);
}

