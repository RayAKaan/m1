#include "phase_graph.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Cross-platform shim (defines strncpy_s/_TRUNCATE/_strdup on non-Windows).
   Included directly so it builds even without -include compat.h. */
#if defined(__has_include)
#  if __has_include("compat.h")
#    include "compat.h"
#  endif
#endif

/* -------------------------------------------------------------------
 * AST node kinds (mirrors m1c_out_raw.c definitions)
 * ------------------------------------------------------------------ */
extern int64_t N_SEQ;
extern int64_t N_LET;
extern int64_t N_ASSIGN;
extern int64_t N_FREEZE;
extern int64_t N_WAS;
extern int64_t N_IF;
extern int64_t N_MATCH;
extern int64_t N_WHILE;
extern int64_t N_FOR;
extern int64_t N_NAME;
extern int64_t N_WHEN;
extern int64_t N_NOW;
extern int64_t N_WILL;
extern int64_t N_BOOL;
extern int64_t N_INT;
extern int64_t N_STRING;

/* runtime API – declared in m0_runtime.c / m1c_out_raw.c preamble */
extern int64_t  m0_get(int64_t node, int64_t i);
extern const char *m0_load_string(int64_t node, int64_t i);
extern int64_t  m0_is_nil(int64_t list);
extern int64_t  m0_head(int64_t list);
extern int64_t  m0_tail(int64_t list);

/* -------------------------------------------------------------------
 * Data structures
 * ------------------------------------------------------------------ */
#define MAX_VARS    64
#define MAX_PHASES  16
#define MAX_EDGES   64

typedef struct {
    char from[64];
    char to[64];
} PEdge;

typedef struct {
    char   var[64];
    char   phases[MAX_PHASES][64];
    int    phase_count;
    PEdge  edges[MAX_EDGES];
    int    edge_count;
    int    terminal;         /* after freeze */
    char   cur_phase[64];    /* current tracked phase */
    int    has_cur;
    int    unknown;          /* phase tracking lost (e.g. loop / computed value) */
} VarState;

static VarState vars[MAX_VARS];
static int var_count;

/* Branch nesting depth (Week 3 Item 3): while > 0 we are emitting inside a
   conditional/loop body, so phase recordings are treated as uncertain. */
static int branch_depth;

/* -------------------------------------------------------------------
 * Helpers
 * ------------------------------------------------------------------ */
static int var_index(const char *name) {
    for (int i = 0; i < var_count; i++)
        if (strcmp(vars[i].var, name) == 0) return i;
    return -1;
}

static int add_var(const char *name) {
    int i = var_index(name);
    if (i >= 0) return i;
    if (var_count >= MAX_VARS) return -1;
    VarState *v = &vars[var_count];
    memset(v, 0, sizeof(*v));
    strncpy_s(v->var, sizeof(v->var), name, _TRUNCATE);
    v->has_cur = 0;
    v->unknown = 0;
    v->terminal = 0;
    return var_count++;
}

static int add_phase(VarState *v, const char *ph) {
    for (int i = 0; i < v->phase_count; i++)
        if (strcmp(v->phases[i], ph) == 0) return i;
    if (v->phase_count >= MAX_PHASES) return -1;
    strncpy_s(v->phases[v->phase_count], 64, ph, _TRUNCATE);
    return v->phase_count++;
}

static void add_edge(VarState *v, const char *from, const char *to) {
    if (v->edge_count >= MAX_EDGES) return;
    strncpy_s(v->edges[v->edge_count].from, 64, from, _TRUNCATE);
    strncpy_s(v->edges[v->edge_count].to,   64, to,   _TRUNCATE);
    v->edge_count++;
}

/* temporary buffer for integer-to-string conversion in extract_phase */
#define INT_PHASE_BUF_SIZE 32
static char int_phase_buf[INT_PHASE_BUF_SIZE];

