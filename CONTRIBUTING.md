# Contributing to C Projects Collection

[![Language: C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![Compiler: GCC](https://img.shields.io/badge/Compiler-GCC-A42E2B?style=for-the-badge&logo=gnu&logoColor=white)](https://gcc.gnu.org/)
[![PRs Welcome](https://img.shields.io/badge/PRs-Welcome-brightgreen?style=for-the-badge)](#how-to-contribute)
[![Repo](https://img.shields.io/badge/GitHub-Spandan2106%2FC--projects-181717?style=for-the-badge&logo=github)](https://github.com/Spandan2106/C-projects)

Thank you for your interest in contributing to **C Projects Collection**! Whether you are adding a new standalone C program, fixing a bug, or improving documentation, your contributions are welcome.

---

## 📋 Table of Contents

- [How to Contribute](#how-to-contribute)
- [Coding Guidelines](#coding-guidelines)
- [Reporting Issues](#reporting-issues)

---

## 🚀 How to Contribute

1. **Fork the repository** to your own GitHub account.
2. **Clone your fork** to your local machine:

   ```bash
   git clone https://github.com/Spandan2106/C-projects.git
   ```

3. **Navigate into the project directory** and create a new branch:

   ```bash
   cd C-projects
   git checkout -b feature-your-feature-name
   ```

4. **Add or modify your C code.** Keep programs lightweight, standalone, and easy to follow.

5. **Compile and test with GCC** using strict warning flags to ensure zero warnings or errors:

   ```bash
   gcc -Wall -Wextra -std=c11 -o output_name your_file.c
   ./output_name
   ```

6. **Stage and commit your changes** with a clear, descriptive message:

   ```bash
   git add .
   git commit -m "Add: brief description of the project or fix"
   ```

7. **Push your branch** to GitHub:

   ```bash
   git push origin feature-your-feature-name
   ```

8. **Open a Pull Request** against the `main` branch of [Spandan2106/C-projects](https://github.com/Spandan2106/C-projects) and explain what your changes do.

## 🧠 Coding Guidelines

- **Standard C:** Write clean, portable, standard C code (`C11` / `C99`) without unnecessary external dependencies.
- **Clean Compilation:** Verify that your code compiles cleanly with `-Wall -Wextra`.
- **Clear Logic & Comments:** Use clear variable names and add brief comments where non-obvious logic or data structures need explanation.
- **Keep Programs Self-Contained:** Each `.c` file in the collection should remain straightforward to compile and run on its own.
- **Update Documentation:** If you add a new project file, add it to the project table in `README.md`.

## 🐛 Reporting Issues

Found a bug, compiler warning, or have an idea for a new C mini-project?

1. Check the [Issues](https://github.com/Spandan2106/C-projects/issues) tab to see if it has already been reported.
2. Open a new issue with:
   - A clear, concise title.
   - Steps to reproduce the issue (or details of your suggestion).
   - Your OS and compiler version (e.g., Ubuntu Linux, `gcc --version`).
