#include "filedb.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int file_size(FILE *file) {
	fpos_t pos;
	fgetpos(file, &pos);
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fsetpos(file, &pos);
	return size;
}

char *path_for_key(fdb database, char *key) {
	int path_length = strlen(database) + strlen(key) + 1; // Add one to include a null character
	char *buffer = malloc(sizeof(char) * path_length);
	snprintf(buffer, path_length, "%s%s", database, key);
	return buffer;
}

void fdb_remove_key(fdb database, char *key) {
	char *path = path_for_key(database, key);
	remove(path);
	free(path);
}

void fdb_set_string(fdb database, char *key, char *string) {
	char *path = path_for_key(database, key);
	FILE *file = fopen(path, "w");
	free(path);
	
	fputs(string, file);
	fclose(file);
}

char *fdb_get_string(fdb database, char *key) {
	char *path = path_for_key(database, key);
	FILE *file = fopen(path, "r");
	free(path);
	
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
		char *path = path_for_key(database, key);	\
		FILE *file = fopen(path, "w");				\
		free(path);									\
		fwrite(&value, sizeof(TYPE), 1, file);		\
		fclose(file);								\
	}

#define FDB_PRIMITIVE_GET_IMPLEMENT(TYPE)			\
	FDB_PRIMITIVE_GET_DEFINITION(TYPE) {			\
		char *path = path_for_key(database, key);	\
		FILE *file = fopen(path, "r");				\
		free(path);									\
		if (file == NULL) {							\
			return 0;								\
		}											\
		TYPE value = 0;								\
		fread(&value, sizeof(TYPE), 1, file);		\
		return value;								\
	}

#define FDB_PRIMITIVE_IMPLEMENT(TYPE) FDB_PRIMITIVE_SET_IMPLEMENT(TYPE) FDB_PRIMITIVE_GET_IMPLEMENT(TYPE)

FDB_PRIMITIVE_IMPLEMENT(char)
FDB_PRIMITIVE_IMPLEMENT(double)
FDB_PRIMITIVE_IMPLEMENT(float)
FDB_PRIMITIVE_IMPLEMENT(int)
FDB_PRIMITIVE_IMPLEMENT(long)
FDB_PRIMITIVE_IMPLEMENT(short)
