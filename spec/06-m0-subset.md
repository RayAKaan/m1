# M₀ Subset Definition — Bootstrap Compiler

## 1. Purpose

M₀ is the minimal subset of the language implemented by the bootstrap compiler (written in C). It exists only to compile the M₁ compiler (the real compiler, written in M₀ itself). Once self-hosting is achieved, the M₀ bootstrap is discarded.

**M₀ is not the product. M₀ is the scaffold.**

## 2. Design Principles

1. **Minimal:** Only features needed to compile the M₁ compiler
2. **Simple:** Easy to implement correctly in C (no complex algorithms)
3. **Explicit:** No type inference — all types annotated
4. **Safe enough:** Pattern exhaustiveness checked, but no linearity/effects
5. **Fast enough:** Must compile M₁ in reasonable time (target: < 1 minute)

## 3. Feature Matrix

| Feature | M₀ Status | Notes |
|---------|-----------|-------|
| **Base types** | ✓ | Int, Float, String, Char, Bool, Unit |
| **Record types** | ✓ | Named fields, no subtyping |
| **Sum types** | ✓ | Simple constructors, single parameter |
| **Function types** | ✓ | Non-dependent only |
| **Type parameters** | ✓ | e.g., `List(T)`, `Optional(T)` (by convention) |
| **Dependent types** | ✗ | M₁ feature |
| **Higher-kinded types** | ✗ | M₁ feature |
| **Linear types** | Parse only | Parsed, not checked. All values Persistent. |
| **Effect labels** | Parse only | Parsed, not checked. All functions pure. |
| **Eventual<T, E>** | ✗ | M₁ feature |
| **Quantifiers (∀, ∃)** | ✗ | M₁ feature |
| **Bidirectional (<->)** | ✗ | M₁ feature. Only <- (derivation) in M₀. |
| **Iff (<->) in expressions** | ✗ | M₁ feature |
| **Constraints (@invariant)** | ✗ | M₁ feature |
| **Pattern matching** | ✓ | With exhaustiveness checking |
| **Let bindings** | ✓ | Type annotation required |
| **Lambda abstraction** | ✓ | Parameter and return types annotated |
| **Recursion** | ✓ | Via `fn` declarations. Self-calls allowed. |
| **Type ascription** | ✓ | `expr : Type` |
| **Module system** | ✓ | Basic. Flat module structure. |
| **FFI (external)** | ✓ | `external "name" : (Args) -> Ret` for LLVM calls |
| **Infix operators** | ✓ | +, -, *, /, ==, !=, <, >, <=, >=, /\, \/, -> |
| **Lists** | ✓ | As built-in type `List(T)` |
| **Strings** | ✓ | Basic operations (length, concat, slice) |
| **Type inference** | ✗ | All types explicit |
| **Bidirectional checking** | ✓ | Infer + check modes as described in 01-types.md |
| **Reduction** | Partial | Beta reduction, constant folding, let simplification |
| **CSE** | ✗ | M₁ optimization |
| **Laziness** | ✗ | M₁ optimization |
| **Parallelism** | ✗ | M₁ feature |
| **Completeness** | Partial | Pattern coverage only |
| **Consistency** | ✗ | M₁ feature |
| **Memory management** | Arena | Compiler uses arenas. Output uses stack allocation. |
| **Code generation** | LLVM IR | Via LLVM-C API. Flat, unoptimized output. |

## 4. Exact Syntax

### 4.1 Complete M₀ Grammar

M₀ implements a subset of the PEG grammar defined in `00-grammar.peg`. The following rules are active in M₀:

