/**
* \file list_t.h
* \author max <mpano91@gmail.com> 
*
*
* Created on Tue Jun  5 16:11:48 2018
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <CUnit/Basic.h>

#include "list.h"

int init_suite(void);
int clean_suite(void);

double timeInMilliSeconds(void) {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

void free_int_fn(void *pointer) {
    free(pointer);
}

void list_create_test() {
    teoArrayList *al = teoArrayListNew(free_int_fn);
    CU_ASSERT_PTR_NOT_NULL_FATAL(al);

    int rv = teoArrayListFree(al);
    CU_ASSERT(!rv);
}

void list_add_remove_test() {
    teoArrayList *al = teoArrayListNew(free_int_fn);
    CU_ASSERT_PTR_NOT_NULL_FATAL(al);

    int *el = (int *)malloc(sizeof(int));
    size_t d_len = sizeof(int);
    *el = 45;
    int i = 0;
    double t_beg = timeInMilliSeconds();
    for (i=0; i<1000000; i++)
        teoArrayListAdd(al, (void *)el, d_len);
    CU_ASSERT(teoArrayListLength(al) == 1000000);
  //  for (i=0; i<200000; i++)
        teoArrayListDelIdx(al, 0, 1000000);
    printf("\n\t%d records add/delete, time %.3f sec ", 1000000, ((timeInMilliSeconds() - t_beg))/1000);
    CU_ASSERT(teoArrayListLength(al) == 0);
    int rv = teoArrayListFree(al);
    CU_ASSERT(!rv);
    free(el);
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
    if ((NULL == CU_add_test(pSuite, "list create/destroy", list_create_test)) ||
        (NULL == CU_add_test(pSuite, "add elements to list, move and delete it", list_add_remove_test))){// ||
       // (NULL == CU_add_test(pSuite, "check queue iterator", check_queue_iterator)) ||
       // (NULL == CU_add_test(pSuite, "delete elements from queue", delete_elements_from_queue)) ) {
        
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    return 0;
}
