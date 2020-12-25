/*all database related objects are stored here*/

/*here or in config hmmmm... */
typedef struct db_config {
    unsigned int initial_size;
}
db_config;

typedef struct db {
    unsigned int test;
} db;

db* init_db(db_config db_config){}