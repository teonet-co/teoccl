/* 
<<<<<<< HEAD
 * \file:   memory.c
=======
 * \file:   teo_memory.c
>>>>>>> feature/linked-list
 * \author: max <mpano91@gmail.com>
 *
 * Created on June 27, 2018, 4:18 PM
 */
#define _POSIX_C_SOURCE 200809L // strdup warning

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

static
void ccl_memory_out(void)
{
    (void)fprintf(stderr, "CCL. Out of memory\n");
    exit(1);
}


void *ccl_malloc(size_t size)
{
    void *memory = NULL;
    if((memory = malloc(size)) == NULL) {
        ccl_memory_out();
    }
    
    return memory;
}


void *ccl_calloc(size_t size)
{
    void *memory = NULL;
    memory = ccl_malloc(size);
    memset(memory, 0, size);

    return memory;
}


char *ccl_strdup(const char *str)
{
    char *newstr;
    if ((newstr = strdup(str)) == NULL) {
        ccl_memory_out();
    }

    return newstr;
}


char *ccl_strndup(char *str, size_t len)
{
    char *newstr;
    if ((newstr = malloc(len + 1)) == NULL) {
        ccl_memory_out();
    }

    (void)strncpy(newstr, str, len);
    newstr[len] = '\0';

    return (newstr);
}


void *ccl_realloc(void *ptr, size_t size)
{
    void *memory;
    if ((memory = realloc(ptr, size)) == NULL) {
        ccl_memory_out();
    }

    return memory;
}
