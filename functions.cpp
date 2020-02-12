#include<iostream>
#include<string.h>
#include "functions.h"
using namespace std;

// global variables
char winner;
char gameBoard[27] = "";
char beginGame = '0';
bool verbalMode = true;

// additional helper functions:
bool isFull(char board[]) {
    int i = 0;
    while (i <= 26) {
        if (board[i] == ' ') return false;
        else i++;
    }
    return true;
}

void greetAndInstruct() {
    cout << "HELLO! Welcome to Tic=Tac-Toe challenge. Player verus Computer. The ultimate competition" << endl;
    cout << "The board is numbered from 1 to 27 as per the following:" << endl;
    displayBoard(gameBoard);
    cout << "Player will start first. Simply input the number of the cell you want to occupy. Player's move is marked with X. Computer's move is marked with O" << endl;
    cout << "START? (y/n): ";
    memset(gameBoard, ' ', 27); gameBoard[27] = '\0';
    cin >> beginGame;
}

void displayBoard(char board[]){
    // prints out to screen game board reflecting current status
    // of game; for new game, board is empty except for the cel numbers
    // displayBoard function reflects new status w/ X's and O's where appropriate
    if (beginGame == '0'){
        // print a row:
        for (int i = 1; i <= 7; i+=3) { // 1, 4, 7...
            // print 3 groupings;            
            for(int j = 0; j < 3; j++) {
                cout << i+(9*j) << " | " << (i+1)+(9*j) << " | " << (i+2)+(9*j); 
                cout << "         ";
            }
            cout << endl;
            if (i != 7) {    
                for (int j = 0; j < 3; j++) {                    
                    if (j == 0) {cout << "---------" << "         ";}
                    else {cout << "------------" << "         ";}
                }
                cout << endl;
            }
        }
    } else {
        // print current board peices:
        // assume that first 1-9 elements of board correspond to peices of first board, ....
        for (int i = 0; i <= 6; i+=3) { // 1, 4, 7...
            // print 3 groupings;            
            for(int j = 0; j < 3; j++) {
                cout << board[i+(9*j)] << " | " << board[i+1+(9*j)] << " | " << board[(i+2)+(9*j)]; 
                cout << "         ";
            }
            cout << endl;
            if (i != 7) {    
                for (int j = 0; j < 3; j++) {                    
                   cout << "---------" << "         ";
                }
                cout << endl;
            }
        }
        cout << endl;
    }
}

bool checkIfLegal (int cellNbre, char board[]){
    if (cellNbre <= 0 || cellNbre >= 28) {
        cout << " ***Error***: cell number entered is out of bounds. Please input a different cell: " << endl;
        return false;
    } else if (board[cellNbre-1] != ' ') {
        cout << "***Error***: cell is occupied by a peice. Please try again: " << endl;
        return false;
    } else {return true;}
}

