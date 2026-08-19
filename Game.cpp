/*
    Mini Game Project - Tic Tac Toe
    ---------------------------------
    A console-based two-player Tic Tac Toe game in C++ demonstrating
    loops, arrays, and conditional logic.

    Features:
      - Dynamic board display after every move
      - Input validation (rejects out-of-range / already-taken cells)
      - Win detection (rows, columns, diagonals) and draw detection
      - Replay option after each game

    Compile:  g++ -o tictactoe TicTacToe.cpp
    Run:      ./tictactoe
*/

#include <iostream>
#include <limits>
using namespace std;

const int SIZE = 3;

// ----------------------------------------------------------------
// Print the current board with cell numbers 1-9 for empty cells
// ----------------------------------------------------------------
void displayBoard(char board[SIZE][SIZE]) {
    cout << "\n";
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cout << " " << board[row][col] << " ";
            if (col < SIZE - 1) cout << "|";
        }
        cout << "\n";
        if (row < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

// ----------------------------------------------------------------
// Initialize board cells with numbers 1-9 (acts as move labels)
// ----------------------------------------------------------------
void initializeBoard(char board[SIZE][SIZE]) {
    int num = 1;
    for (int row = 0; row < SIZE; row++)
        for (int col = 0; col < SIZE; col++)
            board[row][col] = '0' + num++;
}

// ----------------------------------------------------------------
// Read and validate a move (1-9), convert to row/col, apply it
// ----------------------------------------------------------------
void makeMove(char board[SIZE][SIZE], char playerSymbol) {
    int choice;

    while (true) {
        cout << "Player " << playerSymbol << ", enter a cell number (1-9): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice < 1 || choice > 9) {
            cout << "Please enter a number between 1 and 9.\n";
            continue;
        }

        int row = (choice - 1) / SIZE;
        int col = (choice - 1) % SIZE;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "That cell is already taken. Choose another.\n";
            continue;
        }

        board[row][col] = playerSymbol;
        break;
    }
}

// ----------------------------------------------------------------
// Check rows, columns, and diagonals for a winning line
// ----------------------------------------------------------------
bool checkWin(char board[SIZE][SIZE], char playerSymbol) {
    // Rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == playerSymbol && board[i][1] == playerSymbol && board[i][2] == playerSymbol)
            return true;
        if (board[0][i] == playerSymbol && board[1][i] == playerSymbol && board[2][i] == playerSymbol)
            return true;
    }

    // Diagonals
    if (board[0][0] == playerSymbol && board[1][1] == playerSymbol && board[2][2] == playerSymbol)
        return true;
    if (board[0][2] == playerSymbol && board[1][1] == playerSymbol && board[2][0] == playerSymbol)
        return true;

    return false;
}

// ----------------------------------------------------------------
// Board is full when no cell still holds its original number label
// ----------------------------------------------------------------
bool isBoardFull(char board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++)
        for (int col = 0; col < SIZE; col++)
            if (board[row][col] != 'X' && board[row][col] != 'O')
                return false;
    return true;
}

// ----------------------------------------------------------------
// Play a single game; returns true if the player wants to replay
// ----------------------------------------------------------------
bool playGame() {
    char board[SIZE][SIZE];
    initializeBoard(board);

    char currentPlayer = 'X';
    bool gameWon = false;

    displayBoard(board);

    for (int turn = 0; turn < SIZE * SIZE && !gameWon; turn++) {
        makeMove(board, currentPlayer);
        displayBoard(board);

        if (checkWin(board, currentPlayer)) {
            cout << "Player " << currentPlayer << " wins! Congratulations!\n";
            gameWon = true;
            break;
        }

        if (isBoardFull(board)) {
            cout << "It's a draw! The board is full.\n";
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    char replay;
    cout << "Do you want to play again? (y/n): ";
    cin >> replay;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return (replay == 'y' || replay == 'Y');
}

// ----------------------------------------------------------------
// Main function
// ----------------------------------------------------------------
int main() {
    cout << "===== TIC TAC TOE =====\n";
    cout << "Player 1: X   Player 2: O\n";
    cout << "Enter the cell number (1-9) to place your mark:\n";
    cout << " 1 | 2 | 3 \n --+---+---\n 4 | 5 | 6 \n --+---+---\n 7 | 8 | 9 \n";

    bool playAgain = true;
    while (playAgain) {
        playAgain = playGame();
    }

    cout << "Thanks for playing!\n";
    return 0;
}
