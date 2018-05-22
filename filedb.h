#pragma once
#include <inttypes.h>

typedef char * fdb;

void fdb_remove(fdb database, char *key);

void fdb_set_string(fdb database, char *key, char *string);
char *fdb_get_string(fdb database, char *key);

#define FDB_PRIMITIVE_SET_DEFINITION(TYPE) void fdb_set_##TYPE(fdb database, char *key, TYPE value)
#define FDB_PRIMITIVE_GET_DEFINITION(TYPE) TYPE fdb_get_##TYPE(fdb database, char *key)
#define FDB_PRIMITIVE_DEFINITION(TYPE) FDB_PRIMITIVE_SET_DEFINITION(TYPE); FDB_PRIMITIVE_GET_DEFINITION(TYPE)

FDB_PRIMITIVE_DEFINITION(float);
FDB_PRIMITIVE_DEFINITION(double);
FDB_PRIMITIVE_DEFINITION(int8_t);
FDB_PRIMITIVE_DEFINITION(int16_t);
FDB_PRIMITIVE_DEFINITION(int32_t);
FDB_PRIMITIVE_DEFINITION(int64_t);
FDB_PRIMITIVE_DEFINITION(uint8_t);
FDB_PRIMITIVE_DEFINITION(uint16_t);
FDB_PRIMITIVE_DEFINITION(uint32_t);
FDB_PRIMITIVE_DEFINITION(uint64_t);

#define fdb_set(DB, KEY, VALUE) _Generic(VALUE, \
    char *: fdb_set_string,                     \
    float: fdb_set_float,                       \
    double: fdb_set_double,                     \
    int8_t: fdb_set_int8_t,                     \
    int16_t: fdb_set_int16_t,                   \
    int32_t: fdb_set_int32_t,                   \
    int64_t: fdb_set_int64_t,                   \
    uint8_t: fdb_set_uint8_t,                   \
    uint16_t: fdb_set_uint16_t,                 \
    uint32_t: fdb_set_uint32_t,                 \
    uint64_t: fdb_set_uint64_t)(DB, KEY, VALUE)
