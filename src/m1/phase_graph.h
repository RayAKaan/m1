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
void    phase_graph_free(void);

#endif
