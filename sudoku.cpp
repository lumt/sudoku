#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* Pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

/* checks whether the board is full and returns true if yes */
bool is_complete(const char board[9][9]) {
  
  /* if any character is missing, it is incomplete */
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (!isdigit(board[row][col]))
	return false;
    }
  }
  /* else it must be complete */
  return true;
}

/* funtion to make a move on the sudoku board at position if valid else returns false */
bool make_move(const char pos[2], char value, char board[9][9]) {
  /* convert position from character type to int */
  int pos_row = pos[0] - 'A';
  int pos_col = (pos[1] - '0') - 1;
  
  if (is_legal_move(pos_row, pos_col, value, board)) {
    board[pos_row][pos_col] = value;
    return true;
  } else {
    return false;
  }
}

/* internal function for make_move: checks whether move is legal */
bool is_legal_move(int pos_row, int pos_col, char value, const char board[9][9]) {
  /* checks if out of range */
  if (pos_row < 0 || pos_row > 9) {
    return false;
  } else if (pos_col < 0 || pos_col > 9) {
    return false;
  }

  /* checks if move can be made per constraints */
  if (row_ok(pos_row, value, board) &&
      col_ok(pos_col, value, board) &&
      subboard_ok(pos_row, pos_col, value, board))
    return true;
  else
    return false;
}

/* internal functions for is_legal_move */
/* checks horizontally across the board */
bool row_ok(int pos_row, char value, const char board[9][9]) {
  for (int i = 0; i < 9; i++) {
    if (board[pos_row][i] == value)
      return false;
  }
  return true;
}

/* checks vertically */
bool col_ok(int pos_col, char value, const char board[9][9]) {
  for (int i = 0; i < 9; i++) {
    if (board[i][pos_col] == value)
      return false;
  }
  return true;
}

/* checks the particular subboard */
bool subboard_ok(int pos_row, int pos_col, char value, const char board[9][9]) {
  int sub_row = pos_row - (pos_row % 3);
  int sub_col = pos_col - (pos_col % 3);

  for (int i = sub_row, n = sub_row + 3; i < n; i++) {
    for (int j = sub_col, m = sub_col +3; j < m; j++) {
      if (board[i][j] == value) {
	return false;
      }
    }
  }
  return true;
}

						    
/* function to save the board to a given filename */
bool save_board(const char* filename, const char board[9][9]) {
  
  ofstream output(filename);
  
  if (!output) {
    cout << "Could not open file." << endl;
    return false;
  }
  assert(output);

  /* writes board to the file */
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      output << board[r][c];
    }
    output << endl;
  }

  output.close();
  return true;
}

/* function to solve the board if a solution exists */
bool solve_board(char board[9][9]) {

  /* counts number of recursion */
  static int counter = 0;
  counter++;
  
  if (is_complete(board)) {
    return true;
  } else {
    char board_copy[9][9];
    char value = '0';
    char pos[] = "A1";
  
    copy_board(board_copy, board);

    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 9; col++) {

	/* skips cells that are occupied */
	if (isdigit(board_copy[row][col]))
	  continue;

	/* otherwise, find appropriate value by iteration */
	for (int num = 1; num <= 9; num++) {
	  value = '0' + num;
	  pos[0] = 'A' + row;
	  pos[1] = '1' + col;

	  /* if a move could be made */
	  if (make_move(pos, value, board_copy)) {
	    /* tries to solve it using the current value and
	     * checks if board is complete by recursively calling itself */
	    if (solve_board(board_copy)) {
	      /* board has been solved, copies solution to original and returns true */
	      copy_board(board, board_copy);
	      if (counter != 0)
		cout << "solve_board has been called " << counter << " times." << endl;
	      counter = 0;
	      return true;
	    }
	  }
	}
	/* exhausted all moves for current cell
	 * return false to return control to previous stack call so it could
	 * iterate over other values for previous cells */
	return false;
      }
    }
    return false;
  }
}

/* function to copy board from one array to another */
void copy_board(char destination[9][9], const char source[9][9]) {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      destination[row][col] = source[row][col];
    }
  }
}