```
// TOP LEVEL
Program        = Module*
Module         = 'module' Name '{' Declaration* '}'

Declaration    = TypeDecl / PropDecl / FnDecl / ExternDecl

TypeDecl       = 'type' Name '=' TypeExpr

PropDecl       = Name ':' TypeExpr '<-' Expr           // Derivation only
               / Name ':' TypeExpr                     // Signature only

FnDecl         = 'fn' Name '(' ParamList? ')' '->' TypeExpr Block

ExternDecl     = 'external' StringLiteral ':' TypeExpr  // FFI to C

// TYPES (same as full grammar but restricted rules)
TypeExpr       = Expr    // Same expression syntax

// EXPRESSIONS (all operators except <->)
Expr           = ImplExpr
ImplExpr       = DisjExpr ( '->' ImplExpr )?
DisjExpr       = ConjExpr ( '\/' DisjExpr )?
ConjExpr       = CmpExpr ( '/\' ConjExpr )?
CmpExpr        = AddExpr ( CmpOp AddExpr )?
AddExpr        = MulExpr ( AddOp AddExpr )?
MulExpr        = PreExpr ( MulOp MulExpr )?
PreExpr        = NotExpr / PostExpr
NotExpr        = 'not' PreExpr
PostExpr       = AtomExpr ( PostfixOp )*
PostfixOp      = '.' Name / '(' ExprList? ')' / ':' Expr

AtomExpr       = LiteralExpr / NameExpr / MatchExpr
               / LetExpr / LambdaExpr / RecordExpr
               / ListExpr / GroupExpr

// Everything below here is the same as the full grammar
// except: no QuantExpr, no IffExpr, no EffExpr
```

### 4.2 M₀ Type Formers

```
Base types:     Int, Float, String, Char, Bool, Unit
Record types:   { field1 : Type1, field2 : Type2, ... }
Sum types:      | C1(T1) | C2 | C3(T3) | ...
                (declared via 'type' with pipe syntax)
Function types: (ParamType) -> RetType
                (Non-dependent only. Parameter must be a single type
                 or a record type. Multiple params use records or currying.)
Type params:    List(Int), Optional(String), Map(String, Int)
                (By convention: surrounding the param type with parens)
```

### 4.3 Example M₀ Program

```
module Lists

-- A simple sum type
type Optional(T) = | Some(T) | None

-- A record type
type Pair(A, B) = {
    first  : A,
    second : B
}

-- A function declaration
fn head(list : List(T)) -> Optional(T) {
    match list {
        Cons(head, tail) -> Some(head)
        Nil              -> None
    }
}

-- A derived proposition
list_length : (list : List(T)) -> Int <- fn(list : List(T)) -> Int {
    match list {
        Cons(head, tail) -> 1 + list_length(tail)
        Nil              -> 0
    }
}

-- External function (FFI to C for bootstrap)
external "LLVMWrite" : (String) -> Int
```

## 5. M₀ Built-in Types and Functions

### 5.1 Built-in Type: List(T)

```
List(T) is provided as a built-in type with:

Constructors:
    Nil  : List(T)
    Cons : (T, List(T)) -> List(T)

Built-in functions (compiler intrinsics):
    list_length : (list : List(T)) -> Int
    list_map    : (list : List(T), f : (T) -> U) -> List(U)
    list_filter : (list : List(T), pred : (T) -> Bool) -> List(T)
    list_fold   : (list : List(T), init : U, f : (U, T) -> U) -> U
```

### 5.2 Built-in Type: String

```
String operations (compiler intrinsics):
    string_length  : (s : String) -> Int
    string_concat  : (a : String, b : String) -> String
    string_split   : (s : String, delim : String) -> List(String)
    string_slice   : (s : String, start : Int, end : Int) -> String
    string_eq      : (a : String, b : String) -> Bool
```

### 5.3 Built-in Type: Map(K, V)

```
Map is provided for the symbol table in the bootstrap compiler:

    map_empty : () -> Map(K, V)
    map_get   : (map : Map(K, V), key : K) -> Optional(V)
    map_set   : (map : Map(K, V), key : K, val : V) -> Map(K, V)
    map_contains : (map : Map(K, V), key : K) -> Bool
    map_keys  : (map : Map(K, V)) -> List(K)
```

## 6. M₀ Compiler Pipeline

### 6.1 Phases

