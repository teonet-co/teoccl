/*
 * File:   stack_t.c
 *
 * Created on Sep 5, 2019, 15:49:18 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "teoccl/stack.h"

int init_suite(void);
int clean_suite(void);


void stack_create_test()
{
    ccl_stack_t *stack = cclStackInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL_FATAL(stack);
    int size_st = cclStackSize(stack);
    CU_ASSERT(size_st == 0);
    cclStackDestroy(stack);
}

void add_elements_to_stack()
{
    const int st_size = 20;

    ccl_stack_t *stack = cclStackInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL_FATAL(stack);

    int i = 0;
    for (i = 0; i < st_size; ++i) {
        cclStackPush(stack, &i);
    }
   
    int size_st = cclStackSize(stack);
    CU_ASSERT(size_st == st_size);

    while (!cclStackEmpty(stack)) {
        int item;
        cclStackPop(stack, (void *)&item);
        printf("pop %d, size %d\n", item, cclStackSize(stack));
    }

    cclStackDestroy(stack);
}

void get_set_clear_elements_from_stack()
{
    const int st_size = 20;

    ccl_stack_t *stack = cclStackInit(sizeof(int));
    CU_ASSERT_PTR_NOT_NULL_FATAL(stack);

    int i = 0;
    for (i = 0; i < st_size; ++i) {
        cclStackPush(stack, &i);
    }
   
    int size_st = cclStackSize(stack);
    CU_ASSERT(size_st == st_size);

    int top = 0;
    cclStackTop(stack, &top);
    CU_ASSERT(top == st_size - 1);

    cclStackClear(stack);
    size_st = cclStackSize(stack);
    CU_ASSERT(size_st == 0);

    cclStackDestroy(stack);
}

/**
 * Que suite add
 * 
 * @return 
 */
int stackSuiteAdd()
{
    CU_pSuite pSuite = NULL;

    /* Add a suite to the registry */
    pSuite = CU_add_suite("CCL stack", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add this module tests to the suite */
    if ((NULL == CU_add_test(pSuite, "deque create/destroy", stack_create_test)) ||
        (NULL == CU_add_test(pSuite, "add elements to deque, move and delete it", add_elements_to_stack))  ||
        (NULL == CU_add_test(pSuite, "get set clear elements from deque", get_set_clear_elements_from_stack)) ) {
        
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    return 0;
}
