/*
 * File:   deque_t.c
 *
 * Created on Sep 5, 2019, 15:49:18 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include "teoccl/deque.h"

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

void deq_with_pointers()
{
    typedef struct data {
        uint32_t packet_length;
        uint16_t id;
        char packet[];
    } data_t;

    const char* p_1 = "qwerty";
    const char* p_2 = "qwerty12345";

    size_t p1_size = strlen(p_1)+1;
    size_t p2_size = strlen(p_2)+1;

    data_t *packet_1 = malloc(sizeof(data_t) + p1_size);
    packet_1->id = 1;
    packet_1->packet_length = p1_size;
//    packet_1->packet = malloc(strlen(p_1)+1);
    strncpy(packet_1->packet, p_1, p1_size);

    data_t *packet_2 = malloc(sizeof(data_t) + p2_size);
    packet_2->id = 2;
    packet_2->packet_length = p2_size;
//    packet_2->packet = malloc(strlen(p_2)+1);
    strncpy(packet_2->packet, p_2, p2_size);

    ccl_deque_t *d = cclDequeInit(sizeof(data_t*));

    cclDequePushFront(d, &packet_1);
    cclDequePushFront(d, &packet_2);

    while (!cclDequeEmpty(d)) {
        data_t *packet = NULL;
        cclDequePopFront(d, (void *)&packet);
        printf("len %d, id %d, data %s\n", packet->packet_length, packet->id, packet->packet);
    }

    cclDequeDestroy(d);

//    free(packet_1->packet);
    free(packet_1);
//    free(packet_2->packet);
    free(packet_2);

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
        (NULL == CU_add_test(pSuite, "get set clear elements from deque", get_set_clear_elements_from_deque)) ||
        (NULL == CU_add_test(pSuite, "deq with pointers", deq_with_pointers)) ) {
        
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    return 0;
}
