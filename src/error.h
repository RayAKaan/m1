#ifndef ERROR_H
#define ERROR_H

#include "ast.h"

typedef enum {
    PHASE_LEXER,
    PHASE_PARSER,
    PHASE_SCOPE,
    PHASE_TYPE,
    PHASE_REDUCE,
    PHASE_CODEGEN,
} Phase;

void error_report(Phase phase, SrcLoc loc, const char *fmt, ...);
void error_warn(Phase phase, SrcLoc loc, const char *fmt, ...);

#endif
