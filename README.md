# Domino

## Building the Library

Note: This will also build the test executable
```sh
cmake -G "Ninja" -S . -B build
cmake --build build
```

## Running the unit tests
This project uses Google Test for unit testing.

1. [Build the test executable](#building-the-library)
2. Run it: `cd build/tests && ctest`
