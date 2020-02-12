#ifndef FUNCS
#define FUNCS

extern char gameBoard[27];
extern char beginGame;

// functions: 
void greetAndInstruct();
void displayBoard(char board[]);
bool checkIfLegal(int cellNbre, char board[]);
bool checkWinner(char board[]);
void computerMove(char board[]);
void computerMoveMinMax(char board[]);

#endif