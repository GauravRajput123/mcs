def is_safe(board, row, col):
    # Check for queens in the same column
    for i in range(row):
        if board[i] == col:
            return False

    # Check for queens on the left diagonal
    for i, j in zip(range(row - 1, -1, -1), range(col - 1, -1, -1)):
        if board[i] == j:
            return False

    # Check for queens on the right diagonal
    for i, j in zip(range(row - 1, -1, -1), range(col + 1, len(board))):
        if board[i] == j:
            return False

    return True

def solve_n_queens(board, row, solutions):
    if row == len(board):
        # Solution found; store it
        solution = []
        for i in range(len(board)):
            row_str = ['.'] * len(board)
            row_str[board[i]] = 'Q'
            solution.append("".join(row_str))
        solutions.append(solution)
        return

    for col in range(len(board)):
        if is_safe(board, row, col):
            board[row] = col
            solve_n_queens(board, row + 1, solutions)
            board[row] = -1  # Backtrack

def solve_8_queens():
    # Initialize board and solutions list
    board = [-1] * 8
    solutions = []
    solve_n_queens(board, 0, solutions)
    
    # Print all solutions
    print(f"Total solutions: {len(solutions)}\n")
    for solution in solutions:
        for row in solution:
            print(row)
        print()

# Run the 8-Queens solution finder
solve_8_queens()

