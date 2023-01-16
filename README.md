# Ping

User interface for ping utility.

## Development

### Dependencies

- CMake 3.5+
- Qt 6.0.4+
- C++ compiler

### Build

```bash
cmake . -B build
cmake --build build
```

## Release

```bash
cmake . -B build
cmake --build build --config Release --target ALL_BUILD -j 10
```

## License

Licensed under the [MIT](LICENSE) License.