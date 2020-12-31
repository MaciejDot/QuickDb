#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__
#include "hash-function.h"
#include "threading.h"
#include <stdint.h>
#include "alloc-functions.h"
#include <stddef.h>
#include <stdio.h>
typedef struct entry
{
	unsigned int hash;
	char *key;
	unsigned int key_length;
	char *data;
	unsigned int data_length;
} entry;

typedef struct entry_list_node
{
	entry entry;
	struct entry_list_node *next;
} entry_list_node;

typedef struct hash_table
{
	entry_list_node **entries;
	uint32_t entries_length;
	lock_t *entires_locks;
	uint32_t *entries_count;
} hash_table;

extern int hash_table_init(hash_table *hash_table, uint32_t initial_size);

extern int hash_table_destroy(hash_table *hash_table);

/**/

extern int add_operation(hash_table *hash_table, const char *key, const uint32_t key_length, const char *data, const uint32_t data_length)
;

extern int del_operation(hash_table *hash_table, const char *key_string, const uint32_t key_length);
//no copy get?
extern entry *get_operation(const hash_table *hash_table, const char *key, const uint32_t key_length);
#endif