# CT60A2600-TiimiE (C)

Note: This project resides in https://github.com/LUT-Courses/CT60A2600-TiimiE and https://github.com/Otto-Hongisto/CT60A2600-TiimiE.

This project is made and maintained to process Population information system data (see data) using different data structures.

---

## 📁 Project Structure

```
.
├── Makefile              # Build targets: build, run, test, clean, etc.
├── src/                  # C source files and headers
│   ├── main.c
│   ├── puukirjasto.c
│   ├── puukirjasto.h
│   ├── listakirjasto.c
│   ├── listakirjasto.h
│   ├── yleinenkirjasto.c
│   └── yleinenkirjasto.h
├── bin/                  # Compiled binaries (output of build)
│   └── app               # Example executable name
├── test/                 # Test sources (e.g., Unity/CMocka) + fixtures
│   ├── testRunner.c
│   ├── listatesti.c
│   └── puutesti.c
├── data/                 # Input datasets / sample inputs (no secrets)
│   ├── sample-input.txt
│   └── README.md         # Describe data sources and formats
└── doc/                  # Documentation (design notes, Doxygen config)
    └── design.md
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

# Memory check
make memcheck
```

---

## 🧭 How to Use This Template (Students)

### 1) Use this template

### 2) Personalize the Project

- Rename the project in this README.
- Fill in the description, inputs/outputs, and known issues.
- Replace sample files in `src/` and `test/` with your implementation.
- **Modify** this README as your project evolves.

### 3) Branching & Commits (Recommended Workflow)

```bash
# Create a feature branch
git checkout -b feature/<short-name>
# Work & commit small, focused changes
git add .
git commit -m "feat: short description"
# Push and open a Pull Request (PR)
git push -u origin feature/<short-name>
```


### 4) Give the TA Access to Your Fork

> **Required for grading.** Add the TA as a **collaborator** to *your forked repository*.

1. On GitHub, open **Settings → Collaborators** (or **Settings → Collaborators and teams**).
2. Click **Add people**, enter the TA's GitHub username (IlKaLUT), choose **Write** access (or as instructed), and **Add**.
3. If the repo is **private**, ensure the TA accepts the email invite.
4. (Optional) If your course uses an organization, you may instead add the TA via **Manage access** or your course team. Follow the course's instructions if they differ.

> Also share the **repository URL** and, if required, the **commit/tag** of the submitted version.

---

## 📚 Documentation

- High-level design/usages: `doc/design.md`
- API docs: generate with Doxygen (currently not in use)

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

```bash
make test
```

---

## 🗂️ Version History

> *(Update this table as you progress. Use semantic versioning if possible.)*

| Version | Date       | Author         | Changes                                               |
|--------:|------------|----------------|-------------------------------------------------------|
| 1.0.0   | 2026-03-08 |                | Linked list struct, read file, write file             |
| 2.0.0   | 2026-03-15 |                | Binary tree struct                                    |
| 3.1.0   | 2026-03-21 | Otto Hongisto  | Balanced search tree struct, read file into BST       |
| 4.0.0   | 2026-03-29 | Jaakko Laitinen |Linked list sorting, adding a new node, removing a node|

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