/* extract phase name from a value node; returns NULL if not a simple name */
static const char *extract_phase(int64_t node) {
    if (!node) return NULL;
    int64_t k = m0_get(node, 0);
    if (k == N_NAME) return m0_load_string(node, 3);
    if (k == N_BOOL) return m0_get(node, 3) ? "true" : "false";
    if (k == N_INT) {
        int64_t ival = m0_get(node, 3);
        snprintf(int_phase_buf, INT_PHASE_BUF_SIZE, "%lld", (long long)ival);
        return int_phase_buf;
    }
    return NULL;  /* complex expression – unknown */
}

/* -------------------------------------------------------------------
 * Snapshot / restore for branch handling (heap-allocated)
 * ------------------------------------------------------------------ */
typedef struct {
    VarState *data;   /* heap-allocated array of var_count vars */
    int count;
} Snapshot;

static Snapshot snapshot_save(void) {
    Snapshot s;
    s.count = var_count;
    if (var_count > 0) {
        s.data = (VarState *)malloc((size_t)var_count * sizeof(VarState));
        if (s.data) memcpy(s.data, vars, (size_t)var_count * sizeof(VarState));
    } else {
        s.data = NULL;
    }
    return s;
}

static void snapshot_restore(const Snapshot *s) {
    var_count = s->count;
    if (s->data && s->count > 0)
        memcpy(vars, s->data, (size_t)s->count * sizeof(VarState));
}

static void snapshot_free(Snapshot *s) {
    free(s->data);
    s->data = NULL;
    s->count = 0;
}

/* merge info from snapshot b into current global vars state */
static void merge_state(const Snapshot *a, const Snapshot *b) {
    (void)a;  /* current state is in global vars[] */
    /* keep a's var list, merge in b's info */
    for (int bi = 0; bi < b->count; bi++) {
        const VarState *bv = &b->data[bi];
        int ai = var_index(bv->var);
        if (ai < 0) {
            /* new variable from else branch – copy it in */
            if (var_count >= MAX_VARS) continue;
            int idx = var_count++;
            memcpy(&vars[idx], bv, sizeof(VarState));
            continue;
        }
        VarState *av = &vars[ai];
        /* merge phases */
        for (int p = 0; p < bv->phase_count; p++)
            add_phase(av, bv->phases[p]);
        /* merge edges */
        for (int e = 0; e < bv->edge_count; e++)
            add_edge(av, bv->edges[e].from, bv->edges[e].to);
        /* terminal if either is terminal */
        if (bv->terminal) av->terminal = 1;
        /* unknown if either is unknown */
        if (bv->unknown) av->unknown = 1;
        /* cur_phase: if they disagree, mark unknown */
        if (av->has_cur && bv->has_cur &&
            strcmp(av->cur_phase, bv->cur_phase) != 0) {
            av->unknown = 1;
        }
    }
}

/* -------------------------------------------------------------------
 * Recursive AST walker
 * ------------------------------------------------------------------ */
static void walk_node(int64_t node);

static void walk_list(int64_t list) {
    while (!m0_is_nil(list)) {
        walk_node(m0_head(list));
        list = m0_tail(list);
    }
}

