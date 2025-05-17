def is_valid(board, row, col, num):
    # Check row
    for x in range(9):
        if board[row][x] == num:
            return False

    # Check column
    for x in range(9):
        if board[x][col] == num:
            return False

    # Check 3x3 box
    start_row = row - row % 3
    start_col = col - col % 3
    for i in range(3):
        for j in range(3):
            if board[start_row + i][start_col + j] == num:
                return False

    return True

def solve_sudoku(board):
    for row in range(9):
        for col in range(9):
            if board[row][col] == 0:
                for num in range(1, 10):
                    if is_valid(board, row, col, num):
                        board[row][col] = num
                        if solve_sudoku(board):
                            return True
                        board[row][col] = 0  # backtrack
                return False
    return True

def print_board(board):
    print("\n+-------+-------+-------+")
    for i in range(9):
        print("|", end=" ")
        for j in range(9):
            cell = board[i][j] if board[i][j] != 0 else " "
            print(cell, end=" ")
            if (j + 1) % 3 == 0:
                print("|", end=" ")
        print()
        if (i + 1) % 3 == 0:
            print("+-------+-------+-------+")

def get_user_input():
    print("Enter the Sudoku puzzle row by row (use 0 for empty cells & separate the numbers using spacebar):")
    board = []
    for i in range(9):
        while True:
            row = input(f"Row {i+1}: ").strip().split()
            if len(row) != 9 or not all(num.isdigit() and 0 <= int(num) <= 9 for num in row):
                print("Invalid input. Please enter 9 numbers between 0 and 9.")
            else:
                board.append([int(num) for num in row])
                break
    return board

# Main flow
sudoku_board = get_user_input()
print("\nInput Sudoku Board:")
print_board(sudoku_board)

if solve_sudoku(sudoku_board):
    print("\nSolved Sudoku Board:")
    print_board(sudoku_board)
else:
    print("\nNo solution exists for the given Sudoku.")