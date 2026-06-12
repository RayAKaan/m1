# Reduction Semantics — [Unnamed Language]

## 1. What Reduction Is

Reduction is NOT optimization. Reduction is **logical normalization** — transforming a proposition to its minimal equivalent form, the same way `x² − 1` reduces to `(x + 1)(x − 1)` in algebra. Same truth, simpler form.

```
Source proposition        → Reduced proposition
───────────────────────────────────────────────
λx.x + 1                  → λx.x + 1          (already minimal)
(λx.x + 1)(5)             → 6                 (beta reduction)
let x = 5*2; x + x        → 10 + 10 → 20     (constant folding + identity)
"hello" + " " + "world"   → "hello world"     (constant folding for strings)
```

Reduction is deterministic, terminating, and confluent (Church-Rosser property). The same program always reduces to the same normal form.

## 2. The Five Reduction Rules

### Rule 1: Identity Elimination

```
P → P    if P is identity                  [Reduce-Id]

fn(x : T) → T { x }    ≡    identity<T>

Application:
     identity<T>(v) → v
     identity(5) → 5
     identity(identity) → identity
```

Identity is detected structurally: a lambda whose body is exactly the parameter.

### Rule 2: Constant Folding

```
All operands are constants → result is constant   [Reduce-Const]

2 + 3 → 5
"hello" + " world" → "hello world"
true /\ false → false
not true → false
```

Applied to any pure proposition whose all sub-propositions are constants.

### Rule 3: Common Subexpression Elimination (CSE)

```
P appears twice in the same pure scope     [Reduce-CSE]
                                                        → compute P once, bind to name, reuse
P is pure (no effects)
─────────────────────
P + P → let _p = P; _p + _p
```

CSE only applies within a pure region (no intervening effect boundaries).

### Rule 4: Laziness (Demand-Driven Derivation)

```
P is only needed when condition C is true     [Reduce-Lazy]
                                                        → don't derive P unless C
P is pure
C is a proposition
─────────────────────
if C then f(P) else g()  →  if C then f(P) else g()
                                                (P is NOT derived when C is false)
```

Laziness falls out of the dependency structure automatically. The compiler does NOT add delay annotations. It analyzes which propositions are reachable under which conditions and defers accordingly.

### Rule 5: Parallelism (Independence)

```
P and Q share no logical dependencies      [Reduce-Par]
P and Q commute (both pure, or commuting effects)
─────────────────────
P; Q → P || Q
```

Parallelism is derived, not annotated. The dependency graph determines independence.

## 3. Reduction Relation

### 3.1 Small-Step Operational Semantics

```
e → e'    // e reduces to e' in one step
e →* e'   // e reduces to e' in zero or more steps (reflexive transitive closure)
e →! e'   // e reduces to e' in normal form (no further reductions possible)
```

### 3.2 Beta Reduction (Core)

```
(fn(x : T) → U { body })(a) → body[a/x]    [Beta]
```

The fundamental reduction rule. Application of a lambda substitutes the argument.

### 3.3 Eta Expansion

```
e : (x : T) → U(x)
────────────────────  [Eta]
e → fn(x : T) → U(x) { e(x) }
```

Eta expansion is not usually a reduction (it makes terms larger), but is used for normalization to eta-long form.

### 3.4 Let Flattening

```
let x = (let y = a; b); c → let y = a; let x = b; c    [Let-Flatten]

let x = v; x → v                                         [Let-Sink]
```

### 3.5 Match Simplification

```
match C_i(v) { ... C_i(x) → body ... } → body[v/x]    [Match-Simplify]
```

When the scrutinee is a known constructor, the match reduces to the corresponding arm.

```
match v { ... } → match v { ... }    (no reduction if v is a variable)    [Match-Stuck]
```

### 3.6 Record Destructuring

```
{ f1 = e1, f2 = e2, ... }.fi → ei    [Field-Access]
```

### 3.7 Reduction Context

```
e → e'
────────────────  [Ctx-App-Fun]
e(a) → e'(a)

e → e'
────────────────  [Ctx-App-Arg]
v(e) → v(e')

e → e'
──────────────────  [Ctx-Let-Bound]
let x = e; b → let x = e'; b

e → e'
────────────────  [Ctx-Let-Body]
let x = v; e → let x = v; e'

e → e'
──────────────────  [Ctx-Match-Scrut]
match e { arms } → match e' { arms }

e → e'
────────────────  [Ctx-Field]
e.f → e'.f
```

Reduction occurs under any context. The full expression is reduced to normal form.

## 4. The Membrane Model (Effect Boundaries)

### 4.1 Membrane Partitioning

