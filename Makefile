C_FLAGS = -std=c11 -Wall

.PHONY: test
test:
	$(CC) $(C_FLAGS) filedb.c test/tests.c -o tests -I.
	./tests ~/
