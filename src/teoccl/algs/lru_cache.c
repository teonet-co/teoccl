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

void refer(ccl_lru_cache_t *lru, void *data, size_t data_len)
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
    teoMapAdd(lru->lru_hash, data, data_len, &lru->lru_que->first, sizeof(lru->lru_que->first));
}

void display(ccl_lru_cache_t *lru, void (*dis)(const void *const data))
{
    printf("\nLLRU SIZE = %ld\n", teoQueueSize(lru->lru_que));
/*
    printf("1) %d\n", *(int *)lru->lru_que->first->data); 
    printf("2) %d\n", *(int *)lru->lru_que->first->next->data); 
    printf("3) %d\n", *(int *)lru->lru_que->first->next->next->data); 
    printf("4) %d\n", *(int *)lru->lru_que->first->next->next->next->data);
*/
    teoQueueIterator it;
    teoQueueData *qd;
    teoQueueIteratorReset(&it, lru->lru_que);

    while(teoQueueIteratorNext(&it)) {
        qd = teoQueueIteratorElement(&it);
        dis(qd->data);
    }
/*
    printf("1) %s\n", (char *)lru->lru_que->first->data); 
    printf("2) %s\n", (char *)lru->lru_que->first->next->data); 
    printf("3) %s\n", (char *)lru->lru_que->first->next->next->data); 
    printf("4) %s\n", (char *)lru->lru_que->first->next->next->next->data);
*/    
}

void cclLruDestroy(ccl_lru_cache_t *lru)
{
    teoQueueDestroy(lru->lru_que);
    free(lru);
}

