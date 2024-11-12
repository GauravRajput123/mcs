import heapq

# Define the goal state
goal_state = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 0]
]

# Define the possible moves (up, down, left, right)
moves = {
    'up': (-1, 0),
    'down': (1, 0),
    'left': (0, -1),
    'right': (0, 1)
}

# Helper function to find the position of a tile
def find_position(puzzle, value):
    for i, row in enumerate(puzzle):
        if value in row:
            return i, row.index(value)
    return None

# Helper function to create a new state after a move
def move_tile(puzzle, pos0, move):
    new_puzzle = [row[:] for row in puzzle]
    i, j = pos0
    di, dj = move
    ni, nj = i + di, j + dj
    # Swap the 0 tile with the adjacent tile in the move direction
    if 0 <= ni < 3 and 0 <= nj < 3:
        new_puzzle[i][j], new_puzzle[ni][nj] = new_puzzle[ni][nj], new_puzzle[i][j]
        return new_puzzle
    return None

# Heuristic function: Manhattan Distance
def heuristic(puzzle):
    distance = 0
    for i in range(3):
        for j in range(3):
            value = puzzle[i][j]
            if value != 0:
                target_i, target_j = divmod(value - 1, 3)
                distance += abs(i - target_i) + abs(j - target_j)
    return distance

# A* algorithm for solving the 8-puzzle problem
def a_star(start):
    # Priority queue and visited set
    priority_queue = []
    heapq.heappush(priority_queue, (0, start, []))
    visited = set()
    visited.add(tuple(map(tuple, start)))

    while priority_queue:
        cost, current, path = heapq.heappop(priority_queue)
        # Check if the goal state is reached
        if current == goal_state:
            return path
        
        # Find the position of the blank tile (0)
        pos0 = find_position(current, 0)

        # Explore possible moves
        for move_name, move_delta in moves.items():
            new_state = move_tile(current, pos0, move_delta)
            if new_state and tuple(map(tuple, new_state)) not in visited:
                new_path = path + [move_name]
                new_cost = len(new_path) + heuristic(new_state)
                heapq.heappush(priority_queue, (new_cost, new_state, new_path))
                visited.add(tuple(map(tuple, new_state)))

    return None

# Function to solve the puzzle and print the steps
def solve_puzzle(start_state):
    solution = a_star(start_state)
    if solution:
        print("Solution found! Moves to solve the puzzle:")
        for move in solution:
            print(move)
        print(f"Total moves: {len(solution)}")
    else:
        print("No solution found.")

# Define the start state (example)
start_state = [
    [1, 2, 3],
    [4, 0, 6],
    [7, 5, 8]
]

if __name__ == "__main__":
    solve_puzzle(start_state)
