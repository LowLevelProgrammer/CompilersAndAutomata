# CompilersAndAutomata

*A practical exploration of Automata Theory, Formal Languages, Parsing, and Compiler Design through incremental implementations.*

---

## Overview

This repository is a structured, implementation-oriented study of concepts from:

- **Theory of Computation**
- **Formal Languages & Automata**
- **Compiler Design**
- **Parsing Theory**

The primary goal of this repository is learning and experimentation — understanding how formal language theory connects to real parsing systems and compiler components through hands-on implementations.

Rather than building a production-grade compiler, this project focuses on exploring the underlying ideas incrementally and systematically.

```text
Language → Grammar → Machine → Parser
```

---

## Motivation

Many concepts in ToC and Compiler Design remain highly theoretical during coursework.  
This repository aims to bridge that gap by implementing the core ideas from scratch and studying how they relate to actual language processing systems.

The focus is on questions such as:

- Why are DFAs used for lexical analysis?
- Why are stacks necessary for parsing context-free languages?
- How do LL and LR parsers differ internally?
- Why does left recursion affect top-down parsers?
- How are grammars transformed into executable parsing procedures?

---

## Current Scope

This repository is intentionally modular and incremental.

At the moment, the focus is primarily on:
- finite automata,
- lexical analysis,
- top-down parsing,
- and bottom-up parsing.

Additional topics may be explored gradually over time as the project evolves.

---

## Topics

### Automata
- DFA
- NFA
- ε-NFA
- DFA Minimization
- Regex → Automata Conversion

### Lexical Analysis
- Tokenization
- Regex-based scanning
- Lexer construction

### Parsing

#### Top-Down Parsing
- Recursive Descent Parsing
- LL(1) Parsing
- FIRST/FOLLOW computation
- Parse Table Construction

#### Bottom-Up Parsing
- Shift-Reduce Parsing
- LR(0)
- SLR(1)
- (Planned) LALR(1)

### Pushdown Automata
- PDA Simulation
- CFG ↔ PDA correspondence

### Possible Future Extensions
- Abstract Syntax Trees
- Semantic Analysis
- Intermediate Representations
- Tiny Interpreters / Compilers
