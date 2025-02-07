CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic -O3 -I./include/

SRCS=./src/main.c ./src/solver.c ./src/validator.c
TARGET=sudoku

TARGET_SRCS=./test/test.c ./src/solver.c ./src/validator.c
TARGET_TEST=test

BINARY_DIR=./bin/

all:
	@mkdir -p $(BINARY_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(BINARY_DIR)$(TARGET)

test:
	@mkdir -p $(BINARY_DIR)
	$(CC) $(CFLAGS) $(TARGET_SRCS) -o $(BINARY_DIR)$(TARGET_TEST)

clean:
	$(RM) -r $(BINARY_DIR) ./test/*.log

.PHONY: clean test