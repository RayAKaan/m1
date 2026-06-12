# Consistency and Completeness — [Unnamed Language]

## 1. Two Distinct Checkers

The consistency checker and completeness checker are separate compiler phases, unified by their foundation in formal logic:

| Checker | Question | Method | Based on |
|---------|----------|--------|----------|
| Completeness | "Are all cases covered?" | Exhaustiveness checking | ML pattern coverage |
| Consistency | "Do any propositions contradict?" | Resolution theorem proving | Robinson 1965 |

---

## 2. Completeness Checker

### 2.1 What It Does

Ensures that every proposition in the program has a truth value for every possible input. Incomplete programs are rejected.

### 2.2 Pattern Coverage (Simple Case)

For match expressions on sum types:

```
type PaymentMethod = | Cash | Credit | Crypto | Debit

payment_result ← payment.method →
    | cash   → immediate_clear
    | credit → pending_auth
    | crypto → blockchain_verify

Completeness:
    Constructors covered: {Cash, Credit, Crypto}
    Missing: {Debit}
    → REJECT: "payment_result is undefined for Debit payments"
```

### 2.3 Pattern Coverage Algorithm

```
Algorithm: check_pattern_coverage(match_expression):

    1. Determine the type of the scrutinee
    2. Enumerate all constructors of the sum type
    3. Extract constructors matched by each arm
    4. Compute: uncovered = constructors \ matched_constructors
    5. If uncovered ≠ ∅:
        Report: "Incomplete match: missing cases {uncovered}"
        Reject program
    6. Check for unreachable arms (matched_constructors \ constructors)
    7. If unreachable ≠ ∅:
        Warn: "Unreachable arm for {unreachable}"
```

### 2.4 Deep Completeness (M₁ Feature)

Beyond pattern coverage, the completeness checker examines the logical structure of propositions:

```
account.withdrawal_allowed ↔
    account.balance ≥ amount ∧
    account.status = active
```

The checker asks:

```
1. "What if account.balance < amount?"
    → withdrawal_allowed = false? (covered by ∧)

2. "What if account.status = suspended?"
    → withdrawal_allowed = false? (need definition for suspended case)

3. "What if amount = 0?"
    → Does the comparison handle zero correctly?

4. "What if amount is negative?"
    → Is amount constrained to Nat / NonNegative?

5. "What if account.balance = amount exactly?"
    → Is this ≥ true? (yes)

6. "What if account.status is unknown?"
    → What is the truth value of withdrawal_allowed when status is UNKNOWN?
```

Each unanswered question is an INCOMPLETE PROPOSITION and must be addressed.

### 2.5 Deep Completeness Algorithm

```
Algorithm: check_deep_completeness(proposition, context):

    1. Extract all logical conditions from the proposition
    2. For each variable referenced:
        a. Determine its type
        b. Determine its possible values (from type or constraints)
        c. For each possible value not explicitly handled:
            Report: "Case not handled: variable = value"
    3. For each comparison operator:
        a. Check all boundary cases (zero, negative, max, etc.)
        b. Check overlapping cases (exact equality)
    4. For each logical connective (∧, ∨, →, ↔):
        a. Verify all truth table combinations are consistent with the proposition
    5. For each case expression:
        a. Run pattern coverage algorithm
        b. For each variable in scope:
            Check if it needs to be addressed in the case
    6. Report all incompletenesses
```

### 2.6 Interaction with Logical States

```
The completeness checker tracks the four logical states:

    "What is the value of x when condition P is UNKNOWN?"
    "What is the value of x when P is UNDEFINED?"

If a proposition's truth depends on an UNKNOWN or UNDEFINED sub-proposition,
the proposition is itself incomplete until those states are addressed.
```

### 2.7 Completeness and Invariants

```
@invariant account.balance ≥ 0

Every proposition that modifies account.balance must maintain this invariant.

Withdrawal:
    account.balance ← account.balance - amount

Completeness check:
    "Is it provable that result ≥ 0 always?"
    
    If not:
        "Withdrawal proposition is incomplete.
         Add constraint: amount ≤ account.balance"
    
    After adding:
    account.balance ← account.balance - amount
        when amount ≤ account.balance
    
    Now provable. Invariant maintained.
```

### 2.8 The Invariant As A Logical Constraint

```
@invariant is NOT a runtime assertion.
@invariant is a logical axiom that the compiler uses to check completeness.

Think of it as:
    "The following proposition MUST be true at all points in the program.
     Check every other proposition for consistency with this constraint."
```

### 2.9 M₀ Subset

```
M₀ completeness:
    - Pattern coverage on match expressions: ✓
    - Deep completeness: ✗
    - Invariant checking: ✗
    - Logical state tracking: ✗

M₀ checks that match arms cover all constructors.
That is the limit of M₀ completeness.
```

---

## 3. Consistency Checker

### 3.1 What It Does

Ensures that no proposition in the program contradicts another. Contradictions are logically impossible to maintain — the program cannot exist with contradictions.

### 3.2 J. A. Robinson's Resolution Principle (1965)

