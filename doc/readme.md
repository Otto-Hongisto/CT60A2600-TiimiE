# CT60A2600-TiimiE (C)

Note: This project resides in https://github.com/LUT-Courses/CT60A2600-TiimiE and https://github.com/Otto-Hongisto/CT60A2600-TiimiE.

## What does the program do?
This project is made and maintained to process Population information system data (see data) using different data structures.
The user can:
    - Load data and create linked lists and binary search trees
    - Add or remove any entities
    - Search data based on different values
    - Sort the data

---

## 📁 Project Structure

```
.
├── Makefile              # Build targets: build, run, test, clean, etc.
├── src/                  # C source files and headers
│   ├── main.c            # Controls the program
│   ├── puu.c             # All functions for the BSTs
│   ├── puu.h
│   ├── lista.c           # Doubly linked list
│   ├── lista.h
│   ├── yleinen.c         # Helper functions for general use
│   └── yleinen.h
├── bin/                  # Compiled binaries (output of build)
│   └── app               # Example executable name
├── test/                 # Test sources (Unity framework)
│   ├── testRunner.c
│   ├── listatesti.c
│   └── puutesti.c
├── data/                 # Input datasets / sample inputs (no secrets)
│   ├── sample-input.txt
│   └── README.md         # Describe data sources and formats
└── doc/                  # Documentation (design notes, Doxygen config)
    └── design.md
    └── html              # Doxygen documentation in HTML
```

> **Notes**
> - `bin/` is generated—usually excluded from version control.
> - Place configuration and design decisions in `doc/`.

---

## 🛠 Prerequisites

- **Compiler**: `gcc` (or `clang`)
- **Make**: GNU Make
- **(Optional)**: `valgrind`, `doxygen`

Check versions:

```bash
gcc --version
make --version
```

---

## 🚀 Quick Start (Build / Run / Test)

```bash
# Build (creates ./bin/app by default)
make

# Run
./bin/app

# Tests
make test

# Valgrind
make valgrind
```

## Example usage of the program
1. Start the program:
    ./bin/app

2. Choose the data structure and load data from a file e.g. "data/miehet_2025.txt"

3. Choose any operation(s)

4. Save the results to a new file

5. End the program

---

## 📚 Documentation

- High-level design/usages: `doc/design.md`
- API docs: generate with Doxygen

```bash
# Generate docs
doxygen doc/Doxyfile
```

---

## 📏 Coding Standards

- **C standard**: C99 
- **Compiler flags**: `-Wall -pedantic`

---

## 🧪 Testing

- Uses Unity framework
- Unity framwork works without any downloads and all the necessary file are in /unity folder
- 17 standarized test cases in total of which all pass

- Manual testing with different inputs has been done

- Memory has been checked using Valgrind

```bash

- To run the tests use:
make test
```

---

## Maintenance and future development
- More test cases
- Even better error handling

- Improved UI
- New data structure


## 🗂️ Version History

| Version | Date       | Author         | Changes                                               |
|--------:|------------|----------------|-------------------------------------------------------|
| 1.0.0   | 2026-03-08 |                | Linked list struct, read file, write file             |
| 2.0.0   | 2026-03-15 |                | Binary tree struct                                    |
| 3.1.0   | 2026-03-21 | Otto Hongisto  | Balanced search tree struct, read file into BST       |
| 4.0.0   | 2026-03-29 | Jaakko Laitinen |Linked list sorting, adding a new node, removing a node|
| 4.1.0   | 2026-04-06 | Otto Hongisto  | Finalizing the program, everything work               |

Tag releases:
- Not in use currently
```bash
git tag -a v0.1.0 -m "Initial scaffold"
git push origin v0.1.0
```

---

## 👤 Author & Course

- **Authors**: Otto Hongisto, Jere Verkkomäki ja Jaakko Laitinen
- **Course**: CT60A2600 Ohjelmakehitys C-kielellä
- **Institution**: LUT University

---

## 📄 License

CC BY if this repository is made public
