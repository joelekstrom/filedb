struct fdb {
	char *path;
	int path_length;
};

void fdb_init(struct fdb *database, char *folder_path);
void fdb_remove_key(struct fdb *database, char *key);

void fdb_set_string(struct fdb *database, char *key, char *string);
char *fdb_get_string(struct fdb *database, char *key);

#define FDB_PRIMITIVE_SET_DEFINITION(TYPE) void fdb_set_##TYPE(struct fdb *database, char *key, TYPE value)
#define FDB_PRIMITIVE_GET_DEFINITION(TYPE) TYPE fdb_get_##TYPE(struct fdb *database, char *key)
#define FDB_PRIMITIVE_DEFINITION(TYPE) FDB_PRIMITIVE_SET_DEFINITION(TYPE); FDB_PRIMITIVE_GET_DEFINITION(TYPE)

FDB_PRIMITIVE_DEFINITION(char);
FDB_PRIMITIVE_DEFINITION(double);
FDB_PRIMITIVE_DEFINITION(float);
FDB_PRIMITIVE_DEFINITION(int);
FDB_PRIMITIVE_DEFINITION(long);
FDB_PRIMITIVE_DEFINITION(short);

#define fdb_set(DB, KEY, VALUE) _Generic(VALUE,							\
										 char: fdb_set_char,			\
										 double: fdb_set_double,		\
										 float: fdb_set_float,			\
										 int: fdb_set_int,				\
										 long: fdb_set_long,			\
										 short: fdb_set_short)(DB, KEY, VALUE)
