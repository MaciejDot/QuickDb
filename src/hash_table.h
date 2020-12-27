#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__
#include <stdint.h>
typedef hash_table;
typedef entry;

extern int hash_table_init(hash_table *hash_table, uint32_t initial_size);

extern int hash_table_destroy(hash_table *hash_table);

extern int add_operation(hash_table *hash_table, const char *key, const uint32_t key_length, const char *data, const uint32_t data_length);

int del_operation(hash_table *hash_table, const char *key_string, const uint32_t key_length);

entry *get_operation(const hash_table *hash_table, const char *key, const uint32_t key_length);
#endif