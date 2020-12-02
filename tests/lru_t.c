/*
 * File:   que_t.c
 *
 * Created on Sep 5, 2019, 15:49:18 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "teoccl/algs/lru_cache.h"

int init_suite(void);
int clean_suite(void);


void lru_create_test()
{
    ccl_lru_cache_t *lru = cclLruInit(3);
    CU_ASSERT_PTR_NOT_NULL_FATAL(lru);
    printf("\n LRU NOT NULL\n");
    cclLruDestroy(lru);
}

void display_int(const void *const data)
{
    printf("      INT data: \"%d\"\n", *(int *)data);
}

void display_str(const void *const data)
{
    printf("      CHAR ARR data: \"%s\"\n", (char *)data);
}

void add_elements_to_lru()
{
    const int lru_size = 4;
    ccl_lru_cache_t *lru = cclLruInit(lru_size);
    CU_ASSERT_PTR_NOT_NULL_FATAL(lru);

    int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    int x4 = 4;
    int x5 = 5;
    int x6 = 4;
    printf("\n");
    cclLruRefer(lru, &x1, sizeof(x1));
    cclLruRefer(lru, &x2, sizeof(x2));
    cclLruRefer(lru, &x3, sizeof(x3));
    cclLruRefer(lru, &x4, sizeof(x4));
    cclLruRefer(lru, &x5, sizeof(x5));
    cclLruRefer(lru, &x6, sizeof(x6));
    cclLruRefer(lru, &x4, sizeof(x4));
    cclLruRefer(lru, &x3, sizeof(x3));
/*
    char *s1 = "aaa";
    char *s2 = "bbbb";
    char *s3 = "ccc";
    char *s4 = "dddd";
    char *s5 = "eee";
    char *s6 = "dddd";
    cclLruRefer(lru, s1, sizeof(s1));
    cclLruRefer(lru, s2, sizeof(s2));
    cclLruRefer(lru, s3, sizeof(s3));
    cclLruRefer(lru, s4, sizeof(s4));
    cclLruRefer(lru, s5, sizeof(s5));
    cclLruRefer(lru, s6, sizeof(s6));
    cclLruRefer(lru, s4, sizeof(s4));
    cclLruRefer(lru, s3, sizeof(s3));
*/
    cclLruForeach(lru, display_int);
    cclLruDestroy(lru);
}

/**
 * Lru suite add
 * 
 * @return 
 */
int lruSuiteAdd()
{
    CU_pSuite pSuite = NULL;

    /* Add a suite to the registry */
    pSuite = CU_add_suite("CCL lru", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add this module tests to the suite */
    if ((NULL == CU_add_test(pSuite, "lru create/destroy", lru_create_test)) ||
        (NULL == CU_add_test(pSuite, "add elements to lru", add_elements_to_lru)) ) {
        
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    return 0;
}
