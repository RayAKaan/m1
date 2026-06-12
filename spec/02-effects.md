# Effect Algebra — [Unnamed Language]

## 1. Overview

Effects are logical labels on propositions that touch physical reality. They form an algebraic structure over which the compiler can reason: commutativity, composition, ordering, and optimization boundaries.

An **effect** is not a runtime mechanism. It is a compile-time label stating: "This proposition's truth depends on physical state."

## 2. Effect Atoms

### 2.1 Primitive Effects

An effect atom is a triple: `(category, resource, details)`.

```
Effect ::= Category ( Resource )*

Category ::= Read | Write | Alloc | Free | IO | Time | Net
Resource ::= Name | StringLiteral
```

Examples:

```
Read(FS, "data.txt")       // reading a file
Write(FS, "log.txt")       // writing a file
Read(Net, "api.example.com") // HTTP request
Alloc(Mem)                 // memory allocation
Free(Mem)                  // memory deallocation
Time(Clock)                // reading current time
IO(Stdout)                 // stdout output
IO(Stdin)                  // stdin input
IO(Env)                    // environment variable access
Net(Socket, "8080")        // network socket
```

### 2.2 The Pure Effect

```
Pure                       // no effect; timeless proposition
```

`Pure` is the identity element of the effect algebra.

### 2.3 The Unknown Effect

```
IO                         // unknown/unspecified effect
```

`IO` is the conservative default. It commutes with nothing and is preserved through reduction. Used when the specific effect cannot be determined or for external functions.

### 2.4 Effect Structure

Effects form a poset (partially ordered set) by specificity:

```
IO (most general, least specific)
├── Read
│   ├── Read(FS)
│   │   └── Read(FS, path)
│   └── Read(Net)
│       └── Read(Net, url)
├── Write
│   ├── Write(FS)
│   │   └── Write(FS, path)
│   └── Write(Net)
│       └── Write(Net, url)
├── Alloc(Mem)
├── Free(Mem)
├── Time(Clock)
└── Net(Socket, port)
```

A more specific effect IS-A less specific effect: `Read(FS, "data.txt") <: Read(FS) <: Read <: IO`.

## 3. The Commutativity Matrix

### 3.1 Core Matrix

Two effects `E1` and `E2` **commute** if executing them in either order produces the same observable result. If they commute, the reduction engine may reorder or parallelize them.

| E1 \\ E2 | Pure | Read(r1) | Write(r1) | Read(r2) | Write(r2) | Alloc | Free | Time | IO |
|----------|------|----------|-----------|----------|-----------|-------|------|------|----|
| Pure | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| Read(r1) | ✓ | ✓ | ✗ if same | ✓ | ✓ | ✓ | ✓ | ✗ | ✗ |
| Write(r1) | ✓ | ✗ if same | ✗ if same | ✓ | ✓ | ✓ | ✓ | ✗ | ✗ |
| Read(r2) | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | ✗ | ✗ |
| Write(r2) | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | ✗ | ✗ |
| Alloc | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | ✗ | ✗ |
| Free | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | ✗ | ✗ |
| Time | ✓ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ |
| IO | ✓ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ |

### 3.2 Commutativity Rules (Formal)

```
Pure commutes with everything:
    Pure · E = E · Pure = E                              [Comm-Pure]

Read commutes with Read (same or different resource):
    Read(r) · Read(s) = Read(s) · Read(r)                [Comm-Read-Read]

Read commutes with Write to different resource:
    Read(r) · Write(s) = Write(s) · Read(r)    if r ≠ s  [Comm-Read-Write-Diff]

Read does NOT commute with Write to same resource:
    Read(r) · Write(r) ≠ Write(r) · Read(r)              [NoComm-Read-Write-Same]

Write does NOT commute with Write to same resource:
    Write(r) · Write(r) ≠ Write(r) · Write(r)            [NoComm-Write-Write-Same]

Write commutes with Write to different resource:
    Write(r) · Write(s) = Write(s) · Write(r)  if r ≠ s  [Comm-Write-Write-Diff]

Alloc and Free commute with Read and Write to different resources:
    Alloc · Read(r) = Read(r) · Alloc                    [Comm-Alloc-Read]
    Alloc · Write(r) = Write(r) · Alloc                  [Comm-Alloc-Write]

Alloc and Free commute with each other:
    Alloc · Free = Free · Alloc                          [Comm-Alloc-Free]

Time commutes with nothing (timestamps are order-sensitive):
    Time · E ≠ E · Time                      for any E    [NoComm-Time]

IO (unknown effect) commutes with nothing:
    IO · E ≠ E · IO                          for any E    [NoComm-IO]
```

