# Lib Power Converter

Common C++11 domain logic library intended for baremetal power converter firmware projects.

## Goals

- CMake-powered static library
- Portable C++11 API surface
- Cross-compile support for modern `arm-none-eabi-gcc`
- Host-side unit testing with GoogleTest + GoogleMock
- Simple extension path for additional compilers/toolchains
- Single-return style rule for implementation files

## Project Layout

- `include/` - Public headers
- `src/` - Library implementation
- `tests/` - Unit tests (host only)
- `cmake/toolchains/` - Cross-compilation toolchain files
- `cmake/` - Shared CMake modules
- `tools/` - Build-time style and helper scripts

## Build

### Host build + tests

```bash
cmake --preset host-debug
cmake --build --preset build-host-debug
ctest --preset test-host-debug
```

### Baremetal ARM build (library only)

```bash
cmake --preset arm-gcc-debug
cmake --build --preset build-arm-gcc-debug
```

## Toolchain Notes

The ARM preset uses `cmake/toolchains/arm-none-eabi-gcc.cmake` and assumes that
`arm-none-eabi-gcc` and related binutils are on your `PATH`.

To support a new compiler family, add a new toolchain file under `cmake/toolchains/`
and, if needed, extend `cmake/CompilerOptions.cmake` with family-specific warnings
and freestanding flags.
