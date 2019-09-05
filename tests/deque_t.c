/*
 * File:   deque_t.c
 *
 * Created on Sep 5, 2019, 15:49:18 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "deque.h"

int init_suite(void);
int clean_suite(void);


void deque_create_test()
{
    ccl_deque_t *deq = cclDequeInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL_FATAL(deq);
    int size_deq = cclDequeSize(deq);
    CU_ASSERT(size_deq == 0);
    cclDequeDestroy(deq);
}

void add_elements_to_deque()
{
    const int deq_size = 20;

    ccl_deque_t *deq = cclDequeInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL_FATAL(deq);

    int i = 0;
    for (i = 0; i < deq_size; ++i) {
        cclDequePushFront(deq, &i);
    }
    for (i = 0+10; i < deq_size+10; ++i) {
        cclDequePushBack(deq, &i);
    }
    
    int size_deq = cclDequeSize(deq);
    CU_ASSERT(size_deq == deq_size*2);

    while (!cclDequeEmpty(deq)) {
        int item;
        cclDequePopFront(deq, (void *)&item);
        printf("%d ", item);
    }


    cclDequeDestroy(deq);
}

void get_set_clear_elements_from_deque()
{
    const int deq_size = 20;

    ccl_deque_t *deq = cclDequeInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL_FATAL(deq);

    int i = 0;
    for (i = 0; i < deq_size; ++i) {
        cclDequePushFront(deq, &i);
    }
    for (i = 0+10; i < deq_size+10; ++i) {
        cclDequePushBack(deq, &i);
    }
    
    int size_deq = cclDequeSize(deq);
    CU_ASSERT(size_deq == deq_size*2);

    int first = 0;
    int last  = 0;

    cclDequeGetFirst(deq, &first);
    CU_ASSERT(first == deq_size - 1);
    cclDequeGetLast(deq, &last);
    CU_ASSERT(last == deq_size + 10 - 1);

    int set_first = 666;
    cclDequeSetFirst(deq, &set_first);
    cclDequeGetFirst(deq, &first);
    CU_ASSERT(first == set_first);
 
    int set_last  = 1488;
    cclDequeSetLast(deq, &set_last);
    cclDequeGetLast(deq, &last);
    CU_ASSERT(last == set_last);

     while (!cclDequeEmpty(deq)) {
        int item;
        cclDequePopFront(deq, (void *)&item);
        printf("%d ", item);
    }

    cclDequeClear(deq);
    size_deq = cclDequeSize(deq);
    CU_ASSERT(size_deq == 0);

    cclDequeDestroy(deq);
}

/**
 * Deque suite add
 * 
 * @return 
 */
int dequeSuiteAdd()
{
    CU_pSuite pSuite = NULL;

    /* Add a suite to the registry */
    pSuite = CU_add_suite("CCL deque", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add this module tests to the suite */
    if ((NULL == CU_add_test(pSuite, "deque create/destroy", deque_create_test)) ||
        (NULL == CU_add_test(pSuite, "add elements to deque, move and delete it", add_elements_to_deque))  ||
        (NULL == CU_add_test(pSuite, "get set clear elements from deque", get_set_clear_elements_from_deque)) ) {
        
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    return 0;
}
