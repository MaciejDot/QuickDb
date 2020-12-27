#ifndef __THREADING_H__
#define __THREADING_H__
typedef lock_t;
int lock_init(lock_t *lock);
int lock_destroy(lock_t *lock);
int lock_lock(lock_t *lock);
int lock_unlock(lock_t *lock);
#endif