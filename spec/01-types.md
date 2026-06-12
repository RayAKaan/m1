# Type System Specification — [Unnamed Language]

## 1. Types Are Propositions

Every type is a proposition. Every value of that type is a proof of that proposition. This is the Curry-Howard correspondence, taken literally as the foundation of the language.

| Type (Proposition) | Value (Proof) |
|--------------------|---------------|
| `Int`              | A specific integer exists |
| `NonZero`          | An integer exists AND it ≠ 0 |
| `(x: T) → U`       | For all x of type T, there exists a U |
| `{ f: T, g: U }`   | A pair (T AND U) exists |
| `\| A(T) \| B \|`    | Either T exists (tagged A) or Unit exists (tagged B) |

You cannot construct a value of a type that contradicts its proposition. This is enforced not by runtime checking or compile-time verification, but by **logical necessity** — the construction would be a logical contradiction, which cannot exist.

## 2. Judgments

The type checker proves judgments of these forms:

```
Γ ⊢ e ⇒ T          // In mode: expression e INFERS type T
Γ ⊢ e ⇐ T          // Check mode: expression e HAS type T (is checked against T)
Γ ⊢ S <: T         // S is a subtype of T
Γ ⊢ T ≡ T'         // T is definitionally equal to T'
Γ ⊢ T type         // T is a valid type
Γ ⊢ ctx            // Γ is a valid context
Γ ⊢ T → T'         // T reduces to T' (computation rule)
```

## 3. The Four Logical States

EVERY type in the system is in exactly one logical state. These states are tracked statically by the type checker, not at runtime.

| State | Meaning | Operations allowed |
|-------|---------|--------------------|
| TRUE | Type is inhabited. A value exists and can be used. | All operations |
| FALSE | Type is uninhabited. No value can exist. | Elimination only (ex falso) |
| UNKNOWN | Not yet determined. The type may be TRUE or FALSE. | Must resolve before use |
| UNDEFINED | Outside the domain of discourse. Logically meaningless. | None — compile error |

### State Transition Rules

```
Γ ⊢ T TRUE          Γ ⊢ T TRUE
──────────────       ─────────────
Γ ⊢ T <: T          Γ ⊢ T → T

Γ ⊢ T TRUE          Γ ⊢ T ≡ T'
────────────────────────────────
Γ ⊢ T' TRUE

Γ ⊢ FALSE <: T      (ex falso: from false, anything follows)
```

UNDEFINED propagates:
```
Γ ⊢ expr : T    T ≡ UNDEFINED
──────────────────────────────
Compile error: "proposition outside domain of discourse"
```

UNKNOWN must be resolved:
```
Γ ⊢ expr : T    T UNKNOWN
──────────────────────────
Compile error: "cannot use UNKNOWN proposition"
"must resolve to TRUE or FALSE before use"
```

For the M₀ subset: only TRUE and FALSE are tracked. UNKNOWN is treated as a compile error for simplicity. Full UNKNOWN handling arrives in M₁.

## 4. Base Types and Type Formers

### 4.1 Base Types

```
Int           Proves: an integer exists
Float         Proves: a float exists
String        Proves: a string exists
Char          Proves: a character exists
Bool          Proves: exists true or false
Unit          Proves: unit exists (trivial truth)
```

### 4.2 Function Types (Pi Types)

```
(x: T) → U    Proves: for all x of type T, there exists a U(x)
```

If `x` does not appear free in `U`, this is a simple function type `T → U` (non-dependent).

### 4.3 Record Types (Sigma Types)

```
{ f1: T1, f2: T2, ... }    Proves: a tuple of T1 AND T2 AND ... exists
```

### 4.4 Sum Types

```
| C1(T1) | C2(T2) | ...    Proves: exists either a T1 (tagged C1) OR T2 (tagged C2) OR ...
```

The leading `|` is required syntax. A sum with one constructor `| C(T)` is isomorphic to `T`.

### 4.5 Type Constructors (Parameterized Types)

```
List(T)       Parameterized: for any type T, a list of T
Optional(T)   Parameterized: for any type T, either Some(T) or None
```

Type constructors are functions at the type level:
```
List : (T: Type) → Type
```

### 4.6 Dependent Types

```
List(T, n)    Proves: a list of exactly n elements of type T exists
```

