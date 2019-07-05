/*
 * File:   map_t.c
 * Author: Kirill Scherba <kirill@scherba.ru>
 *
 * Created on Jun 5, 2016, 4:32:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "linked_list.h"

int init_suite(void);
int clean_suite(void);

static long long timeInMilliseconds(void)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}


void check_add_and_size()
{
    ccl_linked_list_t *linked_list = cclLinkedListInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL(linked_list);
    int i = 0;
    int result = 0;
    int size_list = 10;
    for (i = 0; i < size_list; ++i) {
        result = cclLinkedListAddAt(linked_list, &i, i);
        CU_ASSERT_EQUAL(result, 0);
    }
    int count = cclLinkedListCount(linked_list);
    CU_ASSERT_EQUAL(count, size_list);
    int head = 0;
    int tail = 0;
    result = cclLinkedListGetAt(linked_list, 0, &head);
    CU_ASSERT_EQUAL(result, 0);
    result = cclLinkedListGetAt(linked_list, count - 1, &tail);
    CU_ASSERT_EQUAL(result, 0);
    cclLinkedListClear(linked_list);
    count = cclLinkedListCount(linked_list);
    CU_ASSERT_EQUAL(count, 0);
    cclLinkedListDestroy(linked_list);
}

void check_add_get_first_last()
{
    ccl_linked_list_t *linked_list = cclLinkedListInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL(linked_list);
    int i = 0;
    int result = 0;
    int size_list = 10;
    for (i = 0; i < size_list; ++i) {
        result = cclLinkedListAddAt(linked_list, &i, i);
        CU_ASSERT_EQUAL(result, 0);
    }
    int count = cclLinkedListCount(linked_list);
    CU_ASSERT_EQUAL(count, size_list);
    
    int head = 0;
    int tail = 0;
    int first = 228;
    int last = 666;

    result = cclLinkedListAddFirst(linked_list, &first);
    CU_ASSERT_EQUAL(result, 0);

    result = cclLinkedListAddLast(linked_list, &last);
    CU_ASSERT_EQUAL(result, 0);

    result = cclLinkedListGetFirst(linked_list, &head);
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_EQUAL(head, first);

    result = cclLinkedListGetLast(linked_list, &tail);

    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_EQUAL(tail, last);

    printf("\nLinked list: ");
    for (i = 0; i < cclLinkedListCount(linked_list); ++i) {
        int j = 0;
        result = cclLinkedListGetAt(linked_list, i, &j);
        printf("%d ", j);
    }
    printf("\n");
}

void check_update_remove()
{
    ccl_linked_list_t *linked_list = cclLinkedListInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL(linked_list);
    int i = 0;
    int result = 0;
    int size_list = 10;
    for (i = 0; i < size_list; ++i) {
        result = cclLinkedListAddAt(linked_list, &i, i);
        CU_ASSERT_EQUAL(result, 0);
    }
    int count = cclLinkedListCount(linked_list);
    CU_ASSERT_EQUAL(count, size_list);
    
    int head = 0;
    int tail = 0;
    int first = 228;
    int last = 666;
    result = cclLinkedListUpdateFirst(linked_list, &first);
    CU_ASSERT_EQUAL(result, 0);

    result = cclLinkedListUpdateAt(linked_list, 7, &last);
    CU_ASSERT_EQUAL(result, 0);

    result = cclLinkedListUpdateLast(linked_list, &last);
    CU_ASSERT_EQUAL(result, 0);

    result = cclLinkedListGetFirst(linked_list, &head);
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_EQUAL(head, first);

    result = cclLinkedListGetLast(linked_list, &tail);
    CU_ASSERT_EQUAL(result, 0);
    CU_ASSERT_EQUAL(tail, last);

    printf("\nLinked list: ");
    for (i = 0; i < cclLinkedListCount(linked_list); ++i) {
        int j = 0;
        result = cclLinkedListGetAt(linked_list, i, &j);
        printf("%d ", j);
    }

    result = cclLinkedListRemoveFirst(linked_list);
    CU_ASSERT_EQUAL(result, 0);

    result = cclLinkedListRemoveAt(linked_list, 5);
    CU_ASSERT_EQUAL(result, 0);

    result = cclLinkedListRemoveLast(linked_list);
    CU_ASSERT_EQUAL(result, 0);
    printf("\nLinked list: ");
    for (i = 0; i < cclLinkedListCount(linked_list); ++i) {
        int j = 0;
        result = cclLinkedListGetAt(linked_list, i, &j);
        printf("%d ", j);
    }

    printf("\n");
}

int cmp_int(const void *a, const void *b)
{
     return *(int*)a - *(int*)b;
}

void check_add_to_sort()
{
    srand(time(NULL));

    ccl_linked_list_t *linked_list = cclLinkedListInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL(linked_list);
    int i = 0;
    int result = 0;
    int size_list = 10;
    for (i = 0; i < size_list; ++i) {
        result = cclLinkedListAddAt(linked_list, &i, i);
        CU_ASSERT_EQUAL(result, 0);
    }
    int count = cclLinkedListCount(linked_list);
    CU_ASSERT_EQUAL(count, size_list);

    printf("\nLinked list(it): ");
    iter_llist_t *it = cclLinkedListGetIter(linked_list);
    while (it) {
        int *data = (int *)cclLinkedListIterData(it);
        printf("%d ", *data);
        it = cclLinkedListIterNext(it);
    }
    printf("\n");

    for (i = 0; i < 10; ++i) {
        int rnd = rand() % 7;
        cclSortLinkedListAdd(linked_list, &rnd, cmp_int);
    }
    printf("\nSorted Linked list: ");
    it = cclLinkedListGetIter(linked_list);
    while (it) {
        int *data = (int *)cclLinkedListIterData(it);
        printf("%d ", *data);
        it = cclLinkedListIterNext(it);
    }
    printf("\n");
}

int linkedListSuiteAdd()
{ 
    CU_pSuite pSuite = NULL;

    pSuite = CU_add_suite("CCL Linked List", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "Linked List: check add and size", check_add_and_size))
    || (NULL == CU_add_test(pSuite, "Linked List: check add/get first/last item", check_add_get_first_last))
    || (NULL == CU_add_test(pSuite, "Linked List: check update/remove", check_update_remove))
    || (NULL == CU_add_test(pSuite, "Linked List: add to sort", check_add_to_sort))
   
    )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return 0;
}