static void walk_node(int64_t node) {
    if (!node) return;
    int64_t k = m0_get(node, 0);

    if (k == N_SEQ) {
        walk_node(m0_get(node, 3));  /* left */
        walk_node(m0_get(node, 4));  /* right */
        return;
    }

    if (k == N_LET) {
        const char *nm = m0_load_string(node, 3);
        int64_t val = m0_get(node, 5);
        int64_t body = m0_get(node, 6);

        /* record initial value as phase */
        const char *ph = extract_phase(val);
        int vi = add_var(nm);
        if (vi >= 0) {
            VarState *v = &vars[vi];
            /* set always implies "live" (mutable binding) */
            add_phase(v, "live");
            if (ph) {
                add_phase(v, ph);
                strncpy_s(v->cur_phase, sizeof(v->cur_phase), ph, _TRUNCATE);
                v->has_cur = 1;
                /* self-loop for identity */
                add_edge(v, ph, ph);
            }
            v->unknown = 0;
        }

        walk_node(val);
        walk_node(body);
        return;
    }

    if (k == N_ASSIGN) {
        const char *nm = m0_load_string(node, 3);
        int64_t val = m0_get(node, 4);
        const char *ph = extract_phase(val);

        int vi = var_index(nm);
        if (vi < 0) return;  /* not a tracked variable */
        VarState *v = &vars[vi];

        if (ph) {
            add_phase(v, ph);
            if (v->has_cur) {
                add_edge(v, v->cur_phase, ph);
            } else {
                /* first assignment after unknown phase */
                add_phase(v, ph);
            }
            strncpy_s(v->cur_phase, sizeof(v->cur_phase), ph, _TRUNCATE);
            v->has_cur = 1;
            v->unknown = 0;
        } else {
            v->unknown = 1;
        }

        walk_node(val);
        return;
    }

    if (k == N_FREEZE) {
        const char *nm = m0_load_string(node, 3);
        int vi = var_index(nm);
        if (vi >= 0) vars[vi].terminal = 1;
        return;
    }

    if (k == N_IF) {
        int64_t cond  = m0_get(node, 3);
        int64_t then_ = m0_get(node, 4);
        int64_t else_ = m0_get(node, 5);
        walk_node(cond);

        Snapshot sa = snapshot_save();
        walk_node(then_);
        Snapshot st = snapshot_save();

        snapshot_restore(&sa);
        walk_node(else_);
        Snapshot se = snapshot_save();

        snapshot_restore(&sa);
        merge_state(NULL, &se);
        /* now vars holds union of then + else */
        snapshot_free(&sa);
        snapshot_free(&st);
        snapshot_free(&se);
        return;
    }

    if (k == N_MATCH) {
        int64_t sc   = m0_get(node, 3);
        int64_t arms = m0_get(node, 4);
        int64_t cnt  = m0_get(node, 5);
        walk_node(sc);

        if (cnt <= 0) return;
        if (cnt == 1) { walk_list(arms); return; }

        /* save initial state */
        Snapshot base = snapshot_save();

        /* walk each arm into its own snapshot */
        enum { MAX_ARMS = 16 };
        Snapshot arm_states[16];
        int arm_count = 0;

        for (int64_t iter = arms;
             !m0_is_nil(iter) && arm_count < MAX_ARMS;
             iter = m0_tail(iter)) {
            snapshot_restore(&base);
            walk_node(m0_head(iter));
            arm_states[arm_count] = snapshot_save();
            arm_count++;
        }

        /* merge all arm states into current: pairwise union */
        if (arm_count > 0) {
            snapshot_restore(&arm_states[0]);
            for (int i = 1; i < arm_count; i++) {
                merge_state(NULL, &arm_states[i]);
            }
            for (int i = 0; i < arm_count; i++)
                snapshot_free(&arm_states[i]);
        }
        snapshot_free(&base);
        return;
    }

    if (k == N_WHILE || k == N_FOR) {
        int64_t body = (k == N_WHILE) ? m0_get(node, 4) : m0_get(node, 6);
        /* loops: mark all as unknown (conservative) */
        for (int i = 0; i < var_count; i++)
            vars[i].unknown = 1;
        walk_node(body);
        return;
    }

    /* Recurse into children of temporal constructs */
    if (k == N_WHEN) {
        walk_node(m0_get(node, 3));  /* cond */
        walk_node(m0_get(node, 4));  /* body */
        return;
    }
    if (k == N_NOW) {
        walk_node(m0_get(node, 3));  /* cond */
        return;
    }
    if (k == N_WILL) {
        walk_node(m0_get(node, 3));  /* cond */
        return;
    }
    if (k == N_WAS) {
        /* was x.phi — just skip, doesn't change graph */
        return;
    }
    /* N_INT, N_STRING, N_BOOL, N_NAME, N_UNIT, N_CALL, N_FIELD, etc. – no state effect */
}

/* -------------------------------------------------------------------
 * DFS reachability: can we reach `target` from any known phase via edges?
 * ------------------------------------------------------------------ */