The type `List(T, n)` depends on the VALUE n. `n` must have a type (e.g., `Nat`).

Dependent function type:
```
(x: T) → U(x)    Proves: for all x : T, a U(x) exists
                                         (U depends on the value of x)
```

### 4.7 Linear Types

```
Linear<T>        Must be used exactly once
Affine<T>        Must be used at most once
Persistent<T>    May be used any number of times (immutable)
```

### 4.8 Eventual Types

```
Eventual<T, E>   Proves: will become true (T) or false (E)
                 Current state: UNKNOWN
```

Eventual is a proposition whose truth value depends on physical reality (time, I/O, external state).

### 4.9 Effect-Annotated Types

```
[IO] T           Proves: T exists, but depends on physical reality
[Read FS "f"] T  Proves: T exists, depends on reading file "f"
```

Effect annotations on types indicate that the proposition's truth depends on physical state.

## 5. Context and Environment

```
Γ ::= ∅                          Empty context
    | Γ, x : T                   Variable binding
    | Γ, x : T ≡ v               Variable with definitional equality
    | Γ, @invariant P            Invariant proposition
    | Γ, @physical_constraint P  Physical constraint
```

Context is ordered. Later entries may depend on earlier entries.

### Context validity

```
──────────
∅ ⊢ ctx

Γ ⊢ ctx    Γ ⊢ T type    x ∉ dom(Γ)
─────────────────────────────────────
Γ, x : T ⊢ ctx
```

## 6. Bidirectional Type Checking Rules

The type checker operates in two modes:
- **Inference** (e ⇒ T): the expression's type is inferred from its structure
- **Checking** (e ⇐ T): the expression is checked against a known type

The checker alternates between modes based on the syntactic form.

### 6.1 Variables

```
Γ ⊢ ctx    x : T ∈ Γ
─────────────────────   [Var-Infer]
Γ ⊢ x ⇒ T
```

Variables always infer. The type is looked up in context.

### 6.2 Literals

```
─────────────  [Int]
Γ ⊢ n ⇒ Int

───────────────  [Float]
Γ ⊢ f ⇒ Float

───────────────  [String]
Γ ⊢ s ⇒ String

───────────────  [Char]
Γ ⊢ c ⇒ Char

──────────────────  [Bool]
Γ ⊢ b ⇒ Bool

───────────  [Unit]
Γ ⊢ {} ⇒ Unit
```

All literals infer their types directly.

### 6.3 Lambda Abstraction

```
Γ, x : A ⊢ body ⇐ B    x may appear free in B
──────────────────────────────────────────────  [Lam-Check]
Γ ⊢ fn(x : A) → B { body } ⇐ (x : A) → B
```

Lambdas are checked against a known function type. The parameter type comes from the annotation; the return type is checked against the annotation.

If no type annotation is available (infer mode), the lambda cannot be fully checked without annotations on parameters:

```
Γ, x : A ⊢ body ⇐ B
────────────────────────  [Lam-Infer]  (requires parameter type annotation)
Γ ⊢ fn(x : A) → B { body } ⇒ (x : A) → B
```

> **M₀ rule:** Parameter types and return types MUST be annotated on all lambdas. No inference of function types.

### 6.4 Application

```
Γ ⊢ f ⇒ (x : A) → B    Γ ⊢ a ⇐ A
──────────────────────────────────  [App-Infer]
Γ ⊢ f(a) ⇒ B[a/x]
```

Application infers the function's type, checks the argument against the parameter type, and substitutes the argument into the return type (dependent application).

Multiple arguments desugar: `f(a, b, c)` → `f(a)(b)(c)`.

### 6.5 Let Binding

```
Γ ⊢ expr ⇐ A    Γ, x : A ⊢ body ⇒ B
─────────────────────────────────────  [Let-Infer]
Γ ⊢ let x : A = expr; body ⇒ B
```

The bound variable is available in the body. The type annotation is required.

> **M₁:** Type annotation may be omitted if `expr` infers its type.

### 6.6 Record Construction

```
Γ ⊢ e_i ⇐ T_i    (for all i)
─────────────────────────────  [Record-Check]
Γ ⊢ { f_1 = e_1, ..., f_n = e_n } ⇐ { f_1 : T_1, ..., f_n : T_n }
```

Records check against the expected record type. Field order is semantically irrelevant but syntactically preserved.