```
Source file (.l0)
    │
    ▼
[Lexer / Parser]          → PEG-based recursive descent
    │                        Builds AST (arena allocated)
    ▼
[Scope Resolver]          → Resolves names to declarations
    │                        Builds symbol table (Map-based)
    ▼
[Type Checker]            → Bidirectional type checking
    │                        Hindley-Milner style (without inference)
    │                        Pattern coverage checking
    ▼
[Simplifier / Reducer]   → Beta reduction, constant folding
    │                        Let simplification
    ▼
[Code Generator]          → LLVM IR emission via C API
    │                        Flat, unoptimized
    ▼
[Linker]                  → Invokes system linker (ld)
    │
    ▼
Executable binary
```

### 6.2 Phase Descriptions

**Lexer / Parser:**
- Hand-written PEG parser or generated via a PEG parser generator
- Produces an AST of proposition nodes
- Each node is allocated from the parse arena
- Source locations tracked for error messages

**Scope Resolver:**
- Walks the AST to build a scope tree
- Resolves each name reference to its declaration
- Reports undefined names
- Built on Map<K,V> for symbol tables

**Type Checker:**
- Bidirectional: infer and check modes
- All types must be explicitly annotated (no inference beyond local propagation)
- Checks pattern exhaustiveness on match expressions
- Reports type mismatches with source locations

**Simplifier / Reducer:**
- Beta reduction: `(fn(x) { body })(arg) → body[arg/x]`
- Constant folding: `2 + 3 → 5`, `"ab" + "cd" → "abcd"`
- Let simplification: `let x = v; body → body[v/x]` when x used once
- Record field access: `{ f = v }.f → v`
- Match simplification: `match C(v) { C(x) → body } → body[v/x]`

**Code Generator:**
- Walks the reduced AST
- Emits LLVM IR for each node
- Calls LLVM-C API functions directly
- Uses stack allocation for all values
- Emits the LLVM module → object file → links with system linker

### 6.3 M₀ Error Handling

```
M₀ errors are reported as:

    [ERROR] <phase>: <file>:<line>:<col>: <message>
    [ERROR] <phase>: <file>:<line>:<col>:   <context>

    Examples:

    [Parser] main.l0:15:8: Unexpected token '}' in type declaration
    [Scope]  main.l0:23:5: Undefined name 'process_order'
    [Type]   main.l0:31:12: Type mismatch
        Expected: Int
        Found:    String (value is "hello")
    [Complete] main.l0:42:5: Incomplete match
        Missing cases: {Debit}
```

## 7. M₀ Compiler Architecture (C)

### 7.1 File Structure

```
src/
├── main.c              -- Entry point, phase orchestration
├── arena.h / arena.c   -- Arena allocator
├── lexer.h / lexer.c   -- Lexer / tokenizer
├── parser.h / parser.c -- PEG parser
├── ast.h               -- AST node definitions
├── scope.h / scope.c   -- Scope resolver
├── types.h             -- Type representation
├── checker.h / checker.c -- Type checker
├── reduce.h / reduce.c -- Reducer / simplifier
├── codegen.h / codegen.c -- LLVM IR code generator
├── error.h / error.c   -- Error reporting
└── utils.h / utils.c   -- Utility functions
```

### 7.2 Size Estimate

```
Component            Lines (C)     Notes
────────────────────────────────────────
Parser + AST          ~3,000       PEG recursion, AST building
Scope resolver        ~1,500       Symbol table, name resolution
Type checker          ~2,500       Bidirectional checking, coverage
Reducer               ~1,000       Beta reduction, constant folding
Code generator        ~3,000       LLVM-C API calls
Arena allocator         ~500       Bump allocation, block chaining
Error reporting         ~500       Source locations, message formatting
Utilities               ~500       String ops, list ops, map ops
LLVM-C bindings       ~1,500       FFI declarations for LLVM-C API
────────────────────────────────────────
TOTAL                ~14,000       Lines of C
```

### 7.3 LLVM-C API Usage

M₀ uses the LLVM-C API for code generation. The key functions are:

