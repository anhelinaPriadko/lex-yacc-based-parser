# C++ Parser using Lex and Yacc (Flex & Bison)

This project is a simple **C++ parser** built using **Flex** (lexical analyzer) and **Bison** (syntax analyzer).  
It parses C++ source code and generates an **Abstract Syntax Tree (AST)** in **JSON format**.  
The resulting `ast.json` file can be visualized using **D3.js** in the provided `index.html` page.

---

## How to Run

### 1. Build the project
Make sure you have **Flex**, **Bison**, and **g++** installed.  
Then open the terminal in the project folder and run:

```bash
make clear
make

### 2. Build the project
Run parser executable to generate ast.json with the result
```bash
./parser test.cpp