```
Γ ⊢ e_i ⇒ T_i    (for all i)
─────────────────────────────  [Record-Infer]
Γ ⊢ { f_1 = e_1, ..., f_n = e_n } ⇒ { f_1 : T_1, ..., f_n : T_n }
```

Without a target type, record types are inferred from field types.

### 6.7 Field Access

```
Γ ⊢ e ⇒ { ..., f : T, ... }
─────────────────────────────  [Field-Infer]
Γ ⊢ e.f ⇒ T
```

### 6.8 Pattern Matching / Case Analysis

```
Γ ⊢ e ⇒ Σ                                    [Match-Check]
Σ has constructors { C_i : A_i } for i = 1..n
Σ is complete (all constructors covered)

For each i:
    Γ, x_i : A_i ⊢ body_i ⇐ T

─────────────────────────────────────────
Γ ⊢ match e { C_1(x_1) → body_1; ...; C_n(x_n) → body_n } ⇐ T
```

The match expression checks that:
1. The scrutinee's type is a sum type
2. All constructors are covered (exhaustiveness)
3. Each arm body has the same type `T`
4. Pattern variables are properly scoped

Exhaustiveness in M₀: simple constructor coverage.
Exhaustiveness in M₁: deep completeness (covered in spec/05-consistency.md).

```
Same premises, T inferred from first arm
───────────────────────────────────────── [Match-Infer]
Γ ⊢ match e { ... } ⇒ T
```

### 6.9 Type Ascription

```
Γ ⊢ e ⇐ T
──────────  [Ascribe-Infer]
Γ ⊢ (e : T) ⇒ T
```

Type ascription switches from check mode (on the expression) to infer mode (on the result). It's the primary way to provide type information to the checker.

### 6.10 List Literal

```
Γ ⊢ e_i ⇐ T    (for all i)
───────────────────────────  [List-Check]
Γ ⊢ [e_1, ..., e_n] ⇐ List(T)

Γ ⊢ e_i ⇒ T    (for all i, same T)
───────────────────────────────────  [List-Infer]
Γ ⊢ [e_1, ..., e_n] ⇒ List(T)
```

Empty list `[]` requires type ascription `[] : List(T)` since `T` cannot be inferred.

### 6.11 If Expression (Sugar)

```
if cond then a else b    ≡    match cond { true → a; false → b }
```

No special typing rule. Desugars before type checking.

## 7. Dependent Types

### 7.1 Dependent Function Type (Pi Type)

```
(x : T) → U(x)    // U may mention x
```

The type `U` depends on the value of the parameter `x`.

Dependent functions (lambdas) with explicit binding:
```
fn(x : T) → U(x) { body }
```

Where `body : U(x)` when `x : T`.

### 7.2 Dependent Application

```
Γ ⊢ f ⇒ (x : A) → B(x)    Γ ⊢ a ⇐ A
──────────────────────────────────────  [DApp-Infer]
Γ ⊢ f(a) ⇒ B(a)
```

The return type `B(a)` is obtained by substituting `a` for `x` in `B(x)`.

### 7.3 Dependent Type Formation

```
Γ ⊢ T type    Γ, x : T ⊢ U type
─────────────────────────────────  [Pi-Form]
Γ ⊢ (x : T) → U type
```

### 7.4 Definitional Equality for Dependent Types

```
Γ ⊢ a ≡ a' : T    Γ ⊢ B(a) type
────────────────────────────────  [Pi-Eq]
Γ ⊢ (x : T) → B(x) ≡ (x : T) → B(x)    // same if a ≡ a' for all a
```

In practice, definitional equality for dependent types requires:

```
Γ, x : T ⊢ B(x) ≡ B'(x)
─────────────────────────
Γ ⊢ (x : T) → B(x) ≡ (x : T) → B'(x)
```

### 7.5 Dependent Pattern Matching

In dependent pattern matching, matching on a scrutinee can refine type information in the branches:

```
match list {
    Nil       → ...  // here we know n ≡ 0
    Cons(h, t) → ... // here we know n ≡ n' + 1 where t : List(T, n')
}
```

This requires type refinement in pattern branches, implemented through **dependent case analysis** (elimination with motive).

> **M₀:** No dependent pattern matching. Simple sum type matching only.
> **M₁:** Full dependent pattern matching with type refinement.

