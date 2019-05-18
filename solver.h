#include <stdbool.h>
// Module for the backtracking sudoku solver

/* ----------------------------------------------------------------
   bool solve_board(row, col, step_count, mod)
   ----------------------------------------------------------------
   Purpose: attempts to solve the sudoku using backtracking
            algorithm while keeping track of the number of 
            steps. Prints out the steps depending on
            input. Returns true if successful, false otherwise
   require: 0 <= row <= 9
            0 <= col <= 8
            step_count is a valid pointer
   effects: prints to the screen
            mutates BOARD
            mutates *step_count
   --------------------------------------------------------------*/
bool solve_board(int row, int col, int *step_count, int mod);