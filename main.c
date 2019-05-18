#include "input.h"
#include "solver.h"
#include "board.h"
#include <stdio.h>

int main(void) {
  int step_count = 0;
  int mod = 0;
  
  printf("Welcome to Sudoku Solver!\n");
  
  printf("Input the sudoku board you want to solve\n");
  // print the empty board
  print_board();
  // ask user for sudoku board input
  user_input();
  
  // ask user for how often to print the board
  print_input(&mod);

  // begin the backtracking solver //
  
  // if successful
  if (solve_board(0, 0, &step_count, mod)) {
    printf("Solved! Took %d steps:\n", step_count);
    print_board();
    return 0;
  }
  
  // if failed
  printf("Unable to solve this sudoku:\n");
  print_board();
  return 0;
}
