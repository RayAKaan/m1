#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include "arena.h"
#include "types.h"

int codegen(Node *program, const char *output_path);

#endif
