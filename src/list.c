
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
}


int cclListCount(const ccl_list_t *dllist)
{
}


int cclListEmpty(const ccl_list_t *dllist)
{
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


int cclListAddFirst(ccl_list_t *bllist, void *const data)
{
}


int cclListAddLast(ccl_list_t *bllist, void *const data)
{
}


int cclListAddAt(ccl_list_t *bllist, void *const data, const int idx)
{
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