## 8. Linear Types

### 8.1 Usage Modalities

```
Linear<T>       // must be used exactly once
Affine<T>       // must be used at most once
Persistent<T>   // may be used any number of times
```

### 8.2 Usage Rules

```
Γ ⊢ e : Linear<T>
──────────────────  [Linear-Use]
Γ ⊢ consume(e) : T    // consumes the linear resource

No other operation may duplicate or discard a Linear<T> value.
```

A linear value can be consumed in a function application:
```
consume_handle : Linear<Handle> → Result

let result = consume_handle(my_handle)
// my_handle is consumed here. Cannot be used again.
```

### 8.3 Subtyping Between Modalities

```
Linear(T) <: Affine(T)
```

A value that must be used exactly once can be treated as a value that may be used at most once. This is a safe coercion.

There is no subtyping between Affine and Persistent — they are structurally different:
- Affine: single ownership, can be moved/consumed
- Persistent: shared ownership, immutable, never consumed

### 8.4 Modality Promotion

```
Γ ⊢ e : T    T is not Linear or Affine
───────────────────────────────────────  [Promote-Persistent]
Γ ⊢ e : Persistent(T)
```

Pure values (Int, Bool, etc.) can be promoted to Persistent freely.

```
Γ ⊢ e : Affine(T)    e is used at most once in body
────────────────────────────────────────────────────  [Promote-Affine]
Γ ⊢ let x : Affine(T) = e; body : U
```

### 8.5 M₀ Rule

M₀ does NOT enforce linear types syntactically. All values are treated as Persistent. The linear type annotations are parsed but not checked. M₁ implements full linearity enforcement.

This means the M₀ bootstrap compiler does NOT track resource usage. Values can be duplicated, discarded, and used arbitrarily. Resource safety is added in M₁.

## 9. Effect Types

### 9.1 Effect-Annotated Function Types

```
(x : T) → [E] U    // Function that may perform effect E
(x : T) → U        // Pure function (no effects)
```

### 9.2 Effect Propagation

```
Γ ⊢ f ⇒ (x : A) → [E] B    Γ ⊢ a ⇐ A
───────────────────────────────────────  [App-Effect]
Γ ⊢ f(a) ⇒ [E] B[a/x]
```

The effect label propagates to the application result.

```
Γ ⊢ f ⇒ (x : A) → B    Γ ⊢ a ⇐ A
───────────────────────────────────  [App-Pure]
Γ ⊢ f(a) ⇒ B[a/x]
```

Pure application carries no effect.

### 9.3 Effect Subtyping

```
Γ ⊢ T <: [E] T    // Any type can be treated as having effect E
                   // ONLY if E is empty (NoEffect or Pure)
```

The conservative rule: pure <: effectful. A pure function can be used where an effectful function is expected.

### 9.4 Effect Composition

When sequencing effectful operations:

```
Γ ⊢ a ⇒ [E1] A    Γ, x : A ⊢ b ⇒ [E2] B
───────────────────────────────────────────  [Let-Effect]
Γ ⊢ let x : A = a; b ⇒ [E1 ∪ E2] B
```

Effects are composed as set union.

### 9.5 Effect Commutativity

Effect commutativity is defined in spec/02-effects.md. For typing:

```
Γ ⊢ a ⇒ [E1] A    Γ ⊢ b ⇒ [E2] B    E1 commutes with E2
─────────────────────────────────────────────────────────  [Par-Effect]
Γ ⊢ { a, b } ⇒ { A, B }    // parallel composition is valid
```

### 9.6 M₀ Rule

M₀ does NOT implement effect tracking. All functions are treated as implicitly effectful. The syntax is parsed but not enforced.

Effects are a full-language (M₁) feature.

## 10. Subtyping

### 10.1 Basic Rules

```
──────────  [Refl]
Γ ⊢ T <: T

Γ ⊢ S <: T    Γ ⊢ T <: U
───────────────────────────  [Trans]
Γ ⊢ S <: U
```

### 10.2 Record Subtyping (Width)

```
{ f_i : T_i for i = 1..n }     and     { f_j : S_j for j = 1..m }
{ f_i : T_i for i = 1..m } ⊆ { f_j : S_j for j = 1..m }
(n ≥ m)    (the wider type has more fields)

For each field f in the narrower type, T_f <: S_f
──────────────────────────────────────────────────  [Rec-Sub]
Γ ⊢ { f_1 : T_1, ..., f_n : T_n } <: { f_1 : S_1, ..., f_m : S_m }
```

