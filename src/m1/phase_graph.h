#ifndef PHASE_GRAPH_H
#define PHASE_GRAPH_H

#include <stdint.h>

typedef uint32_t VarID;
typedef uint32_t PhaseID;

void    phase_graph_init(void);
void    phase_graph_build(int64_t body_node);
int64_t phase_graph_query(char *var, char *phase);
int     phase_graph_will_query(const char *var, const char *phase);
int64_t phase_graph_record(const char *var, const char *phase);
int64_t phase_graph_freeze(const char *var);
int64_t phase_graph_will_check(const char *var, const char *phase);

/* String Interning API */
VarID   phase_graph_intern_var(const char *var);
PhaseID phase_graph_intern_phase(const char *phase);

/* now re-check (Week 2, Feature 1) */
int64_t phase_graph_now_recheck_declare(int64_t cond_node);
int64_t phase_graph_now_recheck_count(void);
int64_t phase_graph_now_recheck_get_node(int64_t i);

/* Targeted now re-check (Phase 2) */
int64_t phase_graph_add_dep(const char *var, int64_t cond_node);
int64_t phase_graph_now_recheck_count_for_var(const char *var);
int64_t phase_graph_now_recheck_get_node_for_var(const char *var, int64_t i);

/* will return-guard (Week 2, Feature 2) */
int64_t phase_graph_will_guard_declare(int64_t cond_node);
int64_t phase_graph_will_guard_count(void);
int64_t phase_graph_will_guard_get_node(int64_t i);

/* will + now conflict detection (Week 3, Item 2) */
int64_t phase_graph_constraint_check(const char *var, int64_t op,
                                     int64_t val, int64_t kind);
void    phase_graph_constraint_reset(void);

/* branch-aware phase tracking (Week 3, Item 3) */
void    phase_graph_enter_branch(void);
void    phase_graph_exit_branch(void);

void    phase_graph_free(void);

#endif
