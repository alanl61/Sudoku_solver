#include "solver.h"
#include "board.h"
#include <stdbool.h>
#include <assert.h>

#include <stdio.h>

enum pos {TOP = 32, MID = 16, BOT = 8,
          LEFT = 4, CENTRE = 2, RIGHT = 1};


/* ----------------------------------------------------------------
   static void reset_temp(temp)
   ----------------------------------------------------------------
   Purpose: mutates the first 9 spots of temp to 0
   require: temp is a valid pointer
            temp is an integer array of length 9 minimum
   effects: mutates *temp
   --------------------------------------------------------------*/
static void reset_temp(int *temp) {
  assert(temp);
  for (int i = 0; i < 9; i++) {
    temp[i] = 0;
  }

  return;
}


/* ----------------------------------------------------------------
   static bool repeat(temp)
   ----------------------------------------------------------------
   Purpose: returns true if temp array contains repeating digits,
            false otherwise
   require: temp is a valid pointer
            temp is an integer array of length 9 minimum
   --------------------------------------------------------------*/
static bool repeat(int *temp) {
  assert(temp);
  
  int digit_occur[10];

  for (int i = 0; i < 10; i++) {
    digit_occur[i] = 0;
  }

  for (int i = 0; i < 9; i++) {
    int index = temp[i];
    digit_occur[index]++;
  }

  // check if any digit is repeated
  for (int i = 1; i < 10; i++) {
    if (digit_occur[i] > 1) {
      return true;
    }
  }

  // no digit is repeated
  return false;
}


/* ----------------------------------------------------------------
   static void store_box(row_st, row_end, col_st, col_end, temp)
   ----------------------------------------------------------------
   Purpose: stores the specified 3x3 integer box into temp
   require: temp is a valid pointer
            temp is an integer array of length 9 minimum
            row_st, col_st >= 0
            row_end, col_end <= 8
   effects: mutates *temp
   --------------------------------------------------------------*/
static void store_box(int row_st, int row_end, 
                      int col_st, int col_end, 
                      int *temp) {
  assert(temp);
  assert(row_st >= 0);
  assert(row_end <= 8);
  assert(col_st >= 0);
  assert(col_end <= 8);

  int index = 0;
  //printf("%d\n", index);

  for (int r = row_st; r <= row_end; r++) {
    for (int c = col_st; c <= col_end; c++) {
      temp[index] = get_val(r, c);
      index++;
    }
  }

  return;
}


/* ----------------------------------------------------------------
   static bool box_check_fail(row, col, temp)
   ----------------------------------------------------------------
   Purpose: checks if the specified 3x3 integer box is in a valid
            sudoku state
   require: temp is a valid pointer
            temp is an integer array of length 9 minimum
            0 <= row <= 8
            0 <= col <= 8
   effects: mutates *temp
   --------------------------------------------------------------*/
static bool box_check_fail(int row, int col, int *temp) {
  assert(temp);
  assert(row >= 0);
  assert(row <= 8);
  assert(col >= 0);
  assert(col <= 8);

  int row_pos = 0;
  int col_pos = 0;

  if (row < 3) {
    row_pos = TOP;
  }
  else if (row < 6) {
    row_pos = MID;
  }
  else {
    row_pos = BOT;
  }

  if (col < 3) {
    col_pos = LEFT;
  }
  else if (col < 6) {
    col_pos = CENTRE;
  }
  else {
    col_pos = RIGHT;
  }

  // determine which box to test for
  int box_pos = row_pos | col_pos;

  // TOP-LEFT
  if (box_pos == 36) {
    store_box(0, 2, 0, 2, temp);
  }
  // TOP-CENTRE
  else if (box_pos == 34) {
    store_box(0, 2, 3, 5, temp);
  }
  // TOP-RIGHT
  else if (box_pos == 33) {
    store_box(0, 2, 6, 8, temp);
  }
  // MID-LEFT
  else if (box_pos == 20) {
    store_box(3, 5, 0, 2, temp);
  }
  // MID-CENTRE
  else if (box_pos == 18) {
    store_box(3, 5, 3, 5, temp);
  }
  // MID-RIGHT
  else if (box_pos == 17) {
    store_box(3, 5, 6, 8, temp);
  }
  // BOT-LEFT
  else if (box_pos == 12) {
    store_box(6, 8, 0, 2, temp);
  }
  // BOT-CENTRE
  else if (box_pos == 10) {
    store_box(6, 8, 3, 5, temp);

  }
  // BOT-RIGHT
  else {
    store_box(6, 8, 6, 8, temp);
  }

  // if digit repeats in the box
  if (repeat(temp)) {
    return true;
  }

  // no digit repeats in the box
  return false;
}


/* ----------------------------------------------------------------
   static bool valid(row, col)
   ----------------------------------------------------------------
   Purpose: returns true if the current state of the sudoku board
            is valid, returns false otherwise
   require: 0 <= row <= 8
            0 <= col <= 8
   --------------------------------------------------------------*/
static bool valid(int row, int col) {
  assert(row >= 0);
  assert(row <= 8);
  assert(col >= 0);
  assert(col <= 8);

  int temp[9];

  // row check
  reset_temp(temp);

  for (int i = 0; i < 9; i++) {
    temp[i] = get_val(row, i);
  }

  if (repeat(temp)) {
    return false;
  }

  // col check
  reset_temp(temp);

  for (int i = 0; i < 9; i++) {
    temp[i] = get_val(i, col);
  }

  if (repeat(temp)) {
    return false;
  }

  // box check
  if (box_check_fail(row, col, temp)) {
    return false;
  }

  // all check passed
  return true;
}


/* ----------------------------------------------------------------
   static void selective_print(count, mod)
   ----------------------------------------------------------------
   Purpose: prints the board every (mod) steps
   require: count is a valid pointer
   --------------------------------------------------------------*/
static void selective_print(int *count, int mod) {
  assert(count);
  
  if (mod == 0) {
    return;
  }

  if ((*count % mod) == 0) {
    printf("At %d steps:\n", *count);
    print_board();
  }

  return;
}


// see solver.h for details
bool solve_board(int row, int col, int *step_count, int mod) {
  assert(step_count);
  assert(row >= 0);
  assert(row <= 9);
  assert(col >= 0);
  assert(col <= 8);

  // if the end is reached
  if (row == 9) {
    return true;
  }

  // if the current pos is unknown tile
  if (get_val(row, col) == 0) {

    for (int val = 1; val <= 9; val++) {
      // mutate the board
      store_at_pos(row, col, val);

      // check if the val is valid
      if (valid(row, col)) {
        // for each successful try, increment the count
        (*step_count)++;
        
        // print the current board
        selective_print(step_count, mod);

        // go onto the next position
        if (col == 8) {
          // go to the next row
          if (!solve_board(row + 1, 0, step_count, mod)) {
            // next pos is impossible to fill, 
            // retry the current pos
            continue;
          }

          return true;
        }
        // go to the next col
        else {
          if (!solve_board(row, col + 1, step_count, mod)) {
            // next pos is impossible to fill, 
            // retry the current pos
            continue;
          }

          return true;
        }
      }

      // else try the next digit
    }

    // no digit worked, set the tile to unknown and
    // return false
    store_at_pos(row, col, 0);
    return false;
  }

  // else go onto the next pos
  if (col == 8) {
    // go to the next row
    return solve_board(row + 1, 0, step_count, mod);
  }

  // go to the next col
  return solve_board(row, col + 1, step_count, mod);
}

