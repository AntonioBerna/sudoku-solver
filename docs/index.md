---
layout: single
title: "Sudoku Solver using bitmasking and backtracking in C"
author_profile: true
toc: true
toc_sticky: true
---

# sudoku-solver

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/1c00f9216d36419b86f0584dd6dafbc4)](https://app.codacy.com/gh/AntonioBerna/sudoku-solver/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade) ![GitHub repo size](https://img.shields.io/github/repo-size/AntonioBerna/sudoku-solver) ![GitHub License](https://img.shields.io/github/license/AntonioBerna/sudoku-solver) ![Docker Image Size](https://img.shields.io/docker/image-size/antonioberna/sudoku-solver)

## Usage

### Classic way

If you want to try my code I must first clone the repository using the command:

```
git clone https://github.com/AntonioBerna/sudoku-solver.git
```

Now you can use the `make` command to generate the executable called `sudoku`, inside `bin/` directory, and then you will need to use the `./bin/sudoku n` command to run the program, where `n` is a number between 1 and 9 (depending on the Sudoku to be solved in `include/problems.h` file). For example, the command `./bin/sudoku 3` generates the following output:

```
-------------------------
| 4 9 6 | 1 7 3 | 8 2 5 | 
| 2 7 8 | 5 9 6 | 4 1 3 | 
| 3 1 5 | 8 4 2 | 6 7 9 | 
-------------------------
| 9 8 1 | 3 5 7 | 2 6 4 | 
| 5 4 3 | 2 6 8 | 1 9 7 | 
| 6 2 7 | 9 1 4 | 3 5 8 | 
-------------------------
| 1 6 4 | 7 3 5 | 9 8 2 | 
| 7 3 2 | 6 8 9 | 5 4 1 | 
| 8 5 9 | 4 2 1 | 7 3 6 | 
-------------------------
main return value: 0
```

If you want to add more sudoku you will have to fix the code present in the `include/problems.h` file (adding new matrices) and also the `NO_PROBLEMS` macro present in the `include/settings.h` file. Please don't forget to update the following sudoku matrix (present at the bottom of the `include/problems.h` file):

```c
static unsigned char (*problems[NO_PROBLEMS + 1])[SIZE][SIZE] = {
    NULL,
    &problem1, &problem2, &problem3,
    &problem4, &problem5, &problem6,
    &problem7, &problem8, &problem9
};
```

Finally, if you want to remove the executable and object files, you can use the `make clean` command.

That's it!

### Docker way

Another solution is to download my docker image from the `Docker Hub` registry using the following command:

```
docker pull antonioberna/sudoku-solver
```

Now you can run the container using the following command:

```
docker run --rm antonioberna/sudoku-solver 3
```

**Note:** The command above will solve the third Sudoku present in the `include/problems.h` file. If you want to solve another Sudoku, just change the number `3` to another number between 1 and 9.
{: .notice--info}

Finally, if you want to remove the image from your machine, you can use the `docker rmi antonioberna/sudoku-solver` command.

## Algorithm: bitmasking + backtracking

My algorithm solves Sudoku using bitmasking, a technique that allows you to represent sets of numbers by bits in an integer. The basic idea is to represent which numbers (from 1 to 9) are still available for each row, column and 3x3 block of the Sudoku, using bitmasks. Let's see step by step how it works.

### Bitmasking

The algorithm uses an array `mask[HALF_SIZE][SIZE]`, where:

- `mask[0][...]` keeps track of the numbers already present per row,
- `mask[1][...]` keeps track of the numbers present per column,
- `mask[2][...]` keeps track of the numbers in each 3x3 block.

Each mask is a 16-bit integer (`uint16_t`), where the bits represent whether or not a number exists in the row/column/block.

**Note:** For example, if `mask[0][i] = 0b100000000` (in binary), it means that the number 9 is present in row `i` (bit 9 is set to 1).
{: .notice--info}

### Bit manipulation functions

```c
void set_bit(uint16_t mask[HALF_SIZE][SIZE], uint16_t i, uint16_t j, uint16_t bit_position) {
    uint16_t bit_on = 1 << bit_position;

    // ? Set the corresponding bit in the row
    mask[0][i] |= bit_on;

    // ? Set the corresponding bit in the column
    mask[1][j] |= bit_on;

    // ? Set the corresponding bit in the 3x3 block
    mask[2][COL_DISPLACEMENT(i, j)] |= bit_on;
}
```

The `set_bit()` function sets the bit corresponding to the presence of a number (from 1 to 9) in the mask. For example, if we enter the number `k` in a Sudoku cell, the bit `k` of the mask corresponding to the row, column and block is set to 1. This is done using the shift `1 << bit_position` operation which moves bit 1 to the corresponding position.

```c
void clear_bit(uint16_t mask[HALF_SIZE][SIZE], uint16_t i, uint16_t j, uint16_t bit_position) {
    uint16_t bit_off = ~(1 << bit_position);

    // ? Clears the corresponding bit in the row
    mask[0][i] &= bit_off;

    // ? Clears the corresponding bit in the column
    mask[1][j] &= bit_off;

    // ? Clears the corresponding bit in the 3x3 block
    mask[2][COL_DISPLACEMENT(i, j)] &= bit_off;
}
```

while the `clear_bit()` function does the opposite: when we remove a number from a cell, the corresponding bit is cleared with `&= ~(1 << bit_position)`.

### Calculating the set of available numbers

When the algorithm needs to decide which number to insert into an empty cell, it computes the set of numbers already present in the row, column, and block of the cell. This is done using a bitwise OR operation:

```c
// ? Calculate the set of possible numbers for the cell (row, column, block)
set = mask[0][i] | mask[1][j] | mask[2][COL_DISPLACEMENT(i, j)];
```

The OR operation combines the bits set in the three masks: row, column and block, resulting in a set representing the numbers already occupied in that position.

### Calculating the possible options

To figure out how many numbers are still available (i.e. how many bits are 0 in the set), use the `get_no_zeros()` function:

```c
// ? This function counts the number of zeros in the binary representation of the set
uint16_t get_no_zeros(uint16_t set) {
    uint16_t count = 0;
    for (uint16_t i = 1; i <= SIZE; ++i) if ((set & (1 << i)) == 0) ++count;
    return count;
}
```

Here, the algorithm cycles through the bits from position 1 to 9 and counts how many bits are still 0, i.e. how many numbers can be inserted into the cell.

### Search for the best candidate

The algorithm explores all the empty cells and looks for the one with the least number of available options, since this reduces the number of attempts. This is done with the following code:

```c
if ((*problem)[i][j] == 0) {

    // ? Calculate the set of possible numbers for the cell (row, column, block)
    set = mask[0][i] | mask[1][j] | mask[2][COL_DISPLACEMENT(i, j)];

    // ? Calculate the number of zeros in the set
    size = get_no_zeros(set);

    // ? If the set size is less than the minimum size found so far
    if (size < new_size) {
        row = i;
        col = j;
        new_set = set;
        new_size = size;

        // ? If the set size is 0, the Sudoku is not solvable
        // ? else if there is only one possible number, exit immediately
        if (size == 0) return false;
        else if (size == 1) goto end;
    }
}
```

Here we look for the cell with the smallest set of numbers (i.e. the one with the fewest options available).

### Backtracking

Finally, the algorithm tries to insert every possible number (the 0 bits in the set) into the selected cell, then recursively calls the same function to solve the rest of the Sudoku:

```c
// ? Iterates over the possible numbers (from 1 to 9) for the selected cell
for (uint16_t k = 1; k <= SIZE; ++k) {

    // ? If the number k is not present in the set of possible numbers
    if ((new_set & (1 << k)) == 0) {

        // ? Try assigning the number k to the cell
        (*problem)[row][col] = k;
        set_bit(mask, row, col, k);

        // ? Recursive call to continue with the resolution
        if (bit_operations(problem, mask)) return true; // ? if the recursive call returns true, the Sudoku is solved

        // ? If the recursive call returns false, unassign the bits
        clear_bit(mask, row, col, k);
    }
}
```

If recursion fails, the entered number is removed and another is tried. If no number works, the cell is reset to 0, and the process is backtracked.

### Solution

If all cells are filled correctly without contradictions, the Sudoku is solved.

```c
void solve(unsigned char (*problem)[SIZE][SIZE]) {
    // ? Bitmask initialization
    uint16_t mask[HALF_SIZE][SIZE] = { 0 };

    // ? Setting the bits in the bitmask based on the numbers already present in the Sudoku
    for (uint16_t i = 0; i < SIZE; ++i) {
        for (uint16_t j = 0; j < SIZE; ++j) {
            set_bit(mask, i, j, (*problem)[i][j]);
        }
    }

    // ? Function call to solve Sudoku
    if (!bit_operations(problem, mask)) puts("The Sudoku is not solvable.");
}
```

The `solve()` function initializes the masks based on the numbers already present and calls the recursive function `bit_operations()` to solve the Sudoku.

## Benchmarks

The following table shows the hardware and software specifications regarding my setup:

| OS                    | CPU                         | RAM       | Toolchain     |
| :---:                 | :---:                       | :---:     | :---:         |
| Manjaro Linux v25.0.0 | Intel Core i7-8650U 1.90GHz | 16GB DDR4 | clang v19.1.7 |

You can use `make test` command to generate the executable called `test`, inside `bin/` directory, and then you will need to use the `./bin/test` command to run the program. The output will be the following:

```
=================================
Problem 1 solved in 13.064 μs.
Problem 1 is valid.
=================================
Problem 2 solved in 4.071 μs.
Problem 2 is valid.
=================================
Problem 3 solved in 531.553 μs.
Problem 3 is valid.
=================================
Problem 4 solved in 23.155 μs.
Problem 4 is valid.
=================================
Problem 5 solved in 8.589 μs.
Problem 5 is valid.
=================================
Problem 6 solved in 9.722 μs.
Problem 6 is valid.
=================================
Problem 7 solved in 17.542 μs.
Problem 7 is valid.
=================================
Problem 8 solved in 19.684 μs.
Problem 8 is valid.
=================================
Problem 9 solved in 10.520 μs.
Problem 9 is valid.
=================================
Total time: 637.900 μs.
=================================
```

**Note:** The `test` program generate the `test/sudoku_results.log` file with the results of the tests.
{: .notice--info}
