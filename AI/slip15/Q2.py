def iterative_deepening_dfs(root, goal_state, max_depth):
    for depth in range(max_depth + 1):
        result = depth_limited_dfs(root, goal_state, depth)
        if result is not None:
            return result
    return None

def depth_limited_dfs(node, goal_state, depth):
    if depth == 0 and node == goal_state:
        return node
    elif depth > 0:
        for child_state in generate_children(node):
            result = depth_limited_dfs(child_state, goal_state, depth - 1)
            if result is not None:
                return result
    return None

def generate_children(state):
    # Modify this function based on your specific problem to generate children
    # For demonstration purposes, let's consider a simple problem of generating children for integers
    return [state + 1, state - 1]

def iterative_deepening_dfs_without_class(initial_state, goal_state, max_depth):
    for depth in range(max_depth + 1):
        result = depth_limited_dfs(initial_state, goal_state, depth)
        if result is not None:
            return result
    return None

if __name__ == "__main__":
    initial_state = 0
    goal_state = 5
    max_depth = 10

    result = iterative_deepening_dfs_without_class(initial_state, goal_state, max_depth)

    if result is not None:
        print("Goal state found:", result)
    else:
        print("Goal state not found within the maximum depth.")