from collections import deque

# Define the possible operations for the jugs
def get_next_states(state):
    # state is a tuple (x, y) where:
    # x is the amount of water in the 5-gallon jug
    # y is the amount of water in the 7-gallon jug

    x, y = state
    next_states = []

    # Fill the 5-gallon jug
    if x < 5:
        next_states.append((5, y))

    # Fill the 7-gallon jug
    if y < 7:
        next_states.append((x, 7))

    # Empty the 5-gallon jug
    if x > 0:
        next_states.append((0, y))

    # Empty the 7-gallon jug
    if y > 0:
        next_states.append((x, 0))

    # Pour water from 5-gallon jug to 7-gallon jug
    if x > 0 and y < 7:
        pour = min(x, 7 - y)
        next_states.append((x - pour, y + pour))

    # Pour water from 7-gallon jug to 5-gallon jug
    if y > 0 and x < 5:
        pour = min(y, 5 - x)
        next_states.append((x + pour, y - pour))

    return next_states

# BFS algorithm to solve the water jug problem
def bfs():
    # Initial state (0, 0) where both jugs are empty
    start_state = (0, 0)
    target = 4  # We need to get 4 gallons in the 7-gallon jug

    # Queue for BFS, stores (state, path_to_state)
    queue = deque([(start_state, [])])

    # Set to store visited states
    visited = set()
    visited.add(start_state)

    while queue:
        (x, y), path = queue.popleft()

        # If we have achieved the goal (4 gallons in the 7-gallon jug)
        if y == target:
            return path + [(x, y)]

        # Explore the next possible states
        for next_state in get_next_states((x, y)):
            if next_state not in visited:
                visited.add(next_state)
                queue.append((next_state, path + [(x, y)]))

    return None  # No solution found

# Function to print the solution path
def print_solution(path):
    if path:
        print("Steps to achieve 4 gallons in the 7-gallon jug:")
        for step in path:
            print(f"5-gallon jug: {step[0]} gallons, 7-gallon jug: {step[1]} gallons")
    else:
        print("No solution found.")

# Example usage
solution = bfs()
print_solution(solution)
