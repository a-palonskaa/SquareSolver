# Quadratic equation solver

## Overview
This is a quadratic equation solver. Give me three coefficients and get result immediately.

<img src="Design/quadr_solver_test.png" width="30%" alt="Logo" /> <img src="Design/test_quadr_wrong_test.png" width="45%" alt="Logo" />

## Build
Run `make` to build program in default mode.

`./build/square` to run program.

> [!NOTE]
> Default mode is `release` mode

---

Run `make release` to build release version of the program.

### Release mode:
- Unit tests are disabled.
- Sets compiler optimization level to **O2**.
- Defines **NDEBUG** (disables standard-C assertions).

---

Run `make debug` to build debug version of the program.

### Debug mode:
- Unit tests are available.
- Sets compiler optimization level to **O0**.
- Adds compilation flag **-ggdb3** (produces extra debugging information).

---

Run `make clean` to remove obj and dependencies files (clean build folder).

## Commands
```-t``` | ```--test```- run tests (available only in debug version)

```-s``` | ```--solve```- solve equation

```-c``` | ```--input-console```- get equation coefficients from stdin

```-i <file name>``` | ```--input-file <file name>```- get coefficients from a file with given name

```-f``` | ```--output-console```- print results to stdout

```-o <file name>``` | ```--output-file <file name>```- print results to a file with given name

```-h``` | ```--help```- print help message with all commands description

> [!NOTE]
> Default mode is `solve` equation mode, get coeffience from `stdin`, print results to `stdout`.