Resolution is a rule of inference for automated theorem proving:

```
Given:      P ∨ Q      (P or Q)
Given:      ¬P ∨ R     (not P or R)
─────────────────────────
Conclude:   Q ∨ R      (Q or R)
```

The two clauses contain complementary literals `P` and `¬P`, which cancel out.

### 3.3 Conversion to Clausal Form

Before resolution can be applied, propositions are converted to **clausal normal form** (CNF):

```
Step 1: Eliminate ↔ (if and only if)
    P ↔ Q  →  (P → Q) ∧ (Q → P)

Step 2: Eliminate → (implies)
    P → Q  →  ¬P ∨ Q

Step 3: Push ¬ (negation) inward
    ¬(P ∧ Q)  →  ¬P ∨ ¬Q
    ¬(P ∨ Q)  →  ¬P ∧ ¬Q
    ¬¬P       →  P
    ¬∀x.P     →  ∃x.¬P
    ¬∃x.P     →  ∀x.¬P

Step 4: Distribute ∨ over ∧
    P ∨ (Q ∧ R)  →  (P ∨ Q) ∧ (P ∨ R)

Step 5: Separate into clauses
    (P ∨ Q) ∧ (R ∨ S)
    → Clause 1: {P, Q}
    → Clause 2: {R, S}
```

### 3.4 Example Conversion

```
Proposition:
    user.access = granted ↔ user.verified ∧ user.subscribed

Step 1 (eliminate ↔):
    (user.access = granted → (user.verified ∧ user.subscribed))
    ∧ ((user.verified ∧ user.subscribed) → user.access = granted)

Step 2 (eliminate →):
    (¬(user.access = granted) ∨ (user.verified ∧ user.subscribed))
    ∧ (¬(user.verified ∧ user.subscribed) ∨ user.access = granted)

Step 3 (push ¬ inward):
    (¬(user.access = granted) ∨ (user.verified ∧ user.subscribed))
    ∧ (¬user.verified ∨ ¬user.subscribed ∨ user.access = granted)

Step 4 (distribute ∨ over ∧):
    (¬(user.access = granted) ∨ user.verified)
    ∧ (¬(user.access = granted) ∨ user.subscribed)
    ∧ (¬user.verified ∨ ¬user.subscribed ∨ user.access = granted)

Step 5 (separate into clauses):
    C1: { ¬(user.access = granted), user.verified }
    C2: { ¬(user.access = granted), user.subscribed }
    C3: { ¬user.verified, ¬user.subscribed, user.access = granted }
```

### 3.5 Resolution Algorithm

```
Algorithm: resolution(clause_set):

    // Phase 1: Normalize all propositions to clausal form
    clauses = []
    for each proposition P in the program:
        clauses.extend(convert_to_cnf(P))

    // Phase 2: Pure literal elimination (optional optimization)
    clauses = pure_literal_elimination(clauses)

    // Phase 3: Unit propagation (optional optimization)
    clauses = unit_propagation(clauses)

    // Phase 4: Main resolution loop
    new = ∅
    while true:
        // Generate all resolvents
        for each pair of clauses (Ci, Cj) in clauses:
            resolvents = resolve(Ci, Cj)
            for R in resolvents:
                if R is the empty clause:
                    return CONTRADICTION_FOUND

                if R is not a tautology and R is not subsumed by any clause:
                    new.add(R)

        if new ⊆ clauses:
            // Fixpoint reached — no new clauses
            return CONSISTENT

        clauses = clauses ∪ new
        new = ∅
```

### 3.6 Unification

For first-order resolution, variables must be unified:

```
Unification algorithm (Robinson 1965):

    unify(term1, term2):
        if term1 is a variable:
            return { term1 → term2 }
        if term2 is a variable:
            return { term2 → term1 }
        if term1 and term2 are the same constant/function:
            recursively unify sub-terms
        otherwise:
            return FAIL

    resolve(C1, C2):
        for each literal L1 in C1:
            for each literal L2 in C2:
                if L1 and ¬L2 are unifiable with substitution θ:
                    new_clause = (C1 \ {L1})θ ∪ (C2 \ {L2})θ
                    if new_clause is not a tautology:
                        add new_clause to clauses
```

### 3.7 Contradiction Detection

```
Proposition A: user.access = granted ↔ user.verified ∧ user.subscribed
Proposition B: user.access = granted ↔ user.age > 18

CNF of A: (from 3.4)
    C1: { ¬(access=granted), verified }
    C2: { ¬(access=granted), subscribed }
    C3: { ¬verified, ¬subscribed, access=granted }

CNF of B:
    C4: { ¬(access=granted), age>18 }
    C5: { ¬(age>18), access=granted }

Resolution:
    From C3 and C5 (resolve on access=granted):
    C6: { ¬verified, ¬subscribed, age>18 }

    From C1 and C5 (resolve on access=granted):
    C7: { ¬verified, age>18 }

    From C2 and C5 (resolve on access=granted):
    C8: { ¬subscribed, age>18 }

    Consider case: verified ∧ subscribed ∧ ¬(age>18)
    From C7 with verified: { age>18 }
    From C8 with subscribed: { age>18 }
    From C4 with ¬(age>18): { ¬(access=granted) }
    From C3 with verified ∧ subscribed: { access=granted }
    Conflict: { access=granted } and { ¬(access=granted) }
    → Resolve to empty clause: CONTRADICTION

Conclusion: "If user is verified, subscribed, and under 18:
    A says access = granted, B says access ≠ granted.
    Contradiction."
```

