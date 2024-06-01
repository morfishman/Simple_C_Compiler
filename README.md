# Simple C Programming Language Compiler
## Check Out The Project Book Book
For a detailed document, [Book the PDF version](Compiler%20Book.pdf).

**Author:** Mor Fishman  
**Date:** May 2024

## Book Table of Contents

1. [Introduction](#introduction)
2. [Abstract](#abstract)
3. [Key Concepts](#key-concepts)
4. [Lexical Analysis](#lexical-analysis)
5. [Syntax Analysis](#syntax-analysis)
6. [Semantic Analysis](#semantic-analysis)
7. [Intermediate Code Generation](#intermediate-code-generation)
8. [Optimization](#optimization)
9. [Code Generation](#code-generation)
10. [Linking](#linking)
11. [Debugging](#debugging)
12. [Development Tools](#development-tools)
13. [Project Description](#project-description)
14. [Language Building Blocks](#language-building-blocks)
15. [Language Features](#language-features)
16. [Language Grammar](#language-grammar)
17. [Theoretical Background](#theoretical-background)
18. [Compiler Processes](#compiler-processes)
19. [Automata and Formal Language](#automata-and-formal-language)
20. [Problem Description and Algorithm Analysis](#problem-description-and-algorithm-analysis)
21. [Strategy and Algorithms](#strategy-and-algorithms)
22. [Detailed Component Design](#detailed-component-design)
23. [Development Environment](#development-environment)
24. [Main Algorithm](#main-algorithm)
25. [User Guide](#user-guide)
26. [Bibliography](#bibliography)


## Introduction

This project entails the design and implementation of a compiler that translates C code into 32-bit assembly language. The compiler ensures the syntactic and semantic correctness of the source file and generates efficient and accurate assembly code.

## Abstract

The project involves creating a compiler that operates on three levels: lexical, syntactical, and semantic. The lexical level identifies the basic elements of the language, the syntactical level arranges these elements into meaningful sequences, and the semantic level ensures the sequences are meaningful. The primary goal is to understand compiler construction deeply and build an efficient compiler from scratch.

## Key Concepts

- **Lexical Analysis:** Converts the source code into tokens.
- **Syntax Analysis:** Arranges tokens into a syntax tree representing the code structure.
- **Semantic Analysis:** Verifies the syntactical structure for semantic correctness.
- **Intermediate Code Generation:** Produces an intermediate code representation.
- **Optimization:** Enhances code efficiency.
- **Code Generation:** Converts intermediate code to machine code.
- **Linking:** Combines machine code with libraries to produce an executable.

## Lexical Analysis

In this phase, the source code is scanned and broken down into the smallest meaningful units called tokens.

## Syntax Analysis

This phase constructs a syntax tree from the tokens, representing the grammatical structure of the source code.

## Semantic Analysis

This phase ensures the syntax tree adheres to the language's semantic rules, checking for type errors and ensuring correct usage of variables and functions.

## Intermediate Code Generation

Generates an intermediate representation of the code that is independent of the target machine.

## Optimization

Enhances the intermediate code by improving its execution efficiency and reducing resource usage.

## Code Generation

Transforms the optimized intermediate code into target-specific machine code.

## Linking

Combines the generated machine code with other object files and libraries to create a complete executable.

## Debugging

Covers techniques and tools for debugging the compiler and the generated code, ensuring correctness and performance.

## Development Tools

Lists the tools and environments used in the compiler's development, including IDEs, libraries, and other resources.

## Project Description

Describes the design and implementation of the simple C compiler, detailing each phase of the compilation process from lexical analysis to code generation, along with theoretical and practical considerations.

## Language Building Blocks

- **Constants:** Fixed values directly embedded in the code.
- **Variables:** Named storage locations for data.
- **Functions:** Reusable code blocks that perform specific tasks.
- **Expressions:** Combinations of operators, variables, and constants that produce a value.
- **Statements:** Instructions that perform actions.

## Language Features

Details the features and capabilities of the simple C programming language supported by the compiler.

## Language Grammar

Defines the grammar rules governing the structure and syntax of the simple C programming language.

## Theoretical Background

Provides the theoretical underpinnings of compiler construction, including formal language theory and automata theory.

## Compiler Processes

Describes the various processes involved in compilation, such as parsing, type checking, and code generation.

## Automata and Formal Language

Explains the role of automata and formal languages in the design and implementation of the compiler.

## Problem Description and Algorithm Analysis

Presents the problems addressed by the compiler and analyzes the algorithms used to solve them.

## Strategy and Algorithms

Outlines the strategic approach and algorithms used in the compiler's implementation.

## Detailed Component Design

Provides a detailed design of the compiler's components, including data structures and algorithms.

## Development Environment

Describes the development environment and programming languages used in the project, focusing on tools and technologies.

## Main Algorithm

Presents the main algorithm of the compiler, detailing its steps and logic.

## User Guide

Provides comprehensive instructions on how to use the compiler, including setup, input requirements, and usage examples.

## Bibliography

Lists the references and resources used in the project.



