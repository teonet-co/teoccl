/*
 * File:   que_t.c
 *
 * Created on Sep 5, 2019, 15:49:18 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "que.h"

int init_suite(void);
int clean_suite(void);


void que_create_test()
{
    ccl_queue_t *que = cclQueInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL_FATAL(que);
    int size_q = cclQueSize(que);
    CU_ASSERT(size_q == 0);
    cclQueDestroy(que);
}

void add_elements_to_que()
{
    const int q_size = 20;

    ccl_queue_t *que = cclQueInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL_FATAL(que);

    int i = 0;
    for (i = 0; i < q_size; ++i) {
        cclQuePush(que, &i);
    }
   
    int size_q = cclQueSize(que);
    CU_ASSERT(size_q == q_size);

    while (!cclQueEmpty(que)) {
        int item;
        cclQuePop(que, (void *)&item);
        printf("%d ", item);
    }

    cclQueDestroy(que);
}

void get_set_clear_elements_from_que()
{
    const int q_size = 20;

    ccl_queue_t *que = cclQueInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL_FATAL(que);

    int i = 0;
    for (i = 0; i < q_size; ++i) {
        cclQuePush(que, &i);
    }
   
    int size_q = cclQueSize(que);
    CU_ASSERT(size_q == q_size);

    int first = 0;
    cclQueFront(que, &first);
    CU_ASSERT(first == 0);

    int last = 0;
    cclQueBack(que, &last);
    CU_ASSERT(last == q_size - 1);

    cclQueClear(que);
    size_q = cclQueSize(que);
    CU_ASSERT(size_q == 0);

    cclQueDestroy(que);
}

/**
 * Que suite add
 * 
 * @return 
 */
int queSuiteAdd()
{
    CU_pSuite pSuite = NULL;

    /* Add a suite to the registry */
    pSuite = CU_add_suite("CCL que", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add this module tests to the suite */
    if ((NULL == CU_add_test(pSuite, "deque create/destroy", que_create_test)) ||
        (NULL == CU_add_test(pSuite, "add elements to deque, move and delete it", add_elements_to_que))  ||
        (NULL == CU_add_test(pSuite, "get set clear elements from deque", get_set_clear_elements_from_que)) ) {
        
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    return 0;
}
