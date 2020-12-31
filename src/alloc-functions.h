#ifndef __ALLOC_FUNCTIONS_H__
#define __ALLOC_FUNCTIONS_H__
#include <stdlib.h>
extern void* _malloc(size_t size);
extern void _free(void* pointer);
extern void* _realloc(void* pointer, size_t size);
#endif