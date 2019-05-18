#include <stdbool.h>

// Module for the data of the game board, provide access to it,
// methods of storing data into the board, and printing the board.
// Also provides a char to integer converter

/* ----------------------------------------------------------------
   int char_to_int(c)
   ----------------------------------------------------------------
   Purpose: returns single-digit integer value base on the input
            char, returns -1 if the char is not a digit
   --------------------------------------------------------------*/
int char_to_int(char c);


/* ----------------------------------------------------------------
   int get_val(row, col)
   ----------------------------------------------------------------
   Purpose: returns the integer stored at the specified position
            on the board
   requires: 0 <= row <= 8
             0 <= col <= 8
   --------------------------------------------------------------*/
int get_val(int row, int col);


/* ----------------------------------------------------------------
   void store_at_pos(row, col, val)
   ----------------------------------------------------------------
   Purpose: store the value at the specified position on the board
   requires: 0 <= row <= 8
             0 <= col <= 8
   effects: mutates BOARD
   --------------------------------------------------------------*/
void store_at_pos(int row, int col, int val);


/* ----------------------------------------------------------------
   bool store_at_row(row, digit_arr)
   ----------------------------------------------------------------
   Purpose: store the input array into the board, return 
            true if digit_arr has a length of 9 and false
            otherwise.
   requires: digit_arr is a valid pointer
             digit_arr has size of at least 9 * sizeof(char)
             0 <= row <= 8
   effects: mutates BOARD
            may print to the screen
   --------------------------------------------------------------*/
bool store_at_row(int row_num, char *digit_arr);


/* ----------------------------------------------------------------
   void print_board()
   ----------------------------------------------------------------
   Purpose: prints out the current state of the sudoku board  
   effects: prints to the screen
   --------------------------------------------------------------*/
void print_board(void);