### 3.3 Derived Commutativity

For effect sets (compound effects):

```
E = {e1, e2, ..., en}    F = {f1, f2, ..., fm}

E commutes with F iff every ei commutes with every fj.
```

### 3.4 Effect Ordering Constraints

Even when effects DO commute, the source order defines a **default** ordering. The compiler may reorder only when:
1. Effects commute (per the matrix)
2. No data dependency exists between the propositions
3. No @physical_constraint specifies ordering requirements

When effects do NOT commute, source order is preserved exactly.

## 4. Effect Composition

### 4.1 Union (Set Union)

Compound effects are sets of effect atoms.

```
Pure ∪ E = E
E ∪ Pure = E
Effect(e1) ∪ Effect(e2) = Effect({e1, e2})
```

### 4.2 Sequencing

```
E1 ; E2 = E1 ∪ E2    // effects accumulate
```

### 4.3 Parallel

```
E1 || E2 = E1 ∪ E2    if E1 commutes with E2
E1 || E2 = ⊥           if E1 does NOT commute with E2
```

If effects don't commute, parallel execution is invalid.

### 4.4 Composition Rules

```
read := Read(FS, "data.txt")
write := Write(FS, "data.txt")

read ; read      = {Read(FS, "data.txt")}       // same effect, idempotent
read ; other_read = {Read(FS, "data.txt"), Read(FS, "other.txt")}
read ; write     = {Read(FS, "data.txt"), Write(FS, "data.txt")}  // ordered
read || write    = ⊥  // invalid (same resource)

read ; alloc     = {Read(FS, "data.txt"), Alloc(Mem)}
read || alloc    = {Read(FS, "data.txt"), Alloc(Mem)}  // independent, parallel valid
```

## 5. Effect Propagation

### 5.1 Through Expressions

```
Pure expression:                  effect = Pure
Variable / Literal:               effect = Pure
Application of pure function:     effect = Pure
Application of effectful function: effect = callee.effect
Lambda:                           effect = body.effect

Γ ⊢ e : [E] T
─────────────────
effect(e) = E
```

### 5.2 Through Let Bindings

```
let x : [E1] T = expr; body
────────────────────────────
effect(let) = E1 ∪ effect(body)
```

### 5.3 Through Match

```
match expr {
    pattern1 → body1    // effect = E1
    pattern2 → body2    // effect = E2
}
────────────────────────
effect(match) = E1 ∪ E2
```

### 5.4 Effect Weakening

A pure proposition can be used where an effectful one is expected:

```
Pure <: IO
Pure <: Read
Read <: IO
Write <: IO

But NOT: IO <: Pure
```

## 6. Effect Boundaries (Membranes)

### 6.1 The Membrane Model

The proposition graph is partitioned at effect boundaries. Each membrane separates a pure region from an effect region.

```
Pure Region A:
    (can reduce freely)
    │
    ▼
[IO] Membrane: read_file("data.txt")
    │
    ▼
Pure Region B:
    (can reduce freely, using read value)
    │
    ▼
[IO] Membrane: write_file("out.txt", result)
    │
    ▼
Pure Region C:
    (can reduce freely)
```

### 6.2 Membrane Rules

```
1. Pure regions are maximally optimized (all 5 reduction rules apply)
2. Membrane nodes are opaque to the reducer (no elimination, reordering, delay)
3. Pure sub-expressions WITHIN membrane node arguments ARE reduced
4. Between non-commuting membranes: source order preserved
5. Between commuting membranes: parallel execution permitted
```

