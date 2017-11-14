#include "minunit.h"
#include "../filedb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int tests_run = 0;
fdb database;

static char * test_strings() {
	char text[] = "This is a lime röck\nProbably.";
	fdb_set_string(database, "string", text);
	
	char *string = fdb_get_string(database, "string");
	mu_assert("Getting a string should match the set string.", strcmp((char *)text, string) == 0);
	free(string);
	
	return 0;
}

static char * test_remove_key() {
	fdb_set_string(database, "string_to_remove", (char *)"some unreadable text");
	fdb_remove_key(database, "string_to_remove");
	char *string = fdb_get_string(database, "string_to_remove");
	mu_assert("Value must be nil after removal", string == NULL);
	return 0;
}

static char * test_ints() {
	int number = 12345;
	fdb_set(database, "integer", number);
	int result = fdb_get_int(database, "integer");
	mu_assert("Getting an integer should match the set integer.", number == result);

	fdb_remove_key(database, "hello");
	result = fdb_get_int(database, "hello");
	mu_assert("If key was removed, get_int should return 0", result == 0);
	return 0;
}

static char * test_shorts() {
	short number = 12345;
	fdb_set(database, "short", number);
	short result = fdb_get_short(database, "short");
	mu_assert("Getting a short should match the set short.", number == result);

	fdb_remove_key(database, "short");
	result = fdb_get_int(database, "short");
	mu_assert("If key was removed, get_short should return 0", result == 0);
	return 0;
}

static char * all_tests() {
	mu_run_test(test_strings);
	mu_run_test(test_remove_key);
	mu_run_test(test_ints);
	mu_run_test(test_shorts);
	return 0;
}

int main(int argc, char **argv) {
	database = argv[1];
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