A record with more fields is a subtype of a record with fewer fields (width subtyping).

### 10.3 Function Subtyping

```
Γ ⊢ A' <: A    Γ, x : A' ⊢ B(x) <: B'(x)
───────────────────────────────────────────  [Fun-Sub]
Γ ⊢ (x : A) → B(x) <: (x : A') → B'(x)
```

Functions are contravariant in the parameter type and covariant in the return type.

### 10.4 Sum Subtyping

```
Each constructor C_i of S is a constructor of T
And T_i <: S_i where C_i(T_i) in S, C_i(S_i) in T
───────────────────────────────────────────────  [Sum-Sub]
Γ ⊢ S <: T
```

A sum type is a subtype of another if it is covered by it.

### 10.5 No Implicit Coercions

The language does NOT perform implicit numeric conversions, string-to-int coercions, or other non-subtype coercions. All type transformations must be explicit.

## 11. Type Equality

### 11.1 Definitional Equality

Definitional equality is checked by the type checker. Two types are definitionally equal if they reduce to the same normal form.

```
Γ ⊢ T ≡ T'    // definitional equality

──────────  [Eq-Refl]
Γ ⊢ T ≡ T

Γ ⊢ T ≡ T'
──────────  [Eq-Sym]
Γ ⊢ T' ≡ T

Γ ⊢ T ≡ T'    Γ ⊢ T' ≡ T''
───────────────────────────  [Eq-Trans]
Γ ⊢ T ≡ T''
```

### 11.2 Beta Reduction

```
Γ ⊢ ((fn(x : A) → B { body })(a)) ≡ body[a/x]    [Eq-Beta]
```

### 11.3 Eta Reduction

```
Γ ⊢ fn(x : A) → B { f(x) } ≡ f    if x ∉ FV(f)    [Eq-Eta]
```

### 11.4 Definitional Unfolding

```
Γ ⊢ x ≡ T    where x : T = body ∈ Γ
────────────────────────────────────  [Eq-Unfold]
Γ ⊢ x ≡ body
```

### 11.5 Propositional Equality

Propositional equality is a TYPE, not a judgment:

```
Equal(a, b, T)    // a equals b as values of type T
```

Or using infix notation:
```
a == b : T    // a equals b as values of type T
```

Propositional equality MUST be proved. It is NOT checked automatically.

```
Γ ⊢ p : Equal(a, b, T)
────────────────────────  [PropEq-Use]
Γ ⊢ a ≡ b : T    // can now treat as definitionally equal
```

## 12. Context Operations

### 12.1 Variable Lookup

```
Γ ⊢ ctx    x : T ∈ Γ
─────────────────────  [Lookup]
Γ ⊢ x ⇒ T
```

### 12.2 Context Extension

```
Γ ⊢ T type    x ∉ dom(Γ)
──────────────────────────  [Extend]
Γ, x : T ⊢ ctx
```

## 13. Completeness Checking (Summary)

The completeness checker extends the type checker. Details in spec/05-consistency.md.

### 13.1 Pattern Coverage

For a match expression on a sum type with constructors `C_1..C_n`:

```
Coverage = { arms matched } ∪ { unreachable }
Complete when Coverage ⊇ Constructors
```

### 13.2 Deep Completeness

Beyond pattern coverage:

```
account.withdrawal_allowed ↔
    account.balance ≥ amount ∧
    account.status = active

Completeness check asks:
  "What if account.status = suspended?"
  "What if amount = 0?"
  "What if amount is negative?"
  "What if balance = amount exactly?"
```

Each question requires a logical case to be addressed. Incomplete programs are rejected.

> **M₀:** Only pattern coverage completeness. No deep completeness.
> **M₁:** Full deep completeness checking.

## 14. M₀ Subset Type Rules

The M₀ bootstrap implements a subset of the type system:

| Feature | M₀ | M₁ |
|---------|----|----|
| Base types (Int, Bool, etc.) | ✓ | ✓ |
| Record types | ✓ | ✓ |
| Sum types (simple) | ✓ | ✓ |
| Function types (non-dependent) | ✓ | ✓ |
| Type parameters (List(T)) | ✓ | ✓ |
| Dependent types | ✗ | ✓ |
| Linear types (parsed) | ✓ (no checking) | ✓ (full) |
| Effect types (parsed) | ✓ (no checking) | ✓ (full) |
| Bidirectional checking | ✓ | ✓ |
| Type inference (local) | ✓ | ✓ |
| Pattern exhaustiveness | ✓ | ✓ (deep) |
| Definitional equality | ✓ | ✓ |
| Propositional equality | ✗ | ✓ |
| Four logical states | TRUE/FALSE only | Full |

M₀ typing is a simplified version of the above rules where:
- All types are considered "always TRUE" (no UNKNOWN/UNDEFINED tracking)
- All values are treated as Persistent (no linearity enforcement)
- All functions are treated as pure (no effect tracking)
- Pattern matching is exhaustive on constructors only (no deep completeness)

## 15. Example Derivations

### 15.1 Simple Let and Application

```
Given: ∅ ⊢ ctx

1. ∅ ⊢ 42 ⇒ Int                [Int]
2. ∅ + x : Int ⊢ x ⇒ Int       [Var]
3. ∅ + x : Int ⊢ x + 1 ⇒ Int  [App] [App] on (+)
4. ∅ ⊢ fn(x : Int) → Int { x + 1 } ⇐ (Int → Int)  [Lam-Check]
5. Let f = fn(x) { x + 1 }
6. ∅ ⊢ let f : Int → Int = fn(x : Int) → Int { x + 1 }; f(5) ⇒ Int  [Let]
```

### 15.2 Record Construction

```
Given: ∅ ⊢ ctx
Goal: ∅ ⊢ { x = 42, name = "hello" } ⇒ { x : Int, name : String }

1. ∅ ⊢ 42 ⇒ Int                [Int]
2. ∅ ⊢ "hello" ⇒ String        [String]
3. ∅ ⊢ { x = 42, name = "hello" } ⇒ { x : Int, name : String }  [Record-Infer]
```

### 15.3 Match with Sum Type

```
Given: type Optional(Int) = | Some(Int) | None
Goal: ∅ ⊢ match opt { Some(v) → v; None → 0 } ⇒ Int

1. ∅ ⊢ opt ⇒ Optional(Int)                    [Var]
2. ∅, v : Int ⊢ v ⇒ Int                      [Var]
3. ∅ ⊢ 0 ⇒ Int                               [Int]
4. All constructors covered: {Some, None}
5. Both arms have type Int                    [Check]
6. ∅ ⊢ match opt { Some(v) → v; None → 0 } ⇒ Int  [Match-Infer]
```

## 16. Implementation Notes

### 16.1 Bidirectional Algorithm

```
type Mode = Infer | Check(Type)

infer(ctx, expr):
    match expr:
        Literal(n) → Int
        Variable(x) → lookup(ctx, x)
        Let(x, t, expr, body) → check(ctx, expr, t); infer(ctx + (x, t), body)
        Lambda(params, ret, body) → (params) → ret    // type from annotations
        Apply(f, arg) → infer_apply(ctx, infer(ctx, f), arg)
        Match(scrutinee, arms) → infer_match(ctx, scrutinee, arms)
        ...

check(ctx, expr, target_type):
    match expr:
        Lambda(params, ret, body) → check_lambda(ctx, params, ret, body, target_type)
        Record(fields) → check_record(ctx, fields, target_type)
        ...
        _ → infer_type = infer(ctx, expr); if subtype(infer_type, target_type): ok
```

### 16.2 Key Invariant

```
At every point, the checker knows either:
  - The expected type (check mode)
  - Or must determine it (infer mode)

Never both. Never neither. This eliminates the need for backtracking
or unification in the core checker.
```

### 16.3 Error Messages

```
Type mismatches MUST report:
  - The expected type (what was required)
  - The actual type (what was found)
  - The expression location
  - The specific field/element that caused the mismatch

Example:
  Type mismatch in record field 'balance':
    Expected:  NonZero
    Found:     Int (value could be zero)
    Location:  accounts/checking.l:42
```

---

*This specification covers the core type system. For effect algebra, see `02-effects.md`. For reduction semantics, see `03-reduction.md`. For memory model, see `04-memory.md`. For consistency and completeness, see `05-consistency.md`.*
