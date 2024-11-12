def print_solution(board):
    for row in board:
        print(" ".join("Q" if cell else "." for cell in row))
    print("\n")

def is_safe(board, row, col, n):
    # Check if there is a queen in the same row
    if any(board[row][c] for c in range(col)):
        return False

    # Check upper diagonal on the left side
    if any(board[r][c] for r, c in zip(range(row, -1, -1), range(col, -1, -1))):
        return False

    # Check lower diagonal on the left side
    if any(board[r][c] for r, c in zip(range(row, n), range(col, -1, -1))):
        return False

    return True

def solve_n_queens_util(board, col, n):
    if col >= n:
        print_solution(board)
        return True

    res = False
    for i in range(n):
        if is_safe(board, i, col, n):
            board[i][col] = 1

            res = solve_n_queens_util(board, col + 1, n) or res

            board[i][col] = 0

    return res

def solve_n_queens(n):
    board = [[0] * n for _ in range(n)]

    if not solve_n_queens_util(board, 0, n):
        print(f"No solution for {n}-Queens.")

if __name__ == "__main__":
    n = int(input("Enter the value of N for N-Queens: "))
    solve_n_queens(n)