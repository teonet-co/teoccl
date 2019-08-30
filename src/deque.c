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
    struct node block_item;
    int block_idx;
    int inner_idx;
    
    if (deq->start_idx == -1) {
        block_idx = -1;
        inner_idx = BLOCK_SIZE - 1; 
    } else {
        block_idx = deq->start_idx / BLOCK_SIZE;
        inner_idx = deq->start_idx % BLOCK_SIZE;
    }

    if (inner_idx == BLOCK_SIZE - 1) {
        struct node *block_iitem_ref;
        if (block_idx == -1) {
            const int old_block_count = deq->block_count;
            const int new_block_count = (int) (RESIZE_RATIO * me->block_count) + 1;
            const int added_blocks = new_block_count - old_block_count;

            deq->block = ccl_realloc(deq->block, new_block_count * sizeof(struct node));
            deq->block_count = new_block_count;

            memmove(&deq->block[added_blocks], deq->block, old_block_count * sizeof(struct node));
            block_idx = added_blocks - 1;
            deq->start_idx += added_blocks * BLOCK_SIZE;
            deq->end_idx += added_blocks * BLOCK_SIZE;

            int i;// TODO: need func for init new blocks
            for (i = 0; i < added_blocks; ++i) {
                struct node *const block_copy = &deq->block[i];
                block_copy->data = NULL;
            }
        }

        block_ref = &deq->block[block_idx];
        if (!block_ref->data) {
            block_ref->data = ccl_malloc(deq->data_size * BLOCK_SIZE);
        }

    }

    block_item = deq->block[block_idx];
    memcpy((char *)block_item.data + inner_idx * deq->data_size,
            data, deq->data_size);
    --(deq->start_idx);
    return 0;
}

int cclDequePushBack(ccl_deque *deq, void *const data)
{
}

