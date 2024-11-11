def is_safe(board, row, col):
    # Check if there is a queen in the same row
    if any(board[row][c] == 1 for c in range(col)):
        return False

    # Check upper diagonal on the left side
    if any(board[r][c] == 1 for r, c in zip(range(row, -1, -1), range(col, -1, -1))):
        return False

    # Check lower diagonal on the left side
    if any(board[r][c] == 1 for r, c in zip(range(row, len(board)), range(col, -1, -1))):
        return False

    return True

def solve_n_queens_util(board, col):
    if col >= len(board):
        return True

    for row in range(len(board)):
        if is_safe(board, row, col):
            board[row][col] = 1

            if solve_n_queens_util(board, col + 1):
                return True

            board[row][col] = 0

    return False

def solve_n_queens(n):
    board = [[0] * n for _ in range(n)]

    if solve_n_queens_util(board, 0):
        print("Solution found:")
        for row in board:
            print(" ".join("Q" if cell == 1 else "." for cell in row))
    else:
        print("No solution found.")

if __name__ == "__main__":
    solve_n_queens(4)