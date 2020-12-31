#include "hash-function.h"
#include "threading.h"
#include <stdint.h>
#include "alloc-functions.h"
#include <stddef.h>
#include <stdio.h>
#include "hash_table.h"

extern int entry_list_node_destroy(entry_list_node *node)
{
	_free(node->entry.key);
	_free(node->entry.data);
	_free(node);
	return 0;
}

extern int hash_table_init(hash_table *hash_table, uint32_t initial_size)
{
	entry_list_node **hash_entries = (entry_list_node **)_malloc(sizeof *hash_entries * initial_size);
	if (!hash_entries)
		return 1;
	lock_t *locks = (lock_t *)_malloc(sizeof *locks * initial_size);
	if (!locks)
	{
		_free(hash_entries);
		return 1;
	}
	uint32_t *entries_count = (uint32_t *)_malloc(sizeof *entries_count * initial_size);
	if (!entries_count)
	{
		_free(hash_entries);
		_free(locks);
		return 1;
	}
	for (uint32_t index = 0; index < initial_size; ++index)
	{
		hash_entries[index] = NULL;
		lock_init(&(locks[index]));
		entries_count[index] = 0;
	}
	hash_table->entries_length = initial_size;
	hash_table->entries_count = entries_count;
	hash_table->entires_locks = locks;
	hash_table->entries = hash_entries;
	return 0;
}

extern int hash_table_destroy(hash_table *hash_table)
{
	_free(hash_table->entries_count);
	for (uint32_t index = 0; index < hash_table->entries_length; ++index)
	{
		lock_destroy(&hash_table->entires_locks[index]);
		entry_list_node *node = hash_table->entries[index];
		entry_list_node *buffor = node;
		while (node != NULL)
		{
			buffor = node->next;
			entry_list_node_destroy(node);
			node = buffor;
		}
	}
	_free(hash_table->entires_locks);
	_free(hash_table->entries);
	return 0;
}

int add_operation_with_index(hash_table *hash_table, const char *key, const uint32_t key_length, const char *data, const uint32_t data_length, const uint32_t hash, const uint32_t hash_index)
{

	entry_list_node *node = hash_table->entries[hash_index];
	if (node == NULL)
	{
		entry_list_node *point = (entry_list_node *)_malloc(sizeof *point);
		if (!point)
		{
			return 1;
		}
		char *key_copy = (char *)_malloc(sizeof *key_copy * key_length);
		if (!key_copy)
		{
			_free(point);
			return 1;
		};
		char *data_copy = (char *)_malloc(sizeof *data * data_length);
		if (!data_copy)
		{
			_free(point);
			_free(key_copy);
			return 1;
		}
		for (uint32_t key_index = 0; key_index < key_length; ++key_index)
		{
			key_copy[key_index] = key[key_index];
		}
		for (uint32_t data_index = 0; data_index < data_length; ++data_index)
		{
			data_copy[data_index] = data[data_index];
		}
		point->entry.hash = hash;
		point->entry.key = key_copy;
		point->entry.key_length = key_length;
		point->entry.data = data_copy;
		point->entry.data_length = data_length;
		point->next = NULL;
		hash_table->entries[hash % hash_table->entries_length] = point;
		return 0;
	}
	do
	{
		if (strings_are_equal(node->entry.key, node->entry.key_length, key, key_length))
		{
			char *data_copy = (char *)_malloc(sizeof *data * data_length);
			if (!data_copy)
			{
				return 1;
			}
			for (uint32_t data_index = 0; data_index < data_length; ++data_index)
			{
				data_copy[data_index] = data[data_index];
			}
			node->entry.data = data_copy;
			node->entry.data_length = data_length;
			return 0;
		}
		node = node->next;
	} while (node->next != NULL);

	entry_list_node *point = (entry_list_node *)_malloc(sizeof *point);
	if (!point)
	{
		return 1;
	}
	char *key_copy = (char *)_malloc(sizeof *key_copy * key_length);
	if (!key_copy)
	{
		_free(point);
		return 1;
	};
	char *data_copy = (char *)_malloc(sizeof *data * data_length);
	if (!data_copy)
	{
		_free(point);
		_free(key_copy);
		return 1;
	}
	for (uint32_t key_index = 0; key_index < key_length; ++key_index)
	{
		key_copy[key_index] = key[key_index];
	}
	for (uint32_t data_index = 0; data_index < data_length; ++data_index)
	{
		data_copy[data_index] = data[data_index];
	}
	point->entry.hash = hash;
	point->entry.key = key_copy;
	point->entry.key_length = key_length;
	point->entry.data = data_copy;
	point->entry.data_length = data_length;
	point->next = NULL;
	node->next = point;
}

/**/

extern int add_operation(hash_table *hash_table, const char *key, const uint32_t key_length, const char *data, const uint32_t data_length)
{
	uint32_t hash = hash_string(key, key_length);
	uint32_t hash_index = hash % hash_table->entries_length;
	/*lock on specific hash_table index+*/
	lock_lock(&(hash_table->entires_locks[hash_index]));
	int result = add_operation_with_index(hash_table, key, key_length, data, data_length, hash, hash_index);
	lock_unlock(&(hash_table->entires_locks[hash_index]));
	return result;
}

extern int del_operation(hash_table *hash_table, const char *key_string, const uint32_t key_length)
{
	uint32_t hash = hash_string(key_string, key_length);
	uint32_t hash_index = hash % hash_table->entries_length;
	lock_lock(&(hash_table->entires_locks[hash_index]));
	entry_list_node *node = hash_table->entries[hash_index];
	entry_list_node *previous = node;
	while (node != NULL)
	{
		if (strings_are_equal(node->entry.key, node->entry.key_length, key_string, key_length))
		{
			if (previous == node)
			{
				hash_table->entries[hash_index] = node->next;
				entry_list_node_destroy(node);
			}
			else
			{
				previous->next = node->next;
				entry_list_node_destroy(node);
			}
			lock_unlock(&(hash_table->entires_locks[hash_index]));
			return 0;
		}
		previous = node;
	}
	lock_unlock(&(hash_table->entires_locks[hash_index]));
	return 1;
}

//no copy get?
extern entry *get_operation(const hash_table *hash_table, const char *key, const uint32_t key_length)
{
	uint32_t hash = hash_string(key, key_length);
	entry_list_node *node = hash_table->entries[hash % hash_table->entries_length];
	while (node != NULL)
	{
		if (strings_are_equal(node->entry.key, node->entry.key_length, key, key_length))
		{
			return &(node->entry);
		}
		node = node->next;
	}
	return NULL;
}

//get_all_keys_operation()
//del_all_operation()

