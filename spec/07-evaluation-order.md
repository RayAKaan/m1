# 7. Evaluation Order

This section defines the deterministic evaluation order of M1 programs.
Any conforming M1 implementation must follow these rules exactly.

## 7.1 Expression Evaluation

All binary expressions evaluate left-to-right.

```
a + b
```

1. Evaluate `a`
2. Evaluate `b`
3. Compute `a + b`

This applies to all operators: `+`, `-`, `*`, `/`, `%`, `==`, `!=`, `<`, `>`, `<=`, `>=`, `&&`, `||`.

## 7.2 Function Call Evaluation

```
f(a, b, c)
```

1. Evaluate `f` (resolve function reference)
2. Evaluate `a`
3. Evaluate `b`
4. Evaluate `c`
5. Call function with evaluated arguments

Arguments are evaluated left-to-right before the function body executes.

## 7.3 Assignment Semantics

```
set _ : Int = x = expr;
```

1. Evaluate RHS (`expr`)
2. Update LHS (`x`) with the computed value
3. Record phase history (track named value assignment)
4. Fire temporal operators (see 7.5)

The old value of `x` is replaced. The new value is visible immediately to all subsequent expressions.

## 7.4 Block and Statement Evaluation

```
{
    stmt1;
    stmt2;
    stmt3
}
```

1. Evaluate `stmt1`
2. Evaluate `stmt2`
3. Evaluate `stmt3`
4. Block result = value of last statement

Semicolons separate statements. A trailing semicolon before `}` is optional.

If a `return expr;` is encountered:
- Evaluate `expr`
- Set return value
- Jump to function return label
- Skip all subsequent statements in the block

## 7.5 Temporal Operator Firing Order

After every assignment, temporal operators fire in this exact order:

1. **Phase history recording** — record the named value assignment
2. **`when` triggers** — check all registered `when` conditions; fire bodies for any that became true
3. **`will` satisfaction** — check all registered `will` commitments; record satisfaction if condition became true
4. **`now` invariant checks** — verify all registered `now` invariants still hold

This order matters. `when` fires before `now` because a trigger may modify state that affects the invariant. `will` records satisfaction after `when` fires because the trigger may cause the commitment to be fulfilled.

### At function return

When a function returns (via `return expr;` or falling through):

1. Check all `will` commitments — if any are unsatisfied, emit error[M1005]
2. Return the value

### At declaration

When `now`, `when`, or `will` are declared:

- `now condition` — immediately verify condition holds; register for future checks
- `when condition then { body }` — register trigger; do not fire immediately even if condition is true
- `will condition` — register commitment; do not check immediately

## 7.6 Freeze Semantics

```
freeze x;
```

1. Add `x` to the frozen set
2. From this point forward, any assignment to `x` is a compile-time error

Freeze is evaluated at the point it appears in the code. It affects all subsequent code, including code in the same block after the freeze statement.

Frozen variables may still be read. Only assignment is prohibited.

## 7.7 Phase History Semantics

```
was x.PhaseName
```

1. Check phase history for variable `x`
2. If `x` was ever assigned the value associated with `PhaseName`, return `1`
3. Otherwise return `0`

Phase history is recorded at every assignment (see 7.3 step 3). The check is compile-time when the phase name is a known literal. The check is runtime when the phase name is computed.

## 7.8 Control Flow

### if / else

```
if condition { then_body } else { else_body }
```

1. Evaluate `condition`
2. If non-zero: evaluate `then_body`
3. If zero: evaluate `else_body` (if present)
4. Result = value of evaluated branch

### while

```
while condition { body }
```

1. Evaluate `condition`
2. If zero: exit loop, result = 0
3. If non-zero: evaluate `body`
4. Go to step 1

`break` inside body exits loop immediately.  
`continue` inside body jumps to step 1 (re-evaluate condition).

### for

```
for init; condition; update { body }
```

1. Evaluate `init`
2. Evaluate `condition`
3. If zero: exit loop, result = 0
4. Evaluate `body`
5. Evaluate `update`
6. Go to step 2

`break` exits loop immediately.  
`continue` jumps to step 5 (evaluate update, then re-check condition).

## 7.9 Non-Determinism Prohibited

M1 programs must be deterministic. The following are not allowed:

- Unspecified evaluation order
- Undefined behavior
- Race conditions (no concurrency in M1 v1.0)

Any implementation must produce identical output for identical input on any platform.

## 7.10 Summary Table

| Event | Order |
|-------|-------|
| Binary expression | Left, then Right |
| Function call | Callee, then args left-to-right |
| Assignment | RHS → LHS update → phase record → when → will → now |
| Block | Sequential, result = last |
| return | Evaluate expr → will checks → exit |
| freeze | Add to frozen set immediately |
| was | Check phase history (compile-time if literal) |
| when declaration | Register only, do not fire |
| will declaration | Register only, do not check |
| now declaration | Verify immediately + register |
