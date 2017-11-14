CFLAGS += -std=c11 -Wall

filedb_tests: filedb.o tests/tests.o
	$(CC) $(LDFLAGS) $^ -o $@

.PHONY: run_tests
run_tests: filedb_tests
	./filedb_tests ./
