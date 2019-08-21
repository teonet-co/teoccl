#include <stdlib.h>
//#include <limits.h>
//#include <string.h>

#include "memory.h"
#include "deque.h"


struct ccl_deque {
    struct node *block;
    size_t node_size;
    int block_count;
    int start_idx;
    int end_idx;
};

struct node {
    void *data;
};

static const int BLOCK_SIZE = 8;
static const double RESIZE_RATIO = 1.5;

ccl_deque_t *cclDequeInit(const size_t data_size)
{
    ccl_deque_t *init;
    struct node *block;

    if (!data_size) {
        return NULL;
    }
    
    init = ccl_malloc(sizeof(ccl_deque_t));
    init->node_size = data_size;
    init->start_idx = BLOCK_SIZE/2;
    init->end_idx = init->start_idx + 1;
    init->block_count = 1;
    init->block = ccl_malloc(sizeof(struct node));

    block = init->block;
    block->data = ccl_malloc(BLOCK_SIZE * init->data_size);

    return init;
}

int cclDequeSize(const ccl_deque_t *deq)
{
    return deq->end_idx - deq->start_idx - 1;
}

int cclDequeEmpty(const ccl_deque_t *deq)
{
    return cclDequeSize(deq) == 0;
}

int cclDequeTrim(ccl_deque_t *deq)
{
    return 1;
}

int cclDequePushFront(ccl_deque *deq, void *const data)
{
}

int cclDequePushBack(ccl_deque *deq, void *const data)
{
}

