/*
 * The MIT License
 *
 * Copyright 2016 Kirill Scherba <kirill@scherba.ru>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


/**
 * \file list.h
 * \brief List module
 * \author max <mpano91@gmail.com>
 *
 * Array List container
 *
 * Created on Fri Jun  1 17:01:30 2018
 */

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_LIST_DEFAULT_SIZE 32 // Default ArrayList size

typedef void (array_list_free_fn) (void *data); // free-callback function

/**
 * @brief Array-List structure
 */
typedef struct ccl_array_list {

    void **array;   ///< Core array
    size_t length;  ///< Count of elements in array
    size_t size;    ///< Size of array
    array_list_free_fn *free_fn; ///< Pointer to free-callback function

} ccl_array_list_t;

/**
 * @brief Create new Array-List
 *
 * @param[in] free_fn - Pointer to free-callback function
 * @return Pointer to ccl_array_list_t
 */
ccl_array_list_t *cclArrayListNew(array_list_free_fn *free_fn);

/**
 * @brief Free memory allocated for Array-List
 *
 * @param[in] tal - Pointer to ccl_array_list_t
 * @return zero \todo Create correct return
 */
int cclArrayListFree(ccl_array_list_t *tal);

/**
 * @brief Get element of Array-List by index
 *
 * @param[out] tal - Pointer to ccl_array_list_t
 * @param[in] i - index in ccl_array_list_t
 * @return Pointer to element of ccl_array_list_t
 */
void *cclArrayListGetIdx(ccl_array_list_t *tal, size_t i);

/**
 * @brief Delete range of elements of Array-List since index
 *
 * @param[in] tal - Pointer to ccl_array_list_t
 * @param[in] i - Delete from this index
 * @param[in] count - Count of deleting elements
 * @return zero \todo Create correct return
 */
int cclArrayListDelIdx(ccl_array_list_t *tal, size_t i, size_t count);

/**
 * @brief Add element to Array-List
 *
 * @param[in] tal - Pointer to ccl_array_list_t
 * @param[in] data - Pointer to the data to be added
 * @return -1 - error, 0 - adding was successful
 */
int cclArrayListAdd(ccl_array_list_t *tal, void *data);

/**
 * @brief Get count of elements in Array-List
 *
 * @param[in] tal - Pointer to ccl_array_list_t
 * @return count of elements in ccl_array_list_t
 */
size_t cclArrayListLength(ccl_array_list_t *tal);

/**
 * @brief Run Qsort for array-list
 *
 * @param tal - array list
 * @param compar - pointer to comparator
 */
void cclArrayListSort(ccl_array_list_t *tal, int(*compar)(const void *, const void *));

/**
 * @brief Binary search for array-list 
 *
 * @param tal - array list
 * @param key - what we want to find
 * @param compar - pointer to comparator
 *
 * @return A pointer to an entry in the array-list that matches the search key 
 */
void *cclArrayListBSearch(ccl_array_list_t *tal, const void **key,
    int(*compar)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif
