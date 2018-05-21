# filedb
This is a _really_ simple key-value store for local use. Each key/value is its own file.
A database is just a folder of keys, making it easily inspectable.

It uses C11 generics to get out of your way as much as possible.

## Usage
```c
fdb database = "path/to/folder/";

// Primitives
fdb_set(database, "five", (uint8_t)5);
uint8_t five = fdb_get_uint8_t(database, "five");

fdb_set(database, "negative_value", (double)-1.312);
double negative_value = fdb_get_double(database, "negative_value");

// Strings
fdb_set(database, "To have no errors\nwould be life without meaning\nNo struggle, no joy.", "poem");
char *poem = fdb_get_string(database, "poem");
free(poem); // Strings are the only type that fdb places in the heap.

// Spring cleaning
fdb_remove(database, "poem");
fdb_remove(database, "five");
fdb_remove(database, "negative_value");
```

Note that the file format is not portable, so this project is probably only useful locally. It might work on different systems as long
as they have the same endianness, but I haven't tested it.
