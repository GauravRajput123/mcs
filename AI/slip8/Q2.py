def check_winner(board):
    # Check rows
    for row in board:
        if all(cell == 'X' for cell in row):
            return 'X'
        elif all(cell == 'O' for cell in row):
            return 'O'

    # Check columns
    for col in range(3):
        if all(board[row][col] == 'X' for row in range(3)):
            return 'X'
        elif all(board[row][col] == 'O' for row in range(3)):
            return 'O'

    # Check diagonals
    if all(board[i][i] == 'X' for i in range(3)) or all(board[i][2 - i] == 'X' for i in range(3)):
        return 'X'
    elif all(board[i][i] == 'O' for i in range(3)) or all(board[i][2 - i] == 'O' for i in range(3)):
        return 'O'

    return None

def check_tie(board):
    return all(cell != ' ' for row in board for cell in row)

def print_board(board):
    for row in board:
        print(" | ".join(row))
        print("-" * 9)

def tic_tac_toe():
    board = [[' ' for _ in range(3)] for _ in range(3)]
    player = 'X'

    while True:
        print_board(board)
        row, col = map(int, input(f"Player {player}, enter your move (row col): ").split())

        if board[row][col] == ' ':
            board[row][col] = player
        else:
            print("Invalid move. Cell already occupied. Try again.")
            continue

        winner = check_winner(board)
        if winner:
            print_board(board)
            print(f"Player {winner} wins!")
            break

        if check_tie(board):
            print_board(board)
            print("It's a tie!")
            break

        player = 'O' if player == 'X' else 'X'

if __name__ == "__main__":
    tic_tac_toe()
