#ifndef __THREADING_H__
#define __THREADING_H__
#include <pthread.h>
#include <stdio.h>
typedef pthread_mutex_t lock_t;
extern int lock_init(lock_t * lock);

extern int lock_destroy(lock_t * lock);

extern int lock_lock(lock_t * lock);

extern int lock_unlock(lock_t * lock);
#endif