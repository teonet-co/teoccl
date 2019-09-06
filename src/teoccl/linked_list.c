#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "teoccl/memory.h"
#include "teoccl/linked_list.h"

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

void cclLinkedListClear(ccl_linked_list_t *llist)
{
    struct node *it = llist->head;
    while (it) {
        struct node *temp = it;
        it = it->next;
        free(temp->data);
        free(temp);
    }

    llist->head = NULL;
    llist->count = 0;
}

void cclLinkedListDestroy(ccl_linked_list_t *llist)
{
    cclLinkedListClear(llist);
    free(llist);
}

int cclLinkedListCount(const ccl_linked_list_t *llist)
{
    return llist->count;
}

int cclLinkedListEmpty(const ccl_linked_list_t *llist)
{
    return cclLinkedListCount(llist) == 0;
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

iter_llist_t *cclLinkedListGetIter(ccl_linked_list_t *llist)
{
    return cclLinkedListGetNodeAt(llist, 0);
}

iter_llist_t *cclLinkedListIterNext(iter_llist_t *it)
{
    return it->next;
}
void *cclLinkedListIterData(iter_llist_t *it)
{
    return it->data;
}

int cclLinkedListAddFirst(ccl_linked_list_t *llist, void *const data)
{
    return cclLinkedListAddAt(llist, data, 0);
}

int cclLinkedListAddLast(ccl_linked_list_t *llist, void *const data)
{
    return cclLinkedListAddAt(llist, data, llist->count);
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
    } else if (idx == llist->count ) {
        struct node *const temp = cclLinkedListGetNodeAt(llist, idx - 1);
        temp->next = item;
        llist->tail = item;
        item->next = NULL;
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

int cclLinkedListGetFirst(ccl_linked_list_t *llist, void *const data)
{
    return cclLinkedListGetAt(llist, 0, data);
}

int cclLinkedListGetLast(ccl_linked_list_t *llist, void *const data)
{
    return cclLinkedListGetAt(llist, llist->count - 1, data);
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

int cclLinkedListUpdateFirst(ccl_linked_list_t *llist, void *const data)
{
    return cclLinkedListUpdateAt(llist, 0, data);
}

int cclLinkedListUpdateLast(ccl_linked_list_t *llist, void *const data)
{
    return cclLinkedListUpdateAt(llist, llist->count - 1, data);
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

int cclLinkedListRemoveFirst(ccl_linked_list_t *llist)
{
    return cclLinkedListRemoveAt(llist, 0);
}

int cclLinkedListRemoveLast(ccl_linked_list_t *llist)
{
    return cclLinkedListRemoveAt(llist, llist->count - 1);
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

void cclSortLinkedListAdd(ccl_linked_list_t *llist, void *data, int (*cmp)(const void *, const void *))
{
    struct node const *it;
    int idx = 0;
    for (it = llist->head; it; it = it->next) {
        if (cmp(it->data, data) >= 0) {
            break;
        }
        ++idx;
    }
    cclLinkedListAddAt(llist, data, idx);
}


void cclLinkedListConcat(ccl_linked_list_t **f_list, ccl_linked_list_t *s_list)
{

    if (*f_list == NULL) {
        *f_list = s_list;
    } else {
        (*f_list)->tail->next = s_list->head;
        (*f_list)->tail = s_list->tail;
        (*f_list)->count += s_list->count;
    }
}


void cclSortLinkedListMerge(ccl_linked_list_t **f_list, ccl_linked_list_t *s_list, int (*cmp)(const void *, const void *))
{
}