### 6.3 Eventual as One-Way Membrane

```
Eventual<T, E>    // value will become T (TRUE) or E (FALSE)

Pure transformations on Eventual values CAN be fused across the membrane:

    content : Eventual<FileContent, FileError> ← read_file("data.txt")
    upper : Eventual<String, FileError> ← content.map(_.to_upper)
    words : Eventual<List<String>, FileError> ← upper.map(_.split(" "))

    ↓ reduction fuses pure transformations:

    content : Eventual<FileContent, FileError> ← read_file("data.txt")
    words : Eventual<List<String>, FileError> ← content.map(c →
        c.to_upper.split(" "))
```

The fusion rule:

```
Γ ⊢ x : Eventual<T, E>    Γ ⊢ f : T → U    (f is pure)
───────────────────────────────────────────────────────  [Eventual-Fuse]
Γ ⊢ x.map(f) : Eventual<U, E>    // preserves the membrane
Γ ⊢ x.map(g).map(f) ≡ x.map(f ∘ g)    // fusion: one transformation
```

## 7. Physical Constraints

### 7.1 Declaring Physical Invariants

```
@physical_constraint
    fs."data.txt".immutable_during(current_scope)
```

This is a logical axiom about physical reality. The programmer asserts it. The compiler trusts it.

### 7.2 Under Constraint

```
Under: @physical_constraint fs."data.txt".immutable_during(s)

    a := Read(FS, "data.txt")      // at T1
    b := Read(FS, "data.txt")      // at T2

    // Under constraint, a ≡ b (same content)
    // CSE can merge into single read: a
```

The constraint changes the commutativity:
```
Read(FS, "data.txt") · Read(FS, "data.txt") = Read(FS, "data.txt")
    only under @physical_constraint that file is immutable
```

### 7.3 Constraint Responsibility

```
The programmer is responsible for physical truth.
The compiler is responsible for logical consistency.

If the programmer asserts a false physical constraint:
    The program is logically unsound.
    Behavior is undefined (like C's undefined behavior).

But unlike C: the constraint is explicitly stated, localized,
and can be audited. Every constraint is a first-class logical
proposition in the source.
```

## 8. Effect Checking Algorithm

```
analyse_effects(expr, context):
    match expr:
        Literal(_) | Variable(_) → Pure

        Lambda(params, body):
            body_effect = analyse_effects(body, context + params)
            return (params) → [body_effect] ret_type

        Apply(f, arg):
            f_effect = analyse_effects(f, context)
            if f_effect has effect E:
                return E
            else:
                return Pure

        Let(name, type, expr, body):
            expr_effect = analyse_effects(expr, context)
            body_effect = analyse_effects(body, context + (name, type))
            return union(expr_effect, body_effect)

        Match(scrutinee, arms):
            scrut_effect = analyse_effects(scrutinee, context)
            arm_effects = [analyse_effects(arm, context) for arm in arms]
            return union({scrut_effect} ∪ arm_effects)

        Record(fields):
            field_effects = [analyse_effects(f, context) for f in fields]
            return union(field_effects)

        FieldAccess(record, field):
            return analyse_effects(record, context)

        TypeAscription(expr, type):
            return analyse_effects(expr, context)
```

## 9. M₀ Subset

M₀ does NOT implement effect checking. All expressions are treated as pure. Effect labels are parsed but not analyzed.

M₀'s external declarations use a simple FFI without effect labels:

```
external "c_function_name" : (ArgType) -> RetType
```

The M₀ compiler calls C functions directly. No effect tracking. No purity guarantees.

Effect checking arrives in M₁ (the self-hosted compiler), which uses the full effect algebra described here.

## 10. Summary

```
Effect Labels: Logical tags on propositions touching physical reality
Commutativity: Determines reordering and parallelization validity
Membranes: Boundaries between pure and effectful regions
Constraints: Programmer-asserted physical invariants
Propagation: Effects flow through the expression tree
```

---

*For reduction semantics over effect boundaries, see `03-reduction.md`.*