The reducer partitions the proposition graph at effect boundaries.

```
Algorithm: partition(proposition_graph):
    1. Label each node with its effect (from effect analysis)
    2. Pure regions: maximally connected subgraphs of pure nodes
    3. Membrane nodes: individual [Effect(e)] nodes
    4. Boundaries: edges between pure regions and membrane nodes
    5. Return: alternating sequence (Pure Region, Membrane, Pure Region, ...)
```

### 4.2 Reduction Within Pure Regions

Inside a pure region, ALL five rules apply without restriction:

```
Eliminate identities
Fold constants
Merge common subexpressions
Defer unused derivations
Schedule independent propositions in parallel
```

### 4.3 Reduction at Membrane Boundaries

At a membrane node, the reducer is constrained:

```
Membrane node M with effect E:
    - Pure sub-expressions within M's arguments: REDUCED
    - M itself: PRESERVED (cannot be eliminated)
    - M's position: PRESERVED (cannot be reordered)
    - M's existence: PRESERVED (cannot be delayed)
```

### 4.4 Reduction Between Membranes

Between two membrane nodes `M1` (effect E1) and `M2` (effect E2):

```
if commutes(E1, E2):
    M1 || M2    // parallel execution permitted
else:
    M1 ; M2     // source order preserved
    M2 ; M1     // NOT valid
```

### 4.5 Formal Membrane Rule

```
reduce(proposition) → reduced_form:

if proposition.effect == Pure:
    apply all 5 rules freely
    return fully_reduced

if proposition.effect == Effect(e):
    let reduced = proposition
    reduced.args = [reduce(arg) for arg in proposition.args]  // reduce pure sub-expressions
    // reduced itself is unchanged
    return reduced

if combining P (effect E1) and Q (effect E2):
    if commutes(E1, E2):
        return reduce_in_parallel(P, Q)
    else:
        return reduce_in_order(P, Q)
```

## 5. Eventual Fusion

### 5.1 The One-Way Membrane

`Eventual<T, E>` is a one-way membrane: pure transformations pass through, effect boundaries do not.

```
Rule: Eventual-Fuse

content : Eventual<FileContent, FileError>
map_fn   : FileContent → String (pure)
upper    : Eventual<String, FileError> ← content.map(map_fn)

Fuses to:
    content : Eventual<FileContent, FileError>
    upper   : Eventual<String, FileError> ← content.map(compound_fn)

Where compound_fn = map_fn ∘ existing_map_fn
```

### 5.2 Fusion Rules

```
P.map(f).map(g) → P.map(g ∘ f)           [Fuse-Map]

P.map(f) → P                              if f = identity      [Fuse-Id]

P.map(f).map(g).map(h) → P.map(h ∘ g ∘ f)  [Fuse-Chain]
```

### 5.3 Fusion Boundary

Fusion stops at the first effectful transformation:

```
P.map(f1).map(f2).filter(pred).map(f3)
    where pred is effectful (e.g., reads current time)

→ P.map(f2 ∘ f1)                       // fuses f1, f2
  .filter(pred)                         // stops here (effect boundary)
  .map(f3)                              // separate
```

No fusion crosses an effect boundary.

## 6. The Physical Constraint Extension

### 6.1 Under Constraint: Enhanced CSE

```
@physical_constraint fs."data.txt".immutable_during(s)

a := Read(FS, "data.txt")    // T1
b := Read(FS, "data.txt")    // T2

→ a := Read(FS, "data.txt")  // single read
  ... use a twice              // second occurrence replaced with reference
```

Without the constraint, two reads of the same file do NOT fuse (they might return different content).

### 6.2 Constraint-Aware Commutativity

```
@physical_constraint fs."data.txt".immutable_during(s)

commutes(Read(FS, "data.txt"), Read(FS, "data.txt")) = true
    // only under this constraint
```

### 6.3 Constraint Scoping

```
@physical_constraint fs."data.txt".immutable_during(s)
{
    // Within this scope: CSE on reads of "data.txt" is valid
    let a = read_file("data.txt");
    let b = read_file("data.txt");
    // a and b may be merged
}
// Outside scope: no CSE
let c = read_file("data.txt");
// c is a separate read
```

## 7. Dependency Analysis

### 7.1 Dependency Graph Construction

```
Build dependency graph from proposition AST:
    Node = proposition
    Edge = "P depends on Q" if Q must be evaluated before P

Dependency types:
    Data dependency:       P uses value produced by Q
    Effect ordering:       P must execute after Q (non-commuting effects)
    Implicit dependency:   P references a name bound by Q
```

### 7.2 Independence Detection

