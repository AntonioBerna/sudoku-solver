# Bitmasking + Backtracking Algorithm

My algorithm solves Sudoku using bitmasking, a technique that allows you to represent sets of numbers by bits in an integer. The basic idea is to represent which numbers (from 1 to 9) are still available for each row, column and 3x3 block of the Sudoku, using bitmasks. Let's see step by step how it works.

## Bitmasking

The algorithm uses an array `mask[HALF_SIZE][SIZE]`, where:

- `mask[0][...]` keeps track of the numbers already present per row,
- `mask[1][...]` keeps track of the numbers present per column,
- `mask[2][...]` keeps track of the numbers in each 3x3 block.

Each mask is a 16-bit integer (`uint16_t`), where the bits represent whether or not a number exists in the row/column/block.

!!! Note
    For example, if `mask[0][i] = 0b100000000` (in binary), it means that the number 9 is present in row `i` (bit 9 is set to 1).

## Bit manipulation functions

```c linenums="1"
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

```c linenums="1"
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

## Calculating the set of available numbers

When the algorithm needs to decide which number to insert into an empty cell, it computes the set of numbers already present in the row, column, and block of the cell. This is done using a bitwise OR operation:

```c
// ? Calculate the set of possible numbers for the cell (row, column, block)
set = mask[0][i] | mask[1][j] | mask[2][COL_DISPLACEMENT(i, j)];
```

The OR operation combines the bits set in the three masks: row, column and block, resulting in a set representing the numbers already occupied in that position.

## Calculating the possible options

To figure out how many numbers are still available (i.e. how many bits are 0 in the set), use the `get_no_zeros()` function:

```c linenums="1"
// ? This function counts the number of zeros in the binary representation of the set
uint16_t get_no_zeros(uint16_t set) {
    uint16_t count = 0;
    for (uint16_t i = 1; i <= SIZE; ++i) if ((set & (1 << i)) == 0) ++count;
    return count;
}
```

Here, the algorithm cycles through the bits from position 1 to 9 and counts how many bits are still 0, i.e. how many numbers can be inserted into the cell.

## Search for the best candidate

The algorithm explores all the empty cells and looks for the one with the least number of available options, since this reduces the number of attempts. This is done with the following code:

```c linenums="1"
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

## Backtracking

Finally, the algorithm tries to insert every possible number (the 0 bits in the set) into the selected cell, then recursively calls the same function to solve the rest of the Sudoku:

```c linenums="1"
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

## Solution

If all cells are filled correctly without contradictions, the Sudoku is solved.

```c linenums="1"
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
