/**
* \file list_t.h
* \author max <mpano91@gmail.com> 
*
*
* Created on Tue Jun  5 16:11:48 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "list.h"

int init_suite(void);
int clean_suite(void);

void free_int_fn(void *pointer) {
    free(pointer);
}

void list_create_test() {
    teoArrayList *al = teoArrayListNew(free_int_fn);
    CU_ASSERT_PTR_NOT_NULL_FATAL(al);

    int rv = teoArrayListFree(al);
    CU_ASSERT(!rv);
}


/**
 * List suite add
 * 
 * @return 
 */
int listSuiteAdd() {
    
    CU_pSuite pSuite = NULL;

    /* Add a suite to the registry */
    pSuite = CU_add_suite("Teo list", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add this module tests to the suite */
    if ((NULL == CU_add_test(pSuite, "list create/destroy", list_create_test))) { //||
       // (NULL == CU_add_test(pSuite, "add elements to queue, move and delete it", add_elements_to_queue)) ||
       // (NULL == CU_add_test(pSuite, "check queue iterator", check_queue_iterator)) ||
       // (NULL == CU_add_test(pSuite, "delete elements from queue", delete_elements_from_queue)) ) {
        
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    return 0;
}
