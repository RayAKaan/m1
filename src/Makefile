CC = clang
CFLAGS = -std=c11 -Wall -Werror -g -D_CRT_SECURE_NO_WARNINGS
LDFLAGS =
SRCS = main.c arena.c error.c lexer.c parser.c scope.c types.c checker.c reduce.c codegen.c
OBJS = $(SRCS:.c=.o)
TARGET = m0c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	del /Q $(OBJS) m0c.exe 2>nul || true