```
independence(P, Q) →
    true if:
        1. P and Q share no variables (no data dependency)
        2. P and Q have commuting effects (no effect ordering)
        3. P and Q are not transitively dependent through any chain
    false otherwise
```

### 7.3 Parallelism Derivation

```
for each pair (P, Q) in dependency graph:
    if independence(P, Q):
        schedule(P) ≠ schedule(Q)    // may execute in parallel
    else:
        schedule(P) < schedule(Q)    // P before Q (or vice versa, based on deps)
```

## 8. The Reduction Algorithm (Complete)

```
function reduce(expr, context):
    // Step 1: Annotate effect labels
    annotate_effects(expr, context)

    // Step 2: Partition at effect boundaries
    regions = partition_at_membranes(expr)

    // Step 3: Reduce each region
    for each region in regions:
        if region.type == PURE:
            reduced = reduce_pure(region)
        else if region.type == MEMBRANE:
            reduced = reduce_membrane(region)
        else if region.type == EVENTUAL:
            reduced = fuse_eventual(region)

    // Step 4: Reconstruct
    result = compose_regions(reduced_regions)

    // Step 5: Normalize
    result = normalize(result)

    return result


function reduce_pure(region):
    // Apply all 5 rules until fixpoint
    changed = true
    while changed:
        changed = false
        for each reduction rule R in {Id, Const, CSE, Lazy, Par}:
            result = apply_rule(R, region)
            if result ≠ region:
                region = result
                changed = true
                break    // re-scan from top after each change
    return region


function reduce_membrane(membrane):
    // Only reduce pure sub-expressions within arguments
    for each arg in membrane.args:
        arg = reduce_pure(arg)
    // membrane itself untouched
    return membrane


function compose_regions(regions):
    // Order based on effect commutativity
    result = first_region
    for each next_region in regions[1:]:
        if commutes(result.effect, next_region.effect):
            result = par(result, next_region)
        else:
            result = seq(result, next_region)
    return result
```

## 9. Normalization

### 9.1 Normal Form

A proposition is in **normal form** when no reduction rule applies. This is the minimal logical form.

```
Normal form properties:
    - No beta-reducible applications
    - No constant-foldable sub-expressions
    - No duplicate pure sub-expressions (CSE applied)
    - No deferred derivations (laziness already encoded in dependency)
    - All independent propositions parallelized
    - All Eventual maps fused
    - All effect boundaries respected
```

### 9.2 Termination

```
Reduction always terminates because:
    1. Beta reduction reduces term size (strictly fewer applications)
    2. Constant folding reduces to literal (no further reduction)
    3. CSE introduces bindings but does not create new reduction opportunities
    4. Laziness removes unreachable sub-expressions
    5. Parallelism does not change term structure

Proof: The reduction relation → is strongly normalizing (every reduction sequence terminates).
The measure |e| = number of applications + number of operators strictly decreases
with each non-CSE reduction step, and CSE steps do not increase the measure.
```

### 9.3 Confluence (Church-Rosser)

```
If e →* e1 and e →* e2, then there exists e3 such that e1 →* e3 and e2 →* e3.

The reduction relation is confluent. Different reduction orders produce
the same normal form (up to renaming of introduced bindings).
```

## 10. Code Generation After Reduction

After reduction, the code generator emits LLVM IR:

```
Reduced proposition → LLVM IR:
    Pure region       → straight-line computation, fully optimized
    Membrane node     → function call to runtime API
    Parallel region   → parallel dispatch (thread pool or work-stealing)
    Sequential region → serial execution in determined order
```

The reduced form is minimal. The code generator does NOT perform additional optimization (LLVM's backend may, but the logical form is already optimal).

## 11. M₀ Subset

M₀ implements:
- Beta reduction (essential for evaluation)
- Constant folding (essential for performance)
- Let flattening and simplification
- Match simplification (known constructor)

M₀ does NOT implement:
- CSE (purely an optimization)
- Laziness analysis (all propositions eager)
- Parallelism derivation (single-threaded)
- Effect membranes (no effect system)
- Eventual fusion (no Eventual type)
- Physical constraint optimization

## 12. Summary

```
Reduction is logical normalization:
    Same truth, simpler form
    Deterministic, terminating, confluent

Five rules:
    1. Identity elimination
    2. Constant folding
    3. Common subexpression elimination
    4. Laziness
    5. Parallelism

Membrane boundaries limit reduction:
    Pure regions: fully reduced
    Effect nodes: preserved, arguments reduced
    Eventual: pure transformations fused

Result: minimal logical form → code generation
```

---

*For the effect system that governs membrane boundaries, see `02-effects.md`. For dependency analysis, see the compiler architecture document.*