### 3.8 Presenting Contradictions to the User

```
The consistency checker reports:

    CONTRADICTION FOUND
    ──────────────────
    Propositions A and B cannot both be true.

    A (accounts.l:15): user.access = granted ↔ user.verified ∧ user.subscribed
    B (auth.l:22):     user.access = granted ↔ user.age > 18

    Counterexample:
        user.verified = true
        user.subscribed = true
        user.age = 16 (≤ 18)

    Under this assignment:
        A → access = granted
        B → access ≠ granted

    Resolution: modify either A or B to handle this case.
```

### 3.9 Consistency with Invariants

```
@invariant account.balance ≥ 0

    Withdrawal proposition:
        account.balance ← account.balance - withdrawal.amount

    Consistency check:
        Hypothesis: account.balance ≥ 0 (invariant)
        Post-state: account.balance' = account.balance - withdrawal.amount

        Can we prove account.balance' ≥ 0?
        No: not if withdrawal.amount > account.balance.

        Constraint needed: withdrawal.amount ≤ account.balance

    The constraint is discovered by attempting to prove consistency
    and identifying the missing condition.
```

### 3.10 The Four Logical States in Consistency

```
The consistency checker operates on TRUE and FALSE states only:

    TRUE propositions:    added to clause set as positive literals
    FALSE propositions:   added to clause set as negative literals
    UNKNOWN propositions: excluded from consistency checking (not yet resolved)
    UNDEFINED propositions: cause compilation error before consistency phase

A program with UNKNOWN propositions cannot proceed to consistency checking.
UNKNOWN must be resolved to TRUE or FALSE first.
```

### 3.11 Limitations (Gödel)

```
The consistency checker cannot prove its own consistency.
This is Gödel's second incompleteness theorem.

The language addresses this honestly:

    @verified       → "checked as far as the logic allows"
    @unverifiable   → "beyond self-verification (known limit)"

    CAN verify:   type correctness, completeness, individual phase consistency
    CANNOT verify: total consistency of the whole system (Gödel limit)

This is not a flaw. Any system claiming total self-verification
is either inconsistent or lying (or both).
```

### 3.12 M₀ Subset

```
M₀ consistency checking: NONE.

M₀ does not implement a consistency checker.
Propositions are assumed to be consistent.
The M₀ compiler trusts the programmer.

The consistency checker arrives in M₁ (self-hosted).
The M₀ bootstrap compiler is written with the understanding
that it will be checked by the M₁ consistency checker when
the language is self-hosting.
```

---

## 4. Integration with the Compiler Pipeline

### 4.1 Phase Ordering

```
1. Parse
2. Scope resolution
3. Type checking
    ├── Completeness: pattern coverage only (M₀)
    └── Completeness: deep (M₁)        ← after type checking, before consistency
4. Consistency checking                  ← after completeness
5. Reduction
6. Dependency analysis
7. Code generation
```

### 4.2 Why Completeness Before Consistency

```
Completeness ensures every proposition has a truth value.
Consistency ensures no propositions contradict.

An incomplete proposition cannot be checked for consistency
because its truth value is not fully determined.

Example:
    "payment_result is undefined for Debit payments"

    Before adding the Debit case:
        We don't know what payment_result is for Debit.
        We cannot check it against other propositions about payment_result.
        The system is incomplete.

    After adding the Debit case:
        payment_result is defined for all PaymentMethod values.
        We can now check consistency with other propositions.

    Order: completeness first, then consistency.
```

### 4.3 Error Recovery

```
If completeness fails:
    - Report all missing cases
    - Do NOT proceed to consistency checking
    - Allow user to fix all cases at once

If consistency fails:
    - Report the contradiction with both propositions
    - Report the logical path that leads to contradiction
    - Do NOT proceed to reduction
    - Allow user to fix the inconsistency

Both must pass before reduction and code generation.
```

---

## 5. Summary

```
Completeness checker:
    Based on:     Exhaustiveness checking (ML pattern coverage) + SMT solving
    Checks:       All cases covered, all propositions have truth value
    Rejects:      Incomplete logic
    M₀ coverage:  Pattern matching only

Consistency checker:
    Based on:     Robinson resolution theorem proving (1965)
    Checks:       No proposition contradicts another
    Rejects:      Contradictory programs
    M₀ coverage:  None (arrives in M₁)

Both are deterministic:
    No heuristics
    No AI
    No machine learning
    No probabilistic inference
    Pure formal logic
```

---

*For the grammar, see `00-grammar.peg`. For the type system, see `01-types.md`.*
