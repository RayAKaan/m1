@echo off
set PATH=C:\Program Files\LLVM\bin;%PATH%
clang -std=c11 -Wall -Werror -g -D_CRT_SECURE_NO_WARNINGS -o m0c.exe main.c arena.c error.c lexer.c parser.c scope.c types.c checker.c reduce.c codegen.c
