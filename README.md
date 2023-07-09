# Domino

## Building the Library
Requires the [Ninja build system](https://ninja-build.org/).
Note: This will also build the test executable
```sh
cmake -G "Ninja" -S . -B build
cmake --build build
```

## Running the unit tests
This project uses [Google Test](https://google.github.io/googletest/) for unit testing.

1. [Build the test executable](#building-the-library)
2. Run it: `cd build/tests && ctest`
