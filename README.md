# Compiler Front-End

> **Academic Project:** Developed as part of the "Compilers" coursework.

This repository contains the implementation of a compiler front-end. It serves as the first major phase of a custom compiler, responsible for analyzing raw source code, validating its structure and meaning, and translating it into an Abstract Syntax Tree (AST) for further downstream processing or code generation.

## Core Components

This front-end pipeline implements the three standard phases of analysis:

1. **Lexical Analysis (Scanner/Lexer)**
   * Reads the raw source code character by character.
   * Groups characters into meaningful sequences called **Tokens**.
   * Strips out whitespace and comments.
   * *Implemented using: [e.g., Flex, ANTLR, custom C++ lexer]*

2. **Syntax Analysis (Parser)**
   * Consumes the token stream from the Lexer.
   * Verifies that the tokens form valid expressions according to the language's Context-Free Grammar (CFG).
   * Constructs a Parse Tree / Abstract Syntax Tree (AST).
   * *Implemented using: [e.g., Bison, Yacc, Recursive Descent Parser]*

3. **Semantic Analysis**
   * Traverses the AST to check for semantic consistency.
   * Manages the **Symbol Table** to track variable declarations and scope.
   * Performs type checking (e.g., ensuring you cannot add an integer to a boolean).
   * Catches errors like undeclared variables or function call mismatches.