static int dfs_reachable(const VarState *v, const char *target,
                         int *visited, int depth) {
    if (depth > MAX_PHASES) return 0;  /* safety bound */

    for (int e = 0; e < v->edge_count; e++) {
        const char *to = v->edges[e].to;
        if (visited[e]) continue;
        if (strcmp(to, target) == 0) return 1;
        /* can we continue from `to` to reach target? mark edge visited */
        visited[e] = 1;
        /* check if `to` is itself a phase with outgoing edges */
        /* we need to find edges whose `from` matches `to` */
        for (int e2 = 0; e2 < v->edge_count; e2++) {
            if (strcmp(v->edges[e2].from, to) == 0) {
                if (dfs_reachable(v, target, visited, depth + 1))
                    return 1;
            }
        }
    }
    return 0;
}

/* -------------------------------------------------------------------
 * Will / now commitment tracking (for Task 3.5)
 * ------------------------------------------------------------------ */
#define MAX_COMMITS 64

typedef struct {
    char var[64];
    char phase[64];
    int  line;
    int  col;
} WillCommit;

static WillCommit will_commits[MAX_COMMITS];
static int    will_commit_count;

static WillCommit now_commits[MAX_COMMITS];
static int    now_commit_count;

/* now re-check support (Week 2, Feature 1) — see FFI functions below */
#define MAX_RECHECK_NODES 64
static int64_t recheck_cond_nodes[MAX_RECHECK_NODES];
static int     recheck_count;

/* will return-guard support (Week 2, Feature 2) — condition AST nodes that must
   hold by the end of the current function. Reset per function (via init). */
#define MAX_WILL_NODES 64
static int64_t will_cond_nodes[MAX_WILL_NODES];
static int     will_cond_count;

void phase_graph_constraint_reset(void);

static void reset_commitments(void) {
    will_commit_count = 0;
    now_commit_count  = 0;
    recheck_count     = 0;
    will_cond_count   = 0;
    phase_graph_constraint_reset();
}

/* -------------------------------------------------------------------
 * now re-check support (Week 2, Feature 1)
 *
 * At a `now C` declaration the compiler hands us the AST node handle for
 * the condition C via phase_graph_now_recheck_declare(). The compiler then,
 * at each later assignment, asks how many active now-conditions exist
 * (phase_graph_now_recheck_count) and fetches each node handle
 * (phase_graph_now_recheck_get_node) so it can re-emit the condition as a
 * C runtime check after the mutation. This is the "correct" re-check:
 * the full condition expression is re-evaluated, not just reported.
 * ------------------------------------------------------------------ */
int64_t phase_graph_now_recheck_declare(int64_t cond_node) {
    if (recheck_count >= MAX_RECHECK_NODES) return 0;
    recheck_cond_nodes[recheck_count] = cond_node;
    recheck_count++;
    return 1;
}

int64_t phase_graph_now_recheck_count(void) {
    return (int64_t)recheck_count;
}

int64_t phase_graph_now_recheck_get_node(int64_t i) {
    if (i < 0 || i >= recheck_count) return 0;
    return recheck_cond_nodes[i];
}

/* -------------------------------------------------------------------
 * will return-guard support (Week 2, Feature 2)
 *
 * At a `will C` site the compiler registers the condition AST node handle.
 * In emit_fn, just before the function returns, the compiler asks how many
 * will-conditions are active and fetches each node to re-emit it as a guard:
 *   if (!(C)) { fprintf(stderr,"[M1101] will commitment unmet\n"); }
 * The registry is per-function (cleared by phase_graph_init at function entry).
 * ------------------------------------------------------------------ */
int64_t phase_graph_will_guard_declare(int64_t cond_node) {
    if (will_cond_count >= MAX_WILL_NODES) return 0;
    will_cond_nodes[will_cond_count] = cond_node;
    will_cond_count++;
    return 1;
}

int64_t phase_graph_will_guard_count(void) {
    return (int64_t)will_cond_count;
}

int64_t phase_graph_will_guard_get_node(int64_t i) {
    if (i < 0 || i >= will_cond_count) return 0;
    return will_cond_nodes[i];
}

