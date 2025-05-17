#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
const int SIZE = 9;
// Function to print the Sudoku board in a table format
void printBoard(const vector<vector<int>>& board) {
    cout << "\n+-------+-------+-------+" << endl;
    for (int i = 0; i < SIZE; ++i) {
        cout << "| ";
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0)
                cout << "  ";  // 2 spaces for empty cell
            else
                cout << board[i][j] << " ";
            if ((j + 1) % 3 == 0) cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0)
            cout << "+-------+-------+-------+" << endl;
    }
}
// Check if a number is safe to place in the cell
bool isValid(const vector<vector<int>>& board, int row, int col, int num) {
    for (int i = 0; i < SIZE; ++i) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[startRow + i][startCol + j] == num)
                return false;
    return true;
}
// Backtracking function to solve the Sudoku
bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board))
                            return true;
                        board[row][col] = 0; // Backtrack
                    }
                }
                return false; // Trigger backtracking
            }
        }
    }
    return true; // Solved!
}
// Get a row of input and validate it
bool getRowInput(vector<int>& row, int rowNum) {
    string line;
    cout << "Enter 9 numbers for Row " << rowNum + 1 << " (0 for empty cells): ";
    getline(cin, line);
    stringstream ss(line);
    int num;
    row.clear();
    while (ss >> num) {
        if (num < 0 || num > 9) {
            cout << "Invalid number detected! Use digits from 0 to 9 only.\n";
            return false;
        }
        row.push_back(num);
    }
    if (row.size() != SIZE) {
        cout << "You must enter exactly 9 numbers.\n";
        return false;
    }
    return true;
}
int main() {
    vector<vector<int>> board(SIZE, vector<int>(SIZE));
    cout << "Enter your Sudoku puzzle row by row (use 0 for empty cells & separate the numbers using spacebar):\n";

    // Input with validation
    for (int i = 0; i < SIZE; ++i) {
        while (!getRowInput(board[i], i)) {
            // Keep asking until valid input
        }
    }
    cout << "\nInput Sudoku Board:";
    printBoard(board);

    // Added spacing to improve UI clarity
    cout << "\nSolving...\n";

    if (solveSudoku(board)) {
        cout << "\nSolved Sudoku Board:";
        printBoard(board);
    } else {
        cout << "\nNo solution exists for the given Sudoku.\n";
    }

    return 0;
}