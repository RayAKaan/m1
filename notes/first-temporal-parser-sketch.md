# First Temporal Parser + AST Sketch for m1c.m0 (Week 2 starter)

**Purpose:** Concrete, copy-pasteable starting point for porting the temporal frontend from C bootstrap into `src/m1/m1c.m0`. Use the C side (`src/ast.h` NodeKind, `phase_graph.c` walk_node + N_* externs, `parser.c`) as reference.

**Date:** 2026-06-14
**Status:** Sketch only — not yet integrated. Start adding to m1c.m0 after Week 1 exploration is done.

---

## 1. New AST Node Kinds (add after `N_WHILE`, line 102)

```m0
    let N_LIVE : Int = 24
    let N_FREEZE : Int = 25
    let N_WAS : Int = 26
    let N_WILL : Int = 27
    let N_NOW : Int = 28
    let N_WHEN : Int = 29
```

> Keep numbering consistent with C side if possible. C has N_FREEZE etc. as externs from `m1c_out_raw`. Match the numbers used in `phase_graph.c` walk: N_FREEZE, N_WAS, N_NOW, N_WILL, N_WHEN.

## 2. Token Constants (add after `TK_WHILE`, line 78)

```m0
    let TK_LIVE : Int = 51
    let TK_FREEZE : Int = 52
    let TK_WWAS : Int = 53
    let TK_WHEN : Int = 54
    let TK_WILL : Int = 55
    let TK_NOW : Int = 56
    let TK_THEN : Int = 57
```

## 3. Thin pg_* Wrappers (add after `phase_graph_*` externals, ~line 23)

```m0
    fn pg_init() -> Int { phase_graph_init() }
    fn pg_record(v : String, p : String) -> Int { phase_graph_record(v, p) }
    fn pg_freeze(v : String) -> Int { phase_graph_freeze(v) }
    fn pg_query(v : String, p : String) -> Int { phase_graph_query(v, p) }
    fn pg_will_check(v : String, p : String) -> Int { phase_graph_will_check(v, p) }
```

## 4. Constructor Functions (add after `n_while`, ~line 237)

```m0
    fn n_live(nm : String, ty : Int, val : Int, line : Int, col : Int) -> Int {
        let n : Int = nk(N_LIVE, line, col, 7);
        let s0 : Int = m0_store_string(n, 3, nm);
        let s1 : Int = m0_set(n, 4, ty);
        let s2 : Int = m0_set(n, 5, val);
        n
    }
    fn n_freeze(nm : String, line : Int, col : Int) -> Int {
        let n : Int = nk(N_FREEZE, line, col, 4);
        let s : Int = m0_store_string(n, 3, nm);
        n
    }
    fn n_was(var : Int, phase : String, line : Int, col : Int) -> Int {
        let n : Int = nk(N_WAS, line, col, 5);
        let s0 : Int = m0_set(n, 3, var);
        let s1 : Int = m0_store_string(n, 4, phase);
        n
    }
    fn n_will(cond : Int, line : Int, col : Int) -> Int {
        let n : Int = nk(N_WILL, line, col, 4);
        let s : Int = m0_set(n, 3, cond);
        n
    }
    fn n_now(cond : Int, line : Int, col : Int) -> Int {
        let n : Int = nk(N_NOW, line, col, 4);
        let s : Int = m0_set(n, 3, cond);
        n
    }
    fn n_when(cond : Int, body : Int, line : Int, col : Int) -> Int {
        let n : Int = nk(N_WHEN, line, col, 5);
        let s0 : Int = m0_set(n, 3, cond);
        let s1 : Int = m0_set(n, 4, body);
        n
    }
```

## 5. Parser Productions (add into `parse_atom` / `parse_decl`)

Insert after the `TK_WHILE` case in `parse_atom` (~line 634):

```m0
        if k == TK_FREEZE {
            let nm : String = ps_str(ps_adv(s));
            mk_pr(n_freeze(nm, line, col), ps_adv(s))
        } else {
        if k == TK_WWAS {
            let vr : PR = parse_atom(ps_adv(s));
            let sdot : PS = ps_adv(vr.st);
            let ph : String = ps_str(ps_adv(sdot));
            mk_pr(n_was(vr.node, ph, line, col), ps_adv(sdot))
        } else {
        if k == TK_WILL {
            let cr : PR = parse_expr(ps_adv(s));
            mk_pr(n_will(cr.node, line, col), cr.st)
        } else {
        if k == TK_NOW {
            let cr : PR = parse_expr(ps_adv(s));
            mk_pr(n_now(cr.node, line, col), cr.st)
        } else {
        if k == TK_WHEN {
            let cr : PR = parse_expr(ps_adv(s));
            let s2 : PS = ps_adv(cr.st);
            let br : PR = parse_expr(s2);
            mk_pr(n_when(cr.node, br.node, line, col), br.st)
        } else {
```

For `TK_LIVE`, add handling in `parse_decl` or a new `parse_stmt` helper.

## 6. Minimal Codegen Hooks (in `emit_c_expr`, before final `m0_print("0")`)

```m0
        if k == N_FREEZE {
            let nm : String = m0_load_string(e, 3);
            let _p : Int = pg_freeze(nm);
            let _q : Int = m0_print("/* freeze "); let _r : Int = m0_print(nm); m0_print(" */ 0")
        } else {
        if k == N_WAS {
            let var_e : Int = m0_get(e, 3);
            let ph : String = m0_load_string(e, 4);
            let vn : String = m0_load_string(var_e, 3);
            let res : Int = pg_query(vn, ph);
            let _p : Int = m0_print(if res == 1 { "1" } else { if res == 0 { "0" } else { "/* unknown was */ 0" } });
            let _q : Int = m0_print("")
        } else {
```

## 7. Integration Order

1. Add N_* constants + token constants (compile-test with m0c first).
2. Add constructor functions.
3. Add pg_* wrappers.
4. Add parser cases for `freeze x;` and `was x.Phase` (easiest, as exprs).
5. Add "live" decl parsing (harder because of `set live` syntax).
6. Wire minimal emit that at least doesn't crash + calls the pg_* wrappers.
7. Test by feeding a small `.m1` with temporal keywords to m1c (via m0c bootstrap).

## 8. Test Snippet

```m1
module TestLive {
    fn main() -> Int {
        set live x : Int = 42;
        freeze x;
        was x.live
    }
}
```

## Files to Touch

- `src/m1/m1c.m0` (main target)
- (later) `tests/` for temporal test cases
- (later) `paper/evidence/` after some pass under m1c
