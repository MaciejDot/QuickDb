#include "hash-function.h"
#include <stdint.h>
/*for hash tables and other data structeres not suitable for password storage*/
extern uint32_t hash_string(const char* st, const uint32_t len) {
	if (len <= 0 || st == 0) return 0;
	uint32_t hash = len;
	for (uint32_t index = 0; index < len / 2; ++index) {
		hash += st[index] + (((uint32_t)st[index + 1]) << 8);
		hash += hash >> 11;
	}
	if (len % 2 == 1)
	{
		hash += st[len - 1];
		hash += hash >> 11;
	}
	hash ^= hash << 3;
	hash += hash >> 5;
	hash ^= hash << 13;
	hash += hash >> 17;
	hash ^= hash << 23;
	hash += hash >> 7;
	return hash;
}