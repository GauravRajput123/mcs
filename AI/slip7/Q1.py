import math

def print_board(board):
    for row in board:
        print(" ".join(row))
    print()

def is_winner(board, player):
    for row in board:
        if all(cell == player for cell in row):
            return True

    for col in range(3):
        if all(board[row][col] == player for row in range(3)):
            return True

    if all(board[i][i] == player for i in range(3)) or all(board[i][2 - i] == player for i in range(3)):
        return True

    return False

def is_full(board):
    return all(cell != ' ' for row in board for cell in row)

def get_winner(board):
    if is_winner(board, 'X'):
        return 'X'
    elif is_winner(board, 'O'):
        return 'O'
    else:
        return None

def evaluate(board):
    winner = get_winner(board)
    if winner == 'X':
        return 1
    elif winner == 'O':
        return -1
    elif is_full(board):
        return 0
    else:
        return None

def minimax(board, depth, alpha, beta, maximizing_player):
    score = evaluate(board)

    if score is not None:
        return score

    if maximizing_player:
        max_eval = -math.inf
        for i in range(3):
            for j in range(3):
                if board[i][j] == ' ':
                    board[i][j] = 'X'
                    eval = minimax(board, depth + 1, alpha, beta, False)
                    board[i][j] = ' '
                    max_eval = max(max_eval, eval)
                    alpha = max(alpha, eval)
                    if beta <= alpha:
                        break
        return max_eval
    else:
        min_eval = math.inf
        for i in range(3):
            for j in range(3):
                if board[i][j] == ' ':
                    board[i][j] = 'O'
                    eval = minimax(board, depth + 1, alpha, beta, True)
                    board[i][j] = ' '
                    min_eval = min(min_eval, eval)
                    beta = min(beta, eval)
                    if beta <= alpha:
                        break
        return min_eval

def find_best_move(board):
    best_val = -math.inf
    best_move = (-1, -1)

    for i in range(3):
        for j in range(3):
            if board[i][j] == ' ':
                board[i][j] = 'X'
                move_val = minimax(board, 0, -math.inf, math.inf, False)
                board[i][j] = ' '

                if move_val > best_val:
                    best_move = (i, j)
                    best_val = move_val

    return best_move

def main():
    board = [[' ' for _ in range(3)] for _ in range(3)]
    current_player = 'X'

    while True:
        print_board(board)

        if current_player == 'X':
            move = find_best_move(board)
            print("Computer plays X at position:", move)
        else:
            move = tuple(map(int, input("Enter your move (row column): ").split()))

        if board[move[0]][move[1]] == ' ':
            board[move[0]][move[1]] = current_player
            winner = get_winner(board)
            if winner:
                print_board(board)
                print(f"{winner} wins!")
                break
            elif is_full(board):
                print_board(board)
                print("It's a tie!")
                break
            else:
                current_player = 'O' if current_player == 'X' else 'X'
        else:
            print("Invalid move. Try again.")

if __name__ == "__main__":
    main()