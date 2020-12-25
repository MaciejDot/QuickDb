#include <stdlib.h>
#include "alloc-functions.h"
/*facade for most important functions for performance*/
extern void* _malloc(size_t size){
    return malloc(size);
}
extern void _free(void* pointer){
    free(pointer);
}
extern void* _realloc(void* pointer, size_t size){
    return realloc(pointer, size);
}