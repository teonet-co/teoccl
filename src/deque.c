
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
    const int start_block =
       deq->start_idx == -1
        ? 0
        : deq->start_idx / BLOCK_SIZE;
    const int end_block =
       deq->end_idx == 0
        ? 0 
        : (deq->end_idx - 1) / BLOCK_SIZE;

    const int new_block_count = end_block - start_block + 1;

    void *const new_block = ccl_malloc(new_block_count * sizeof(struct node));
    
    int i;
    for (i = 0; i < start_block; i++) {
        const struct node block_item = deq->block[i];
        free(block_item.data);
    }
    
    for (i = end_block + 1; i < deq->block_count; i++) {
        const struct node block_item = deq->block[i];
        free(block_item.data);
    }

    memcpy(new_block, &deq->block[start_block],
           new_block_count * sizeof(struct node));
    free(deq->block);
    deq->block = new_block;
    deq->block_count = new_block_count;
    deq->start_index -= start_block * BLOCK_SIZE;
    deq->end_index -= start_block * BLOCK_SIZE;
    
    return 0;
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
        if (block_idx == -1) {
            const int old_block_count = deq->block_count;
            const int new_block_count = (int) (RESIZE_RATIO * deq->block_count) + 1;
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

        struct node *block_ref = &deq->block[block_idx];
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
    struct node block_item;
    const int block_idx = deq->end_idx / BLOCK_SIZE;
    const int inner_idx = deq->end_idx % BLOCK_SIZE;

    if (inner_idx == 0) {
        if (block_idx == deq->block_count) {
            const int new_block_count = (int) (RESIZE_RATIO * deq->block_count) + 1;
           
            deq->block = ccl_realloc(deq->block, new_block_count * sizeof(struct node));
            deq->block_count = new_block_count;

            int i;// TODO: need func for init new blocks
            for (i = block_idx; i < deq->block_count; ++i) {
                struct node *const block_copy = &deq->block[i];
                block_copy->data = NULL;
            }
        }

        struct node *block_ref = &deq->block[block_idx];
        if (!block_ref->data) {
            block_ref->data = ccl_malloc(deq->data_size * BLOCK_SIZE);
        }
    }

    block_item = deq->block[block_idx];
    memcpy((char *)block_item.data + inner_idx * deq->data_size,
            data, deq->data_size);
    ++(deq->end_idx);
    return 0;
}


int cclDequePopFront(ccl_deque_t *deq, void *const data)
{
    int block_idx;
    int inner_idx;
    struct node block_item;

    if (cclDequeEmpty(deq)) {
        return -1;
    }

    ++(deq->start_idx);
    block_idx = deq->start_idx / BLOCK_SIZE;
    inner_idx = deq->start_idx % BLOCK_SIZE;
    block_item = deq->block[block_idx];
    memcpy(data, (char *)block_item.data + inner_idx * deq->data_size,
            deq->data_size);
    return 0;
}


int cclDequePopBack(ccl_deque_t *deq, void *const data)
{
    int block_idx;
    int inner_idx;
    struct node block_item;

    if (cclDequeEmpty(deq)) {
        return -1;
    }

    --(deq->end_idx);
    block_idx = deq->end_idx / BLOCK_SIZE;
    inner_idx = deq->end_idx % BLOCK_SIZE;
    block_item = deq->block[block_idx];
    memcpy(data, (char *)block_item.data + inner_idx * deq->data_size,
            deq->data_size);
    return 0;
}


int cclDequeSetFirst(ccl_deque_t *deq, void *data)
{
    return cclDequeSetAt(deq, data, 0);
}


int cclDequeSetAt(ccl_deque_t *deq, int index, void *data)
{
    int block_idx;
    int inner_idx;
    struct node block_item;

    if ((idx < 0) || (idx >= cclDequeSize(deq))) {
        return -1;
    }

    idx += deq->start_idx + 1;
    block_idx = idx / BLOCK_SIZE;
    inner_idx = idx % BLOCK_SIZE;
    block_item = deq->block[block_idx];
    memcpy((char *)block_item.data + inner_idx * deq->data_size,
            data, deq->data_size);

    return 0; 
}


int cclDequeSetLast(ccl_deque_t *deq, void *data)
{
    return cclDequeGetAt(deq, data, cclDequeSize(deq) - 1);
}


int cclDequeGetFirst(ccl_deque_t *deq, void *data)
{
    return cclDequeGetAt(deq, data, 0);
}


int cclDequeGetAt(ccl_deque_t *deq, int idx, void *data)
{
    int block_idx;
    int inner_idx;
    struct node block_item;

    if ((idx < 0) || (idx >= cclDequeSize(deq))) {
        return -1;
    }

    idx += deq->start_idx + 1;
    block_idx = idx / BLOCK_SIZE;
    inner_idx = idx % BLOCK_SIZE;
    block_item = deq->block[block_idx];
    memcpy(data, (char *)block_item.data + inner_idx * deq->data_size,
            deq->data_size);

    return 0;
}


int cclDequeGetLast(ccl_deque_t *deq, void *data)
{
    return cclDequeGetAt(deq, data, cclDequeSize(deq) - 1);
}


int cclDequeClear(ccl_deque_t *deq)
{
    void *temp_block_data;
    int i;
    struct node *block;
    struct node *const temp_block = malloc(sizeof(struct node));
    if (!temp_block) {
        return -ENOMEM;
    }
    temp_block_data = malloc(BLOCK_SIZE * deq->data_size);
    if (!temp_block_data) {
        free(temp_block);
        return -ENOMEM;
    }
    for (i = 0; i < deq->block_count; i++) {
        const struct node block_item = deq->block[i];
        free(block_item.data);
    }
    free(deq->block);
    deq->start_index = BLOCK_SIZE / 2;
    deq->end_index = deq->start_index + 1;
    deq->block_count = 1;
    deq->block = temp_block;
    block = deq->block;
    block->data = temp_block_data;
}


void cclDequeDestroy(ccl_deque_t *deq)
{
    int i;
    for (i = 0; i < deq->block_count; ++i) {
        const struct node block_item = deq->block[i];
        free(block_item.data);
    }

    free(deq->block);
    free(deq);
}

