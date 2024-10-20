CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wpedantic -O3 -g -I./include
TARGET=sudoku
SRCS=src/main.c src/solver.c src/validator.c
OBJS=$(SRCS:.c=.o)

%.o: %.c
	$(CC) $< -c $(CFLAGS) -o $@

all: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET)

.PHONY: clean

clean:
	$(RM) $(TARGET) $(OBJS)
