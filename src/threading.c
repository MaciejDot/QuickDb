#include <pthread.h>
#include <stdio.h>
#include "threading.h"
/*facade for pthread library*/

typedef pthread_mutex_t lock_t;

extern int lock_init(lock_t * lock)
{
    return pthread_mutex_init(lock, NULL);
};

extern int lock_destroy(lock_t * lock){
    return pthread_mutex_destroy(lock);
};

extern int lock_lock(lock_t * lock){
    return pthread_mutex_lock(lock);
};

extern int lock_unlock(lock_t * lock){
    return pthread_mutex_unlock(lock);
};