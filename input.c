#include "input.h"
#include "board.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


// Constants
static char const SOLVE_CHAR = 'S';
static char const QUIT_CHAR = 'Q';


/* ----------------------------------------------------------------
   static bool is_digit(c)
   ----------------------------------------------------------------
   Purpose: returns true if the char is a digit, false otherwise
   --------------------------------------------------------------*/
static bool is_digit(char c) {
  if ((c >= '0') && (c <= '9')) {
    return true;
  }

  return false;
}


/* ----------------------------------------------------------------
   static void row_numbers_input(row)
   ----------------------------------------------------------------
   Purpose: read the numbers for the specified row and store it
            at the specified row
   require: 1 <= row <= 9;
   effects: prints to the screen
            reads input
            mutates BOARD
   --------------------------------------------------------------*/
static void row_numbers_input(int row) {
  assert(row >= 1);
  assert(row <= 9);

  int maxlen = 16;
  
  // allocate memory for the input char arr (for row's numbers)
  char *input = malloc(maxlen * sizeof(char));
  if (input == NULL) {
    printf("Heap ran out of memory, terminating program\n");
    exit(EXIT_SUCCESS);
  }

  while (true) {
    // print the instructions to input the row's numbers
    printf("(Valid inputs: 0-9. 0 represents unknown tile. ");
    printf("No need to enter trailing 0)\n");
    printf("Enter Row %d's numbers: ", row);

    // fill the first 9 spot with '0'
    for (int i = 0; i < 9; i++) {
      input[i] = '0';
    }

    // set up variables for reading the row numbers
    int current_i = -1;
    bool read_success = true;

    do {
      current_i++;

      // double the size of the string if needed    
      if (current_i >= maxlen) {
        maxlen *= 2;

        input = realloc(input, maxlen * sizeof(char));
        if (input == NULL) {
          printf("Heap ran out of memory, ");
          printf("terminating program\n");
          exit(EXIT_SUCCESS);
        }
      }

      scanf("%c", &(input[current_i]));

      // if the input contain anything besides
      // newline or digit, the input is invalid
      if (!is_digit(input[current_i]) &&
          input[current_i] != 10) {
        read_success = false;
      }

      // loop until the newline token is reached
    } while (input[current_i] != 10);

    // mutate the newline token to '0'
    input[current_i] = '0';

    // if the char arr is valid, break
    if (read_success) {
      break;
    }

    // invalid inputs, ask for the row's numbers again
    printf("Input must only contain 0-9, try again\n");
  }

  // store the valid digit arr into the board
  row--;
  store_at_row(row, input);
  free(input);

  // print the current state of the board
  printf("Current board state:\n");
  print_board();

  return;
}


// see input.h for details
void user_input(void) {
  // keep reading user inputs until break (row number, S, Q)
  while (true) {
    char row_select = 0;
    char second_char = 0;

    printf("(Valid inputs: 1-9, S to solve, Q to quit)\n");
    printf("Which row do you want to modify? ");
    scanf("%c", &row_select);

    if (row_select == 10) {
      printf("Invalid input, try again\n");
      continue;
    }

    scanf("%c", &second_char);

    // ensure the second char is the newline token
    if (second_char == 10) {
      // if the user wants to quit the program
      if (row_select == QUIT_CHAR) {
        printf("Program terminated\n");
        exit(EXIT_SUCCESS);
        return;
      }

      // if the user is done inputting, free and return
      if (row_select == SOLVE_CHAR) {
        return;
      }

      // if the row number is invalid, ask for input again
      if (row_select > '9' || row_select < '1') {
        printf("Invalid input, try again\n");
        continue;
      }
    }
    else {
      // read the remaining garbage value
      while (true) {
        scanf("%c", &row_select);
        if (row_select == 10) {
          break;
        }
      }

      // Invalid inputs, ask for input again
      printf("Invalid input, try again\n");
      continue;
    }

    int row = char_to_int(row_select);

    // read the row's number and store it
    row_numbers_input(row);

    // loop to select a new operation
  }

  // should never reach here
  return;
}


// see input.h for details
void print_input(int *mod) {
  assert(mod);

  *mod = -1;
  char second_char = 0;

  while (true) {
    printf("(Valid inputs: Any non-negative integer ");
    printf("(0 means no steps shown))\n");
    printf("Input how often you want to see the board: ");

    // read the first integer encountered
    int retval = scanf("%d", mod);

    if (retval != 1) {
      // read the remaining garbage value
      while (true) {
        scanf("%c", &second_char);
        if (second_char == 10) {
          break;
        }
      }
      printf("Invalid input, try again\n");
      continue;
    }

    scanf("%c", &second_char);

    // ensure the second char is the newline token
    if (second_char == 10) {
      // check if the integer is not negative
      if (*mod > 0) {
        printf("Board will print every %d steps\n", *mod);
        return;
      }

      // show no steps
      if (*mod == 0) {
        printf("No steps will be shown\n");
        return;
      }

      // mod is negative, loop back
      printf("Invalid input, try again\n");
    }
    else {
      // read the remaining garbage value
      while (true) {
        scanf("%c", &second_char);
        if (second_char == 10) {
          break;
        }
      }
    }
    
    // invalid input, loop back
  }

  // should never reach here
  return;
}