```c
// Module and context
LLVMModuleCreateWithName("module_name")
LLVMContextCreate()
LLVMDisposeModule()

// Types
LLVMInt32Type()
LLVMInt1Type()        // Bool
LLVMFloatType()
LLVMPointerType()     // String, List, references
LLVMFunctionType(param_types, param_count, is_vararg)
LLVMStructType(field_types, field_count, is_packed)

// Constants
LLVMConstInt(type, value, is_signed)
LLVMConstString(context, string, length, dont_null_terminate)
LLVMConstNull(type)

// Instructions
LLVMBuildAdd(builder, lhs, rhs, "name")
LLVMBuildSub(builder, lhs, rhs, "name")
LLVMBuildMul(builder, lhs, rhs, "name")
LLVMBuildICmp(builder, predicate, lhs, rhs, "name")
LLVMBuildBr(builder, block)
LLVMBuildCondBr(builder, cond, true_block, false_block)
LLVMBuildCall2(builder, fn_type, fn, args, arg_count, "name")
LLVMBuildAlloca(builder, type, "name")
LLVMBuildStore(builder, value, pointer)
LLVMBuildLoad2(builder, type, pointer, "name")
LLVMBuildExtractValue(builder, agg, index, "name")
LLVMBuildInsertValue(builder, agg, value, index, "name")
LLVMBuildPhi(builder, type, "name")

// Builder
LLVMCreateBuilder()
LLVMPositionBuilderAtEnd(builder, block)
LLVMDisposeBuilder()
```

## 8. M₀ Compilation of M₁

### 8.1 The Goal

The M₀ compiler must compile the M₁ compiler. The M₁ compiler is written in the M₀ subset, extended with:

