// ? The Sudoku solving algorithm presented in the code uses a bitwise representation and
// ? a recursive search to determine whether a Sudoku grid can be filled in a valid way.
// ? Here is an explanation of the mathematical and logical workings of the algorithm:
// ? 
// ? The algorithm uses a mask matrix of size HALF_SIZE x SIZE to keep track of the
// ? numbers already used in each row, column, and 3x3 block of the Sudoku grid.
// ? 
// ? Each row of the mask matrix represents:
// ? 
// ? - mask[0]: the numbers in each row.
// ? - mask[1]: the numbers in each column.
// ? - mask[2]: the numbers in each 3x3 block.
// ? 
// ? Each number from 1 to 9 is represented by a specific bit in a 16-bit integer.
// ? For example, the number 1 is represented by bit 0 (1 << 1), the number 2 by bit 1 (1 << 2), and so on.
// ? 
// ? Bit Manipulation Functions:
// ? 
// ? - set_bit(): Sets the bit corresponding to a number in the row, column and block.
// ? This implies that the number is already present and therefore cannot be used in that context.
// ? 
// ? - clear_bit(): Turns off the corresponding bit, useful when canceling an attempt (backtracking).
// ? 
// ? - get_no_zeros: Counts the numbers that cannot be used (zero in the bitmask context).
// ? This determines how many options remain for a cell.
// ? 
// ? Recursive Search (Backtracking):
// ? 
// ? - bit_operations(): This function explores the grid looking for empty cells and calculating the possible choices for each.
// ? 
// ? - For each empty cell, a "set" of possible numbers is calculated using the current mask.
// ? If the number of possibilities is less than the previously found, the cell is considered a candidate for a solution attempt.
// ? 
// ? - If a cell with a unique possibility is found, the algorithm assigns that number and continues recursively.
// ? If the recursion finds a valid solution, the Sudoku is solved.
// ? 
// ? - If there are no valid choices, the algorithm cancels the assignment and tries other possibilities.

#include "settings.h"

#define COL_DISPLACEMENT(i, j) (HALF_SIZE * (i / HALF_SIZE) + j / HALF_SIZE)

void set_bit(uint16_t mask[HALF_SIZE][SIZE], uint16_t i, uint16_t j, uint16_t bit_position) {
    uint16_t bit_on = 1 << bit_position;
    
    // set the corresponding bit in the row
    mask[0][i] |= bit_on;
    
    // set the corresponding bit in the column 
    mask[1][j] |= bit_on;
    
    // set the corresponding bit in the 3x3 block
    mask[2][COL_DISPLACEMENT(i, j)] |= bit_on;
}

void clear_bit(uint16_t mask[HALF_SIZE][SIZE], uint16_t i, uint16_t j, uint16_t bit_position) {
    uint16_t bit_off = ~(1 << bit_position);

    // clears the corresponding bit in the row
    mask[0][i] &= bit_off;

    // clears the corresponding bit in the column
    mask[1][j] &= bit_off;
    
    // clears the corresponding bit in the 3x3 block
    mask[2][COL_DISPLACEMENT(i, j)] &= bit_off;
}

// counts the number of zeros in the binary representation of the set
uint16_t get_no_zeros(uint16_t set) {
    uint16_t count = 0;
    for (uint16_t i = 1; i <= SIZE; ++i) if ( (set & (1 << i)) == 0 ) ++count;
    return count;
}

bool bit_operations(unsigned char (*problem)[SIZE][SIZE], uint16_t mask[HALF_SIZE][SIZE]) {
    uint16_t new_set = 0, new_size = SIZE;
    int16_t row = -1, col = -1;
    uint16_t set, size;

    // iterate over all the cells of the Sudoku
    for (uint16_t i = 0; i < SIZE; ++i) {
        for (uint16_t j = 0; j < SIZE; ++j) {

            // check if the cell is empty
            if ( (*problem)[i][j] == 0 ) {
            
                // calculate the set of possible numbers for the cell (row, column, block)
                set = mask[0][i] | mask[1][j] | mask[2][COL_DISPLACEMENT(i, j)];

                // calculate the number of zeros in the set
                size = get_no_zeros(set);
                
                // if the set size is less than the minimum size found so far
                if (size < new_size) {
                    row = i;
                    col = j;
                    new_set = set;
                    new_size = size;

                    // if the set size is 0, the Sudoku is not solvable
                    // else if there is only one possible number, exit immediately
                    if (size == 0) return false; else if (size == 1) goto end;
                }
            }
        }
    }

end:
    // if there are no empty cells, the Sudoku is solved
    if (row == -1) return true;

    // iterates over the possible numbers (from 1 to 9) for the selected cell
    for (uint16_t k = 1; k <= SIZE; ++k) {

        // if the number k is not present in the set of possible numbers
        if ( (new_set & (1 << k) ) == 0 ) {
            
            // try assigning the number k to the cell
            (*problem)[row][col] = k;
            set_bit(mask, row, col, k);

            // recursive call to continue with the resolution
            if (bit_operations(problem, mask)) return true; // if the recursive call returns true, the Sudoku is solved
            
            // if the recursive call returns false, unassign the bits
            clear_bit(mask, row, col, k);
        }
    }

    // if none of the numbers work, cancel the assignment and go back
    (*problem)[row][col] = 0;

    return false; // the Sudoku is not solvable
}

void solve(unsigned char (*problem)[SIZE][SIZE]) {
    // bitmask initialization
    uint16_t mask[HALF_SIZE][SIZE] = { 0 };

    // setting the bits in the bitmask based on the numbers already present in the Sudoku
    for (uint16_t i = 0; i < SIZE; ++i) {
        for (uint16_t j = 0; j < SIZE; ++j) {
            set_bit(mask, i, j, (*problem)[i][j]);
        }
    }

    // function call to solve Sudoku
    if (!bit_operations(problem, mask)) puts("The Sudoku is not solvable.");
}