/* -------------------------------------------------------------------
 * will + now conflict detection (Week 3, Item 2)
 *
 * The self-hosted compiler's `will`/`now` take boolean conditions, not var.Phase.
 * For the common decidable case `op` is a comparison of a variable against an
 * integer literal (e.g. `will x == 5`, `now x < 3`). We record each such
 * constraint as (var, op, value, kind) and, on each new constraint, check it
 * against all prior constraints on the same variable for a literal contradiction.
 *
 * op codes (match m1c.m0 OP_*): 5=EQ 6=NEQ 7=LT 8=GT 9=LE 10=GE
 * kind: 0 = now (must hold now & after mutations), 1 = will (must eventually hold)
 *
 * Returns 1 if the new constraint contradicts an existing one, else 0.
 * ------------------------------------------------------------------ */
#define MAX_CONSTRAINTS 128
typedef struct { char var[64]; int op; int64_t val; int kind; } Constraint;
static Constraint constraints[MAX_CONSTRAINTS];
static int constraint_count;

/* Does a value v satisfy (op, bound)? */
static int sat(int op, int64_t v, int64_t bound) {
    switch (op) {
        case 5:  return v == bound;   /* EQ  */
        case 6:  return v != bound;   /* NEQ */
        case 7:  return v <  bound;   /* LT  */
        case 8:  return v >  bound;   /* GT  */
        case 9:  return v <= bound;   /* LE  */
        case 10: return v >= bound;   /* GE  */
        default: return 1;
    }
}

/* Are two single-variable constraints jointly unsatisfiable? Decided by scanning
   a bounded integer window around the two bounds (sufficient for the comparison
   ops above, which are monotone / point constraints). */
static int contradicts(int op1, int64_t b1, int op2, int64_t b2) {
    int64_t lo = (b1 < b2 ? b1 : b2) - 2;
    int64_t hi = (b1 > b2 ? b1 : b2) + 2;
    for (int64_t v = lo; v <= hi; v++)
        if (sat(op1, v, b1) && sat(op2, v, b2)) return 0; /* some v satisfies both */
    return 1; /* no value in the window satisfies both -> contradiction */
}

/* Record a (var,op,val,kind) constraint; return 1 if it contradicts a prior
   constraint on the same variable (and emit a diagnostic), else 0. */
int64_t phase_graph_constraint_check(const char *var, int64_t op,
                                     int64_t val, int64_t kind) {
    int conflict = 0;
    for (int i = 0; i < constraint_count; i++) {
        if (strcmp(constraints[i].var, var) != 0) continue;
        if (contradicts((int)op, val, constraints[i].op, constraints[i].val)) {
            const char *k_new = kind ? "will" : "now";
            const char *k_old = constraints[i].kind ? "will" : "now";
            fprintf(stderr,
                "[M1102] warning: '%s %s ...' conflicts with prior '%s %s ...'\n",
                k_new, var, k_old, var);
            conflict = 1;
        }
    }
    if (constraint_count < MAX_CONSTRAINTS) {
        strncpy_s(constraints[constraint_count].var, 64, var, _TRUNCATE);
        constraints[constraint_count].op   = (int)op;
        constraints[constraint_count].val  = val;
        constraints[constraint_count].kind = (int)kind;
        constraint_count++;
    }
    return conflict;
}

void phase_graph_constraint_reset(void) { constraint_count = 0; }

/* -------------------------------------------------------------------
 * Branch-aware phase tracking (Week 3, Item 3)
 *
 * The compiler brackets each conditional/loop body with enter/exit so that any
 * phase recorded inside (which may or may not execute at runtime) is treated as
 * uncertain rather than a definite phase. This prevents `was x.P` from folding
 * to a wrong literal when the assignment to x is conditional.
 * ------------------------------------------------------------------ */
void phase_graph_enter_branch(void) { branch_depth++; }
void phase_graph_exit_branch(void)  { if (branch_depth > 0) branch_depth--; }


static int is_will_committed(const char *var, const char *phase) {
    for (int i = 0; i < will_commit_count; i++)
        if (strcmp(will_commits[i].var, var) == 0 &&
            strcmp(will_commits[i].phase, phase) == 0)
            return 1;
    return 0;
}