- More library functions (string operations, list operations)
- The full AST definitions for the complete language
- All compiler phases (including those M₀ doesn't implement: effects, consistency, etc.)

M₁ is a program that, when compiled by M₀, produces a binary that:
1. Parses the FULL language (including features M₀ doesn't implement)
2. Type checks the FULL language
3. Checks completeness AND consistency
4. Performs full reduction
5. Generates optimized LLVM IR
6. Can compile ITSELF (self-hosting)

### 8.2 Bootstrapping Verification

```
1. Write M₁ compiler in M₀ subset
2. Compile with M₀ compiler     → produces m1-binary-v1
3. Compile M₁ source with m1-binary-v1   → produces m1-binary-v2
4. Compare m1-binary-v1 and m1-binary-v2
    - If identical: bootstrap verified ✓
    - If different: inconsistency detected, debug
```

### 8.3 The Thermometer Principle

```
The M₁ compiler implements features it doesn't USE:

    M₁ implements:
    - Dependent types     (but M₁ is written in simple types)
    - Effect tracking     (but M₁ uses no effects in pure phases)
    - Linear types        (but M₁ uses arena allocation)
    - Consistency checker (but M₁'s own consistency is unchecked)
    - Full reduction      (but M₁ is compiled by M₀'s simple reducer)

    "A thermometer doesn't need to be hot to measure heat."
```

## 9. Development Timeline

### 9.1 Phase 1: C Bootstrap (Months 0–6)

```
Goal: M₀ compiler written in C

Milestones:
    Month 1:  Lexer + Parser working. Can parse M₀ programs. Build AST.
    Month 2:  Type checker working. Can type-check M₀ programs.
    Month 3:  Reducer + Code generator working.
              Can produce executable that prints "hello, world".
    Month 4:  Working compiler for M₀ programs.
              Can compile small programs (math, string ops, list ops).
    Month 5:  Compiler can compile itself (no, the C compiler compiles M₀).
              But M₀ can compile moderate-sized programs.
    Month 6:  M₁ compiler written in M₀, compiled by M₀.
              Produces m1-binary-v1.
```

### 9.2 Phase 2: Self-Hosting (Months 6–18)

```
Goal: M₁ compiler written in M₁, verified self-hosting

Milestones:
    Month 6-8:   M₁ compiler works. Full language features implemented.
    Month 9:     m1-binary-v1 compiles M₁ source → m1-binary-v2
    Month 10:    Self-hosting verified (v1 == v2)
    Month 12:    Dependent types working. Compiler uses dependent types.
    Month 14:    Effect tracking + consistency checker working.
    Month 16:    Full reduction with CSE, laziness, parallelism.
    Month 18:    M₁ compiler is production-quality.
```

### 9.3 Phase 3: Runtime + Standard Library (Months 18–30)

```
Goal: Full systems language with runtime, stdlib, concurrency

Milestones:
    Month 18-20: Linear memory manager runtime
    Month 20-22: I/O boundary system (Eventual<T,E>)
    Month 22-24: Concurrency runtime (dependency-driven execution)
    Month 24-26: Standard library (collections, I/O, networking)
    Month 26-28: Package manager and tooling
    Month 28-30: Production release (self-hosting, documented)
```

## 10. Potential M₀ Simplifications

### 10.1 Simplify: No Recursion in Parser

If the PEG grammar is complex, the parser can be simpler:

```
// Instead of full left-recursion handling, use:
// 1. Pratt parsing for expressions (precedence climbing)
// 2. Recursive descent for declarations
// 3. No parser generator — hand-written

Pratt parsing handles expressions with operator precedence
efficiently and is straightforward to implement in C.
```

### 10.2 Simplify: Single Pass Type Checker

```
Instead of building a full type inference engine:

1. Walk declarations in order
2. For each declaration:
    a. Look up previously declared names
    b. Check the body against the declared type
    c. Add the name to the environment
3. All types are explicit: never infer from usage
   (only infer from literal values and annotations)
```

### 10.3 Simplify: Flat Code Generation

```
Instead of optimizing LLVM IR:

1. Generate flat, simple IR
2. Every variable gets an alloca (stack slot)
3. Every store/load is explicit
4. No LLVM optimization passes
5. Let LLVM's -O2 handle optimization

This simplifies the code generator dramatically.
M₀ generates correct code. LLVM makes it fast.
```

### 10.4 Simplify: No Module System

```
If modules add complexity, flatten everything:

1. All declarations are global
2. Name collisions are errors
3. No module-scoped visibility
4. Module keyword is parsed but namespace is flat

The M₁ compiler can implement proper modules.
```

## 11. Testing M₀

### 11.1 Test Strategy

```
1. Unit tests for each compiler phase (C level)
    - Parser: parse strings → check AST
    - Type checker: type programs → expect pass/fail
    - Code generator: compile → run → check output

2. Integration tests (program level)
    - Write M₀ programs
    - Compile with M₀ compiler
    - Run the resulting executable
    - Check output matches expected

3. Self-compilation tests (meta level)
    - M₀ compiler compiles a program
    - M₁ compiler (compiled by M₀) compiles the same program
    - Compare outputs
```

### 11.2 Example Test Cases

```
// test_001_hello.l0 — basic program
module Hello
fn main() -> Int {
    print("hello, world")
    0
}

// test_010_fibonacci.l0 — recursive function
module Fibonacci
fn fib(n : Int) -> Int {
    match n == 0 {
        true  -> 0
        false -> match n == 1 {
            true  -> 1
            false -> fib(n - 1) + fib(n - 2)
        }
    }
}
fn main() -> Int {
    fib(10)  -- should output 55
}

// test_020_incomplete_match.l0 — should fail
module BadMatch
type Color = | Red | Green | Blue
fn describe(c : Color) -> String {
    match c {
        Red  -> "red"
        Blue -> "blue"
        -- Missing: Green → compile error expected
    }
}
```

## 12. Summary

```
M₀ is the bootstrap subset:

    Types:          Int, Float, String, Char, Bool, Unit,
                    records, sum types, List, Map, function types
    Expressions:    literals, variables, let, lambda, application,
                    match, record construction/access, list literal,
                    all operators (except <->, forall, exists)
    Declarations:   type, prop (derivation and signature), fn, external
    Checking:       bidirectional type checking, pattern coverage
    Reduction:      beta, constant folding, let simplification
    Code gen:       LLVM IR via LLVM-C API, flat output
    Memory:         arena allocation in compiler, stack in output

M₀ excludes:
    Dependent types, quantifiers, effects, invariants,
    deep completeness, consistency checking, CSE,
    laziness, parallelism, linear types, Eventual<T,E>

M₀ exists to compile M₁. M₁ is the real compiler.
M₀ is discarded after self-hosting.
```

---

*For the full grammar, see `00-grammar.peg`. For the compiler architecture, see the bootstrap plan document.*
