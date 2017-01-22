#ifndef SUDOKU_H
#define SUDOKU_H

/* function declarations */
void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
void print_frame(int row);
void print_row(const char* data, int row);
bool is_complete(const char board[9][9]);
bool make_move(const char pos[2], char value, char board[9][9]);
bool is_legal_move(int pos_row, int pos_col, char value, const char board[9][9]);
bool row_ok(int pos_row, char value, const char board[9][9]);
bool col_ok(int pow_col, char value, const char board[9][9]);
bool subboard_ok(int pow_row, int pow_col, char value, const char board[9][9]);
bool save_board(const char* filename, const char board[9][9]);
bool solve_board(char board[9][9]);
void copy_board(char destination[9][9], const char source[9][9]);

#endif
