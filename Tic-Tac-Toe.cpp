#include <iostream>
#include <limits.h>

void printBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j];
            if (j < 2) std::cout << " | ";
        }
        std::cout << std::endl;
        if (i < 2) std::cout << "---------\n";
    }
}

bool isValidMove(char board[3][3], int row, int col) {
    return board[row][col] == ' ';
}

bool makeMove(char board[3][3], int position, char player) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    std::cout << "Making move at position " << position << " (row: " << row << ", col: " << col << ")\n";

    if (isValidMove(board, row, col)) {
        board[row][col] = player;
        return true;
    } else {
        std::cout << "Invalid move! Try again.\n";
        return false;
    }
}

bool checkWin(char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;

    return false;
}

bool checkTie(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

int main() {
    int mode;

    do {
        char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
        int position;
        char currentPlayer = 'X';
        bool gameWon = false;

        std::cout << "Welcome to Tic Tac Toe!\n";
        std::cout << "Choose game mode: \n1. Single Player (vs Computer)\n2. Two Players\n";
        
        while (true) {
            std::cin >> mode;
            if (mode == 1 || mode == 2) break;
            std::cout << "Invalid selection! Please choose 1 or 2.\n";
        }

        while (!gameWon) {
            printBoard(board);  // Print the board before each move
            bool validMove = false;

            if ((mode == 1 && currentPlayer == 'O') || mode == 2) {
                std::cout << "Player " << currentPlayer << ", choose a position (1-9): ";
                std::cin >> position;

                if (position < 1 || position > 9) {
                    std::cout << "Invalid position! Choose between 1 and 9.\n";
                    continue;
                }

                validMove = makeMove(board, position, currentPlayer);
            } else {
                std::cout << "The Computer thinks...\n";
                position = (rand() % 9) + 1; // Random for simplicity in single-player mode
                validMove = makeMove(board, position, 'X');
            }

            if (!validMove) continue;  // Skip to the next loop iteration if the move was invalid

            if (checkWin(board, currentPlayer)) {
                printBoard(board);
                std::cout << "Player " << currentPlayer << " wins!\n";
                gameWon = true;
            } else if (checkTie(board)) {
                printBoard(board);
                std::cout << "It's a draw!\n";
                gameWon = true;
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        char playAgain;
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;

        if (playAgain != 'y' && playAgain != 'Y') break;

    } while (true);

    std::cout << "Thanks for playing!\n";
    return 0;
}
