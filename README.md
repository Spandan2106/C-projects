# C Projects Collection

[![Language: C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![Compiler: GCC](https://img.shields.io/badge/Compiler-GCC-A42E2B?style=for-the-badge&logo=gnu&logoColor=white)](https://gcc.gnu.org/)
[![Platform: CLI](https://img.shields.io/badge/Platform-CLI%20%7C%20Console-2EA44F?style=for-the-badge)](#building--running)
[![Repo](https://img.shields.io/badge/GitHub-Spandan2106%2FC--projects-181717?style=for-the-badge&logo=github)](https://github.com/Spandan2106/C-projects)

A collection of lightweight, standalone C programs demonstrating core programming concepts, data structure visualizations, file handling, and interactive command-line console applications.

---

## 📋 Table of Contents
- [Overview](#overview)
- [Included Projects](#included-projects)
- [Key Concepts Covered](#key-concepts-covered)
- [Prerequisites](#prerequisites)
- [Building & Running](#building--running)
- [Contributing](#contributing)
- [License](#license)

---

## 🌟 Overview
This repository contains standalone mini-projects written in standard C. Each file is self-contained and designed for quick compilation and terminal execution, making it a practical reference for:
* File I/O operations and record persistence in C
* Data structures and tree visualization
* Menu-driven CLI applications and input/state handling

---

## 📂 Included Projects

| Source File | Project Name | Description |
| :--- | :--- | :--- |
| `atm.c` | ATM Simulation | Basic ATM machine interface supporting balance checks and cash withdrawals. |
| `bank.c` | Bank Management System | Console-based bank account management system for handling user records. |
| `binarytrrevisulizer.c` | Binary Tree Visualizer | Binary tree structure visualization and traversal tool. |
| `bus.c` | Bus Reservation System | Console logic for seat/bus reservation management. |
| `calculator.c` | CLI Calculator | Command-line calculator for arithmetic operations. |
| `contactbook1.c` | Contact Book | Contact management utility to store, search, and delete entries. |

---

## 🧠 Key Concepts Covered
* **Control Flow & Menus:** Interactive loops, `switch` statements, and state transitions.
* **Data Structures:** Tree structures and structured records (`struct`).
* **File Handling:** Reading and writing persistent data from the terminal.
* **Compiler Warnings & Safety:** Writing clean C code that compiles cleanly with strict warning flags.

---

## ⚙️ Prerequisites
To compile and run these programs locally, install a standard C compiler:
* **Linux / macOS:** `gcc` or `clang`
* **Windows:** **MinGW** / **MSYS2** or WSL

Verify your compiler installation:
```bash
gcc --version
```
## 🛠️ Building & Running
Each ```.c``` file is standalone and can be compiled directly with ```gcc```.

1. Compile a Specific Project
```Bash
gcc -Wall -Wextra -std=c11 -o atm atm.c
```
2. Run the Compiled Binary
On Linux / macOS:

```Bash
./atm
```
On Windows (PowerShell / Command Prompt):

```DOS
.\atm.exe
```
3. Quick Compile Examples for Other Files
```Bash
gcc -Wall -Wextra -std=c11 -o bank bank.c
gcc -Wall -Wextra -std=c11 -o tree binarytrrevisulizer.c
gcc -Wall -Wextra -std=c11 -o bus bus.c
gcc -Wall -Wextra -std=c11 -o calc calculator.c
gcc -Wall -Wextra -std=c11 -o contacts contactbook1.c
```
## 🤝 Contributing
Contributions, bug fixes, and improvements to existing console utilities are welcome. Feel free to fork the repository, make your changes on a branch, and open a pull request.

## 📄 License
This project is open-source. Add a ```LICENSE``` file (such as MIT) to the repository if you want to specify explicit reuse terms.
