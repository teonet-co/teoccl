#include "memory.h"
#include "deque.h"
#include "stack.h"

struct ccl_stack {
    ccl_deque_t deq;
};


ccl_stack_t cclStackInit(size_t data_size)
{
    ccl_stack_t *init;
    if (data_size == 0) {
        return NULL;
    }

    init = ccl_malloc(sizeof(struct ccl_stack_t));

    init->deq = cclDequeInit(data_size);
    if (!init->deq) {
        free(init);
        return NULL;
    }

    return init;
}


int cclStackSize(ccl_stack_t *s)
{
    return cclDequeSize(s->deq);
}


int cclStackEmpty(ccl_stack_t *s)
{
    return cclDequeEmpty(s->deq);
}


int cclStackTrim(ccl_stack_t *s)
{
    return cclDequeTrim(s->deq);
}


int cclStackPush(ccl_stack_t *s, void *const data)
{
    return cclDequePushBack(s->deq, data);
}


int cclStackPop(ccl_stack_t *s, void *data)
{
    return cclDequePopBack(s->deq, data) == 0;
}


int cclStackTop(ccl_stack_t *s, void *data)
{
    return cclDequeGetLast(s->deq, data) == 0;
}


int cclStackClear(ccl_stack_t *s)
{
    return cclDequeClear(s->deq);
}


void cclStackDestroy(ccl_stack_t *s)
{
    cclDequeDestroy(s->deq);
    free(s);
}
