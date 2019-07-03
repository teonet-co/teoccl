#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "memory.h"
#include "linked_list.h"

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
};


ccl_linked_list_t *cclLinkedListInit(const size_t data_size)
{
    ccl_linked_list_t *init;

    if (!data_size) {
        return NULL;
    }

    init = ccl_malloc(sizeof(ccl_linked_list_t));
    init->head = NULL;
    init->tail = NULL;
    init->node_size = data_size;
    init->count = 0;

    return init;
}

int cclLinkedListCount(const ccl_linked_list_t *llist)
{
    return llist->count;
}

static int cclLinkedListIllegalInput(ccl_linked_list_t *llist, const int idx)
{
    return idx < 0 || idx >= llist->count;
}

static struct node *cclLinkedListGetNodeAt(ccl_linked_list_t *llist, const int idx)
{
    struct node *temp = llist->head;

    if ((idx == llist->count - 1) && (llist->tail)) {
        return llist->tail;
    }

    int i = 0;
    for (i = 0; i < idx; ++i) {
        temp = temp->next;
    }

    if (!temp->next) {
        llist->tail = temp;
    }

    return temp;
}


int cclLinkedListAddAt(ccl_linked_list_t *llist, void *const data, const int idx)
{
    struct node *item;

    if (idx < 0 || idx > llist->count) {
        return -1; // bad args
    }

    item = ccl_malloc(sizeof(struct node));
    item->data = ccl_malloc(llist->node_size);
    
    memcpy(item->data, data, llist->node_size);
    
    if (idx == 0) {
        item->next = llist->head;
        llist->head = item;
    } else {
        struct node *const temp = cclLinkedListGetNodeAt(llist, idx - 1);
        item->next = temp->next;
        temp->next = item;
        if (!item->next) {
            llist->tail = item;
        }
    }

    llist->count++;

    return 0;
}

int cclLinkedListGetAt(ccl_linked_list_t *llist, const int idx, void *const data)
{
    struct node *temp;
    if (cclLinkedListIllegalInput(llist, idx)) {
        return -1; // bad args
    }

    temp = cclLinkedListGetNodeAt(llist, idx);
    memcpy(data, temp->data, llist->node_size);
    return 0; // all good
}


int cclLinkedListUpdateAt(ccl_linked_list_t *llist, const int idx, void *const data)
{
    struct node *temp;
    if (cclLinkedListIllegalInput(llist, idx)) {
        return -1; // bad args
    }

    temp = cclLinkedListGetNodeAt(llist, idx);
    memcpy(temp->data, data, llist->node_size);
    return 0; // all good
}


int cclLinkedListRemoveAt(ccl_linked_list_t *llist, const int idx)
{
    if (cclLinkedListIllegalInput(llist, idx)) {
        return -1; // bad args
    }

    if (idx == 0) {
        struct node *temp_head = llist->head;
        llist->head = temp_head->next;
        free(temp_head->data);
        free(temp_head);
    } else {
        struct node *const temp = cclLinkedListGetNodeAt(llist, idx - 1);
        struct node *const backup = temp->next;
        temp->next = temp->next->next;
        if (!backup->next) {
            llist->tail = temp;
        }
        free(backup->data);
        free(backup);
    }

    llist->count--;
    return 0;
}


