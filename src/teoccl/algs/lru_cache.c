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


ccl_lru_cache_t *cclLruInit(const size_t size)
{
    ccl_lru_cache_t *lru = malloc(sizeof(ccl_lru_cache_t));
    lru->cache_size = size;
    lru->lru_que = teoQueueNew();
    lru->lru_hash = teoMapNew(size, 1);

    return lru;
}

void cclLruRefer(ccl_lru_cache_t *lru, void *data, size_t data_len)
{
    if (teoMapGet(lru->lru_hash, data, data_len, NULL) == (void *)-1) {
        if (teoQueueSize(lru->lru_que) == lru->cache_size) {
            teoQueueData *last = teoQueueRemove(lru->lru_que, lru->lru_que->last);
            teoMapDelete(lru->lru_hash, last->data, last->data_length);
            free(last);
        }
    } else {
        void *d = teoMapGet(lru->lru_hash, data, data_len, NULL);
        teoQueueRemove(lru->lru_que, *(teoQueueData **)d);
    }

    teoQueueAddTop(lru->lru_que, data, data_len);
    teoMapAdd(lru->lru_hash, data, data_len, (uint8_t*)&lru->lru_que->first, sizeof(lru->lru_que->first));
}

void cclLruForeach(ccl_lru_cache_t *lru, void (*fn)(const void *const data))
{
    teoQueueIterator it;
    teoQueueIteratorReset(&it, lru->lru_que);

    while(teoQueueIteratorNext(&it)) {
        teoQueueData *qd = teoQueueIteratorElement(&it);
        fn(qd->data);
    }
}

void cclLruDestroy(ccl_lru_cache_t *lru)
{
    teoQueueDestroy(lru->lru_que);
    free(lru);
}

