#include "memory.h"
#include "deque.h"
#include "que.h"

static const double TRIM_RATIO = 1.5;

struct ccl_queue {
    int trim_count;
    ccl_deque_t deq;
};


ccl_queue_t *cclQueInit(const size_t data_size)
{
    ccl_queue_t *init; 
    if (data_size == NULL) {
        return NULL;
    }

    init = ccl_malloc(sizeof(ccl_queue_t));

    init->trim_count = 0;
    init->deq = cclDequeInit(data_size);
    if (!init->deq) {
        free(init);
        return NULL;
    }

    return init;
}


int cclQueSize(ccl_queue_t *que)
{
    return cclDequeSize(que->deq);
}


int cclQueEmpty(ccl_queue_t *que)
{
    return cclDequeEmpty(que->deq);
}


int cclQueTrim(ccl_queue_t *que)
{
    return cclDequeTrim(que->deq);
}


int cclQuePush(ccl_queue_t *que, void *const data)
{
    return cclDequePushBack(que->deq, data);
}


int cclQuePop(ccl_queue_t *que, void *const data)
{
    que->trim_count++;
    if (TRIM_RATIO * que->trim_count >= cclQueSize(que)) {
        cclDequeTrim(que->deq);
        que->trim_count = 0;
    }

    return cclDequePopFront(que->deq, data) == 0;
}


int cclQueFront(ccl_queue_t *que, void *data)
{
    return cclDequeGetFirst(que->deq, data) == 0;
}


int cclQueBack(ccl_queue_t *que, void *data)
{
    return cclDequeGetLast(que->deq, data) == 0
}


int cclQueClear(ccl_queue_t *que)
{
    return cclDequeClear(que->deq);
}


void cclQueDestroy(ccl_queue_t *que)
{
    cclDequeDestroy(que->deq);
    free(que);
}