static int is_now_committed(const char *var, const char *phase) {
    for (int i = 0; i < now_commit_count; i++)
        if (strcmp(now_commits[i].var, var) == 0 &&
            strcmp(now_commits[i].phase, phase) == 0)
            return 1;
    return 0;
}

static void record_will(const char *var, const char *phase, int line, int col) {
    if (will_commit_count >= MAX_COMMITS) return;
    strncpy_s(will_commits[will_commit_count].var,   64, var,   _TRUNCATE);
    strncpy_s(will_commits[will_commit_count].phase, 64, phase, _TRUNCATE);
    will_commits[will_commit_count].line = line;
    will_commits[will_commit_count].col  = col;
    will_commit_count++;
}

static void record_now(const char *var, const char *phase, int line, int col) {
    if (now_commit_count >= MAX_COMMITS) return;
    strncpy_s(now_commits[now_commit_count].var,   64, var,   _TRUNCATE);
    strncpy_s(now_commits[now_commit_count].phase, 64, phase, _TRUNCATE);
    now_commits[now_commit_count].line = line;
    now_commits[now_commit_count].col  = col;
    now_commit_count++;
}

static void print_location_hint(int line, int col) {
    fprintf(stderr, "<phase-graph>:%d:%d", line, col);
}

/* Look for any will that conflicts with the given now var+phase */
static int find_will_conflict(const char *var, const char *phase) {
    for (int i = 0; i < will_commit_count; i++)
        if (strcmp(will_commits[i].var, var) == 0 &&
            strcmp(will_commits[i].phase, phase) == 0)
            return i;
    return -1;
}

/* Look for any now that conflicts with the given will var+phase */
static int find_now_conflict(const char *var, const char *phase) {
    for (int i = 0; i < now_commit_count; i++)
        if (strcmp(now_commits[i].var, var) == 0 &&
            strcmp(now_commits[i].phase, phase) == 0)
            return i;
    return -1;
}

/* -------------------------------------------------------------------
 * will query: return 1 if every terminal-reaching path passes through `phase`
 * Also detects duplicates and now–will conflicts.
 * ------------------------------------------------------------------ */
int phase_graph_will_query(const char *var, const char *phase) {
    int vi = var_index(var);
    if (vi < 0) return -1;  /* unknown variable */

    const VarState *v = &vars[vi];

    /* Duplicate will detection */
    if (is_will_committed(var, phase)) {
        fprintf(stderr, "[M1103] warning: duplicate 'will %s.%s'\n", var, phase);
        return 1;  /* already committed – treat as satisfied */
    }

    /* Now–will conflict: was a 'now' already declared for this var+phase? */
    int nci = find_now_conflict(var, phase);
    if (nci >= 0) {
        fprintf(stderr, "[M1101] error: 'will %s.%s' conflicts with prior 'now %s.%s'",
                var, phase, var, phase);
        print_location_hint(now_commits[nci].line, now_commits[nci].col);
        fprintf(stderr, "\n");
        return 1;
    }

    /* Record this will */
    record_will(var, phase, 0, 0);

    /* if variable is never known or tracking is lost, can't decide */
    if (v->unknown) return -1;
    if (!v->terminal) return -1;  /* not bounded – runtime check needed */

    /* if the target phase was never even recorded, it can't be satisfied */
    int phase_exists = 0;
    for (int p = 0; p < v->phase_count; p++)
        if (strcmp(v->phases[p], phase) == 0) { phase_exists = 1; break; }
    if (!phase_exists) return 0;

    /* Conservative: if `phase` appears in phases[] and var is terminal,
       and no `unknown` branch exists, we assume the will is satisfied. */
    return 1;
}

/* -------------------------------------------------------------------
 * will_check: called for `now x.V` to detect now–will conflicts
 * Returns 1 if conflict found, 0 otherwise.
 * ------------------------------------------------------------------ */
