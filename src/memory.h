/* 
 * \file:   teo_memory.h
 * \author: max <mpano91@gmail.com>
 *
 * Created on Apr 23, 2019, 7:52 PM
 */

#ifndef TEO_MEMORY_H
#define TEO_MEMORY_H
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void *ccl_malloc(size_t);
void *ccl_calloc(size_t);
char *ccl_strdup(const char *);
char *ccl_strndup(char *, size_t);
void *ccl_realloc(void *, size_t);

#ifdef __cplusplus
}
#endif

#endif /* TEO_MEMORY_H */

