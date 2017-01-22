#include <iostream>
#include <cstdio>
#include "sudoku.h"
#include <ctime>

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  cout << "====================== Question 1 ======================" << endl << endl;

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  cout << "====================== Question 2 ======================" << endl << endl;


  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move." << endl;

  // write more tests
  cout << "Putting '1' into B3 is ";
  if (!make_move("B3", '1', board)) 
    cout << "NOT ";
  cout << "a valid move." << endl;

  cout << "Putting '6' into A1 is ";
  if (!make_move("A1", '6', board)) 
    cout << "NOT ";
  cout << "a valid move." << endl;

  cout << "Putting '9' into E9 is ";
  if (!make_move("E9", '9', board)) 
    cout << "NOT ";
  cout << "a valid move." << endl;

  cout << "Putting '5' into E5 is ";
  if (!make_move("E5", '5', board)) 
    cout << "NOT ";
  cout << "a valid move." << endl;

  cout << "Putting '8' into H3 is ";
  if (!make_move("H3", '8', board)) 
    cout << "NOT ";
  cout << "a valid move." << endl;

  cout << "Putting '7' into F9 is ";
  if (!make_move("F9", '7', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is: " << endl;
  display_board(board);


  cout << "====================== Question 3 ======================" << endl << endl;

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  cout << "====================== Question 4 ======================" << endl << endl;

  double t_delta;
  cout.precision(3);
  cout.setf(ios::fixed);
  
  load_board("easy.dat", board);
  t_delta = clock();
  if (solve_board(board)) {
    t_delta = clock() - t_delta;
    cout << "The 'easy' board has a solution:" << endl;
    cout << "Time elapsed = " << t_delta / CLOCKS_PER_SEC << "ms." << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("medium.dat", board);
  t_delta = clock();
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    t_delta = clock() - t_delta;
    cout << "Time elapsed = " << t_delta / CLOCKS_PER_SEC*1000 << "ms." << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;
  
  cout << "====================== Question 5 ======================" << endl << endl;

  // write more tests

  load_board("mystery3.dat", board);
  t_delta = clock();
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << endl;
    t_delta = clock() - t_delta;
    cout << "Time elapsed = " << t_delta / CLOCKS_PER_SEC*1000 << "ms." << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;
  
  load_board("mystery1.dat", board);
  t_delta = clock();
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << endl;
    t_delta = clock() - t_delta;
    cout << "Time elapsed = " << t_delta / CLOCKS_PER_SEC*1000 << "ms." << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("mystery2.dat", board);
  t_delta = clock();
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << endl;
    t_delta = clock() - t_delta;
    cout << "Time elapsed = " << t_delta << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
    t_delta = clock() - t_delta;
    cout << "Time elapsed = " << t_delta / CLOCKS_PER_SEC*1000 << "ms." << endl;
  cout << endl;
  display_board(board);

  return 0;
}