int64_t phase_graph_will_check(const char *var, const char *phase) {
    /* Duplicate now detection */
    if (is_now_committed(var, phase)) {
        fprintf(stderr, "[M1104] warning: duplicate 'now %s.%s'\n", var, phase);
        return 1;
    }

    /* Now–will conflict: was a 'will' already declared for this var+phase? */
    int wci = find_will_conflict(var, phase);
    if (wci >= 0) {
        fprintf(stderr, "[M1101] error: 'now %s.%s' conflicts with prior 'will %s.%s'",
                var, phase, var, phase);
        print_location_hint(will_commits[wci].line, will_commits[wci].col);
        fprintf(stderr, "\n");
        return 1;
    }

    /* Record this now */
    record_now(var, phase, 0, 0);
    return 0;
}

/* -------------------------------------------------------------------
 * Public API
 * ------------------------------------------------------------------ */
void phase_graph_init(void) {
    memset(vars, 0, sizeof(vars));
    var_count = 0;
    branch_depth = 0;
    reset_commitments();
}

void phase_graph_build(int64_t body_node) {
    phase_graph_init();
    walk_node(body_node);
}

int64_t phase_graph_query(char *var, char *phase) {
    int vi = var_index(var);
    if (vi < 0) {
        /* variable never seen – was query is false */
        return 0;
    }
    const VarState *v = &vars[vi];

    /* If phase tracking was lost (e.g. a conditional/loop assignment), we cannot
       statically decide membership — fall back to runtime. This must take priority
       over the membership/reachability checks below, otherwise a phase recorded
       before the branch could fold to a wrong literal. */
    if (v->unknown) {
        return -1;
    }

    /* special: "live" phase – was x.live means "was this var ever assigned?" */
    if (strcmp(phase, "live") == 0) {
        return (v->has_cur || v->phase_count > 0) ? 1 : 0;
    }

    /* check direct phase membership */
    for (int p = 0; p < v->phase_count; p++)
        if (strcmp(v->phases[p], phase) == 0) return 1;

    /* DFS reachability: check if `phase` is reachable via edge transitions */
    int visited[64] = {0};
    for (int p = 0; p < v->phase_count; p++) {
        if (dfs_reachable(v, phase, visited, 0)) {
#ifdef PG_DEBUG
            fprintf(stderr, "[PG] was %s.%s → 1 (via DFS)\n", var, phase);
#endif
            return 1;
        }
    }

    /* if unknown, fall back to runtime */
    if (v->unknown) {
#ifdef PG_DEBUG
        fprintf(stderr, "[PG] was %s.%s → -1 (unknown)\n", var, phase);
#endif
        return -1;
    }

    /* if terminal and phase never seen nor reachable, definitely false */
    if (v->terminal) {
#ifdef PG_DEBUG
        fprintf(stderr, "[PG] was %s.%s → 0 (terminal, unreachable)\n", var, phase);
#endif
        return 0;
    }

    /* non-terminal – more transitions possible */
#ifdef PG_DEBUG
    fprintf(stderr, "[PG] was %s.%s → -1 (non-terminal)\n", var, phase);
#endif
    return -1;
}

/* -------------------------------------------------------------------
 * Task 3.1 FFI wrappers: record / freeze / will_check
 * ------------------------------------------------------------------ */
int64_t phase_graph_record(const char *var, const char *phase) {
    int vi = add_var(var);
    if (vi < 0) return 0;
    VarState *v = &vars[vi];
    /* Inside a conditional branch / loop body the assignment may or may not
       execute, so we MUST NOT record it as a definite phase (that would let a
       later `was x.P` fold to a wrong literal). Instead mark the variable
       unknown so queries fall back to a runtime phase_graph_query(). */
    if (branch_depth > 0) {
        v->unknown = 1;
        return 1;
    }
    add_phase(v, phase);
    if (v->has_cur) {
        add_edge(v, v->cur_phase, phase);
    }
    strncpy_s(v->cur_phase, sizeof(v->cur_phase), phase, _TRUNCATE);
    v->has_cur = 1;
    v->unknown = 0;
    return 1;
}

int64_t phase_graph_freeze(const char *var) {
    int vi = var_index(var);
    if (vi < 0) return 0;
    vars[vi].terminal = 1;
    return 1;
}

void phase_graph_free(void) {
    /* no dynamic allocations to free currently */
}
