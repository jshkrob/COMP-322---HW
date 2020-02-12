#include<iostream>
#include "functions.h"
using namespace std;

int main() {
    int playerMove;
    greetAndInstruct();

    if (beginGame == 'y') {
        // initiate game loop:
        while(!checkWinner(gameBoard)) {
            // extract valid move:
            do {
                cout << "Input your move here: ";
                cin >> playerMove;
                cout << endl;
            } while (!checkIfLegal(playerMove, gameBoard));

            // user = 'X' and computer = 'O'
            gameBoard[playerMove  - 1] = 'X'; 
            cout << "Player's move: " << endl;
            displayBoard(gameBoard);

            computerMove(gameBoard); 
            cout << "Computer's move: " << endl;
            displayBoard(gameBoard);
        }
        cout << " Thanks for playing!" << endl;
        return 0;
    }
    
}




