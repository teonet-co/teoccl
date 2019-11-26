/* 
 * \file:   memory.c
 * \author: max <mpano91@gmail.com>
 *
 * Created on June 27, 2018, 4:18 PM
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__GNUC__)
#include <stdnoreturn.h>
#define TEOCCL_NORETURN noreturn
#elif defined(_MSC_VER)
// C11 _Noreturn is not supported in MSVC yet.
#define TEOCCL_NORETURN __declspec(noreturn)
#else
#define TEOCCL_NORETURN
#endif

TEOCCL_NORETURN static void exit_out_of_memory(void) {
    (void)fprintf(stderr, "CCL. Out of memory\n");
    exit(1);
}

void *ccl_malloc(size_t size) {
    void *memory = malloc(size);
    if (memory == NULL) {
        exit_out_of_memory();
    }
    
    return memory;
}

void *ccl_calloc(size_t size) {
    void *memory = ccl_malloc(size);
    memset(memory, 0, size);

    return memory;
}

char *ccl_strdup(const char *str) {
#if defined(_MSC_VER)
    char *newstr = _strdup(str);
#else
    char *newstr = strdup(str);
#endif

    if (newstr == NULL) {
        exit_out_of_memory();
    }

    return newstr;
}

char *ccl_strndup(const char *str, size_t len) {
    char *newstr = ccl_malloc(len + 1);

#if defined(_MSC_VER)
    (void)strncpy_s(newstr, len + 1, str, len);
#else
    (void)strncpy(newstr, str, len);
#endif

    newstr[len] = '\0';

    return (newstr);
}

void *ccl_realloc(void *ptr, size_t size) {
    void *memory = realloc(ptr, size);
    if (memory == NULL) {
        exit_out_of_memory();
    }

    return memory;
}
