#include "minunit.h"
#include "../filedb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int tests_run = 0;
fdb database;

static char * test_strings() {
	char text[] = "This is a lime röck\nProbably.";
	fdb_set(database, "string", text);
	char *string = fdb_get_string(database, "string");
	mu_assert("Getting a string should match the set string.", strcmp((char *)text, string) == 0);
	free(string);
	
	return 0;
}

static char * test_remove_key() {
	fdb_set(database, "string_to_remove", (char *)"some unreadable text");
	fdb_remove_key(database, "string_to_remove");
	char *string = fdb_get_string(database, "string_to_remove");
	mu_assert("Value must be nil after removal", string == NULL);
	return 0;
}

#define PRIMITIVE_TEST(TYPE)											\
	static char * test_##TYPE() {										\
		TYPE value = (TYPE)rand();										\
		fdb_set(database, #TYPE, value);								\
		TYPE result = fdb_get_##TYPE(database, #TYPE);					\
		mu_assert("Failed test for ##TYPE, returned value didn't match input", value == result); \
		return 0;														\
	}

PRIMITIVE_TEST(double);
PRIMITIVE_TEST(float);
PRIMITIVE_TEST(int8_t);
PRIMITIVE_TEST(int16_t);
PRIMITIVE_TEST(int32_t);
PRIMITIVE_TEST(int64_t);
PRIMITIVE_TEST(uint8_t);
PRIMITIVE_TEST(uint16_t);
PRIMITIVE_TEST(uint32_t);
PRIMITIVE_TEST(uint64_t);

static char * all_tests() {
	mu_run_test(test_strings);
	mu_run_test(test_remove_key);
	mu_run_test(test_float);
	mu_run_test(test_double);
	mu_run_test(test_int8_t);
	mu_run_test(test_int16_t);
	mu_run_test(test_int32_t);
	mu_run_test(test_int64_t);
	mu_run_test(test_uint8_t);
	mu_run_test(test_uint16_t);
	mu_run_test(test_uint32_t);
	mu_run_test(test_uint64_t);
	return 0;
}

int main(int argc, char **argv) {
	srand(time(NULL));
	database = argv[1] ?: "test_database/";
	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);
	return 0;
}

