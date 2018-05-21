#include "filedb.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// Creates a local char buffer 'path' containing the full path to the file for KEY
#define MAKE_PATH(DATABASE, KEY)							\
	size_t _length = (strlen(DATABASE) + strlen(KEY) + 1);	\
	char path[_length];										\
	snprintf(&path[0], _length, "%s%s", DATABASE, KEY)

void fdb_remove(fdb database, char *key) {
	MAKE_PATH(database, key);
	remove(path);
}

void fdb_set_string(fdb database, char *key, char *string) {
	MAKE_PATH(database, key);
	FILE *file = fopen(path, "w");
	fputs(string, file);
	fclose(file);
}

long file_size(FILE *file) {
	fpos_t pos;
	fgetpos(file, &pos);
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fsetpos(file, &pos);
	return size;
}

char *fdb_get_string(fdb database, char *key) {
	MAKE_PATH(database, key);
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		return NULL;
	}
	
	int buffer_size = file_size(file) + 1;
	char *buffer = malloc(buffer_size);
	int read_size = fread(buffer, sizeof(unsigned char), buffer_size, file);
	fclose(file);

	if (read_size + 1 != buffer_size) {
		return NULL;
	}
	
	return buffer;
}

#define FDB_PRIMITIVE_SET_IMPLEMENT(TYPE)			\
	FDB_PRIMITIVE_SET_DEFINITION(TYPE) {			\
		MAKE_PATH(database, key);					\
		FILE *file = fopen(path, "w");				\
		fwrite(&value, sizeof(TYPE), 1, file);		\
		fclose(file);								\
	}

#define FDB_PRIMITIVE_GET_IMPLEMENT(TYPE)			\
	FDB_PRIMITIVE_GET_DEFINITION(TYPE) {			\
		MAKE_PATH(database, key);					\
		FILE *file = fopen(path, "r");				\
		if (file == NULL) {							\
			return 0;								\
		}											\
		TYPE value = 0;								\
		fread(&value, sizeof(TYPE), 1, file);		\
		return value;								\
	}

#define FDB_PRIMITIVE_IMPLEMENT(TYPE) FDB_PRIMITIVE_SET_IMPLEMENT(TYPE) FDB_PRIMITIVE_GET_IMPLEMENT(TYPE)

FDB_PRIMITIVE_IMPLEMENT(float)
FDB_PRIMITIVE_IMPLEMENT(double)
FDB_PRIMITIVE_IMPLEMENT(int8_t)
FDB_PRIMITIVE_IMPLEMENT(int16_t)
FDB_PRIMITIVE_IMPLEMENT(int32_t)
FDB_PRIMITIVE_IMPLEMENT(int64_t)
FDB_PRIMITIVE_IMPLEMENT(uint8_t)
FDB_PRIMITIVE_IMPLEMENT(uint16_t)
FDB_PRIMITIVE_IMPLEMENT(uint32_t)
FDB_PRIMITIVE_IMPLEMENT(uint64_t)
