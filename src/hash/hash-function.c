#include "hash-function.h"
/*for hash tables and other data structeres not suitable for password storage*/
extern unsigned int hash(const char* st, const unsigned int len) {
	if (len <= 0 || st == 0) return 0;
	unsigned int hash = len;
	for (unsigned int index = 0; index < len / 2; ++index) {
		hash += st[index] + (((unsigned int)st[index + 1]) << 8);
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