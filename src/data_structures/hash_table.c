typedef struct entry {
	unsigned int hash;
	char* key;
	unsigned int key_length;
	char* data;
	unsigned int data_length;
} entry;

typedef struct entry_list_node {
	entry entry;
	entry_list_node* next;
} entry_list_node;

typedef struct hash_table {
	entry_list_node** entries;
	unsigned int entries_length;
	unsigned int locks;
	unsigned int counters;
	//thread locks * locks
	//locks length == entries length
	//lock only on specific index
	//get operations are locking?
	//flush counters -> need only if we want o(1) 
	//dont need counter flushers
	//prob counters -> hash choose -> ln(n) -> get MLE
	//estimate error 
	//hash counter
	unsigned int entries_count;
} hash_table;