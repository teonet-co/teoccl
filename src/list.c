
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "memory.h"
#include "list.h"

#ifndef SIZE_T_MAX
  #if SIZEOF_SIZE_T == SIZEOF_INT
    #define SIZE_T_MAX UINT_MAX
  #elif SIZEOF_SIZE_T == SIZEOF_LONG
    #define SIZE_T_MAX ULONG_MAX
  #elif SIZEOF_SIZE_T == SIZEOF_LONG_LONG
    #define SIZE_T_MAX ULLONG_MAX
  #else
    #error Unable to determine size of size_t
  #endif
#endif

struct ccl_linked_list {
    struct node *head;
    struct node *tail;
    size_t node_size;
    int count;
};

struct node {
    void *data;
    struct node *next;
    struct node *prev;
};


ccl_linked_list_t *cclListInit(const size_t data_size)
{
    ccl_list_t *init;

    if (!data_size) {
        return NULL;
    }

    init = ccl_malloc(sizeof(ccl_list_t));
    init->head = NULL;
    init->tail = NULL;
    init->node_size = data_size;
    init->count = 0;

    return init;
}


int cclListCount(const ccl_list_t *dllist)
{
    return dllist->count;
}


int cclListEmpty(const ccl_list_t *dllist)
{
    return cclListCount(dllist) == 0;
}


iter_list_t *cclListGetIter(const ccl_list_t *dllist)
{
}


iter_list_t *cclListIterNext(iter_list_t *it)
{
}


void *cclListIterData(iter_list_t *it)
{
}

static struct node *cclListGetNodeFromHead(ccl_list_t *bllist, const int idx)
{
    struct node *temp = bllist->head;
    int i = 0;
    for (i = 0; i < idx; ++i) {
        temp = temp->next;
    }

    return temp;
}

static struct node *cclListGetNodeFromTail(ccl_list_t *bllist, const int idx)
{
    struct node *temp = bllist->tail;
    int i = 0;
    for (i = bllist->count - 1; i > idx; --i) {
        temp = temp->prev;
    }

    return temp;

}

static struct node *cclListGetNodeAt(ccl_list_t *bllist, const int idx)
{
    if (idx < (cclListCount(bllist) / 2)) {
        return cclListGetNodeFromHead(bllist, idx);
    }

    return cclListGetNodeFromTail(bllist, idx);
}

int cclListAddFirst(ccl_list_t *bllist, void *const data)
{
    return cclListAddAt(bllist, data, 0);
}


int cclListAddLast(ccl_list_t *bllist, void *const data)
{
    return cclListAddAt(bllist, data, bllist->count);
}


int cclListAddAt(ccl_list_t *bllist, void *const data, const int idx)
{
    if (idx < 0 || idx > bllist->count) {
        return -1; //bad args
    }

    struct node *item = ccl_malloc(sizeof(struct node));
    item->data = ccl_malloc(bllist->node_size);

    memcpy(item->data, data, bllist->node_size);

    if (!bllist->head) {
        item->next = NULL;
        item->prev = NULL;
        bllist->head = item;
        bllist->tail = item;
    } else if (idx == 0) {
        struct node *const temp = bllist->head;
        temp->prev = item;
        item->next = temp;
        item->prev = NULL;
        bllist->head = item;
    } else if (idx == bllist->count) {
        struct node *const temp = bllist->tail;
        temp-next = item;
        item->prev = temp;
        item->next = NULL;
        bllist->tail = item;
    } else {
        struct node *const temp = cclListGetNodeAt(bllist, idx);
        item->prev = temp->prev;
        item->next = temp;
        temp->prev->next = item;
        temp->prev = item;
    }

    ++(bllist->count);

    return 0;//all good
}


int cclListGetFirst(ccl_list_t *bllist, void *const data)
{
}


int cclListGetLast(ccl_list_t *bllist, void *const data)
{
}


int cclListGetAt(ccl_list_t *bllist, const int idx, void *const data)
{
}


int cclListUpdateFirst(ccl_list_t *bllist, void *const data)
{
}


int cclListUpdateLast(ccl_list_t *bllist, void *const data)
{
}


int cclListUpdateAt(ccl_list_t *bllist, const int idx, void *const data)
{
}


int cclListRemoveFirst(ccl_list_t *bllist)
{
}


int cclListRemoveLast(ccl_list_t *bllist)
{
}


int cclListRemoveAt(ccl_list_t *bllist, const int idx)
{
}


void cclListClear(ccl_list_t *bllist)
{
}


void cclListDestroy(ccl_list_t *bllist)
{
}


void cclSortListAdd(ccl_list_t *bllist, void *data, int (*cmp)(const void *, const void *))
{
}

