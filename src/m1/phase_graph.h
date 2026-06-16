#ifndef PHASE_GRAPH_H
#define PHASE_GRAPH_H

#include <stdint.h>

void    phase_graph_init(void);
void    phase_graph_build(int64_t body_node);
int     phase_graph_query(const char *var, const char *phase);
int     phase_graph_will_query(const char *var, const char *phase);
int64_t phase_graph_record(const char *var, const char *phase);
int64_t phase_graph_freeze(const char *var);
int64_t phase_graph_will_check(const char *var, const char *phase);

/* now re-check (Week 2, Feature 1) */
int64_t phase_graph_now_recheck_declare(int64_t cond_node);
int64_t phase_graph_now_recheck_count(void);
int64_t phase_graph_now_recheck_get_node(int64_t i);

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
