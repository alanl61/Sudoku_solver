#include "board.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Global Varaible
static int BOARD[9][9];


// see board.h for details
int char_to_int(char c) {
  if (c == '0') {
    return 0;
  }
  else if (c == '1') {
    return 1;
  }
  else if (c == '2') {
    return 2;
  }
  else if (c == '3') {
    return 3;
  }
  else if (c == '4') {
    return 4;
  }
  else if (c == '5') {
    return 5;
  }
  else if (c == '6') {
    return 6;
  }
  else if (c == '7') {
    return 7;
  }
  else if (c == '8') {
    return 8;
  }
  else if (c == '9') {
    return 9;
  }
  else {
    return -1;
  }
}


// see board.h for details
int get_val(int row, int col) {
  assert(row <= 8);
  assert(row >= 0);
  assert(col <= 8);
  assert(col >= 0);
  return BOARD[row][col];
}


// see board.h for details
void print_board(void) {
  printf("=====================================\n");

  // print the first 3 boxes
  for (int r = 0; r < 3; r++) {
    printf("|");
    for (int c = 0; c < 9; c++) {
      int num = BOARD[r][c];
      if (num == 0) {
        printf("   |");
      }
      else {
        printf(" %d |", num);
      }
    }

    if (r == 2) {
      printf("\n============+===========+============\n");
      break;
    }

    printf("\n|-----------|-----------|-----------|\n");
  }

  // print the second 3 boxes
  for (int r = 3; r < 6; r++) {
    printf("|");
    for (int c = 0; c < 9; c++) {
      int num = BOARD[r][c];
      if (num == 0) {
        printf("   |");
      }
      else {
        printf(" %d |", num);
      }
    }

    if (r == 5) {
      printf("\n============+===========+============\n");
      break;
    }

    printf("\n|-----------|-----------|-----------|\n");
  }

  // print the third 3 boxes
  for (int r = 6; r < 9; r++) {
    printf("|");
    for (int c = 0; c < 9; c++) {
      int num = BOARD[r][c];
      if (num == 0) {
        printf("   |");
      }
      else {
        printf(" %d |", num);
      }
    }

    if (r == 8) {
      printf("\n=====================================\n\n");
      break;
    }

    printf("\n|-----------|-----------|-----------|\n");
  }

  return;
}


// see board.h for details
void store_at_pos(int row, int col, int val) {
  assert(row <= 8);
  assert(row >= 0);
  assert(col <= 8);
  assert(col >= 0);
  BOARD[row][col] = val;
  return;
}


// see board.h for details
bool store_at_row(int row, char *digit_arr) {
  assert(digit_arr);
  assert(row <= 8);
  assert(row >= 0);

  for (int i = 0; i < 9; i++) {
    BOARD[row][i] = char_to_int(digit_arr[i]);
  }

  return true;
}