bool checkWinner(char board[]){
    bool solExists = false; 
    char chk[2] = {'X', 'O'};

    // tie conditional
    if (isFull(board)) {
        cout << "The board is full: tie game!!!";
        return false;
    }

    // O(n^2) checking: each row in each singularly and all possible other row combinations
    for (int plyr = 0; plyr < 2; plyr++) {
        //same spots:
        for(int i = 0; i <= 8; i++) {
            solExists = (board[i] == chk[plyr] && board[i] == board[i+9] && board[i+9] == board[i+18]);
            if (solExists) { 
                if (verbalMode) cout << "Player " << chk[plyr] << " has just won the game with a same-spot match!!!";
                winner = plyr;
                return solExists;
            }
        }
    
        // rows:
        for (int i = 0; i <= 6; i+=3) {
            for (int j = 0; j <= 18; j+=9) {
                solExists = (board[i+j] == chk[plyr] && board[i+j] == board[i+j+1] && board[i+j+1] == board[i+j+2]);
                if (solExists){ 
                    if (verbalMode) cout << "Player " << chk[plyr] << " has just won the game with a row match!!!";                   
                    winner = plyr;
                    return solExists;
                }
            }
            // rows across boards
            solExists = (board[i] == chk[plyr] && board[i] == board[(i+1)+9] && board[(i+1)+9] == board[(i+2)+18]);
            if (solExists){ 
                if (verbalMode) cout << "Player " << chk[plyr] << " has just won the game with a row match!!!";
                winner = plyr;
                return solExists;
            }
                
            solExists = (board[i+2] == chk[plyr] && board[i+2] == board[(i+1)+9] && board[(i+1)+9] == board[i+18]);
            if (solExists){ 
                if (verbalMode) cout << "Player " << chk[plyr] << " has just won the game with a row match!!!";
                winner = plyr;
                return solExists;
            }
        }

        // columns:
        for (int i = 0; i<=18; i+=9) { // loop through 3 boards
            for(int j = i; j < i+3; j++) {
                solExists = (board[j] == chk[plyr] && board[j] == board[j+3] && board[j+3] == board[j+6]);
                if (solExists){ 
                    if (verbalMode) cout << "Player " << chk[plyr] << " has just won the game with a column match!!!";
                    winner = plyr;
                    return solExists;
                }
            }
        }            
        // columns across boards:
        for (int i = 0; i < 3; i++) {
            solExists = (board[i] == chk[plyr] && board[i] == board[i+12] && board[i+12] == board[i+24]);
            if (solExists){ 
                if (verbalMode) cout << "Player " << chk[plyr] << " has just won the game with a column match!!!";
                winner = plyr;
                return solExists;
            }
            solExists = (board[i+6] == chk[plyr] && board[i+6] == board[i+12] && board[i+12] == board[i+18]);
            if (solExists){ 
                if (verbalMode) cout << "Player " << chk[plyr] << " has just won the game with a column match!!!";
                winner = plyr;
                return solExists;
            } 
        }
        // diagonols:
        for (int i = 0; i<=18; i+=9) {
            solExists = (board[i] == chk[plyr] && (board[i]==board[i+4] && board[i+4]==board[i+8])) || (board[i+2] == chk[plyr] && (board[i+2]==board[i+4] && board[i+4]==board[i+6]));
            if (solExists){ 
                if (verbalMode) cout << "Player " << chk[plyr] << " has just won the game with a diagonol match!!!";
                winner = plyr;
                return solExists;
            }

            // 3 panel diagonols:
            if (i == 0) {
                solExists = (board[i] == chk[plyr] && (board[i]==board[i+4 + 9] && board[i+4 + 9]==board[i+8 + 18])) || (board[i+6] == chk[plyr] && (board[i+6]==board[i+4 + 9] && board[i+4 +9]==board[i+2 + 18]));
                if (solExists){ 
                    if (verbalMode) cout << "Player " << chk[plyr] << " has just won the game with a diagonol match!!!";
                    winner = plyr;
                    return solExists;
                }
            }
        }
    }
}

// Attempted to use MINMAX: 

// We will use a MINMAX algorithm for the computer's next move, with limit on
// the number of branches available to the algorithm to predict its next move
int minimax(char board[], int depth, bool maximizingPlayer) {
    // assume Computer is MAXIMIZING player 
    if (depth == 0 || checkWinner(board)) {
        if (winner == 'O') {return 1;}
        else if (isFull(board)) {return 0;} 
        else {return -1;}
    } else if (maximizingPlayer) {
        int maxEval = -10000000;
        for(int i = 0; i < 27; i++) {
            if (board[i] == '\0') {
                char childBoard[30]; strncpy(childBoard, board, 27);
                childBoard[i] = 'O';
                int eval = minimax(childBoard, depth-1, false);
                if (eval > maxEval) maxEval = eval;
            }
        }
        return maxEval;
    } else {
        int minEval = 10000000;
        for(int i = 0; i < 27; i++) {
            if (board[i] == '\0') {
                char childBoard[30]; strncpy(childBoard, board, 27);
                childBoard[i] = 'X';
                int eval = minimax(childBoard, depth-1, true);
                if (eval < minEval) minEval = eval;
            }
        }
        return minEval;
    }
    return 1;
}

void computerMove(char board[]){
    int score = -10000000, bestMv = -1, limitDepth  = 3;
    bool didWin= false;
    verbalMode = false;
    // look at all possible solutions for move 'O'
    for(int i = 0; i < 27; i++) {
        if (board[i] == ' ') {
            board[i] = 'O'; // try this solution
            didWin = checkWinner(board);
            if (didWin) {
                bestMv = i; 
            } 
            board[i] = ' '; // undo
            /*
            int currScore = minimax(board, limitDepth, true); // returns +1 or -1
            cout << currScore << endl;
            if (currScore >= score) {
                score = currScore;
                bestMv = i;
            }
            */
        }
    }

    if (!didWin) {
        // loop through all possible 'X' moves and find the one that is necissary for 'X'
        // to win and BLOCK that move:
        for(int i = 0; i < 27; i++) {
            if (board[i] == ' ') {
                board[i] = 'X'; 
                didWin = checkWinner(board);
                if (didWin) {
                    // block this move
                    bestMv = i; 
                }
                board[i] = ' ';
                
            }
        }
        if (bestMv == - 1) {
            int i = 0; 
            while (board[i] != ' ') {i++;}
            board[i] = 'O';
            return;
        }
        
    } 

    board[bestMv] = 'O';
    verbalMode = true;
}
