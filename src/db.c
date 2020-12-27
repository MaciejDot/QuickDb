/*all database related objects are stored here*/

#include "hash_table.h"
#include "alloc-functions.h"

/*here or in config hmmmm... */

typedef struct db_config {
    unsigned int initial_size;
}
db_config;

typedef struct db {
    hash_table store;
} db;

int db_init(db* db, db_config config){
    hash_table* store = _malloc(sizeof * store);
    if(!store) return 1;
    if(!hash_table_init(store, config.initial_size))return 1;
    db->store = store;
    return 0;
}

void db_destroy(db* db){
    hash_table_destroy(db -> store);
    _free(db);
}