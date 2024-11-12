def bfs(graph, start, goal):
    visited = set()
    queue = [(start, [start])]

    while queue:
        current_node, path = queue.pop(0)

        if current_node == goal:
            return path

        if current_node not in visited:
            visited.add(current_node)

            for neighbor in graph[current_node]:
                if neighbor not in visited:
                    queue.append((neighbor, path + [neighbor]))

    return None

# Example graph represented as an adjacency list
graph = {
    1: [2, 3],
    2: [4, 5],
    3: [6, 7],
    4: [8],
    5: [8],
    6: [8],
    7: [8],
    8: []
}

# Specify the initial and goal nodes
initial_node = 1
goal_node = 8

# Run BFS and print the result
result = bfs(graph, initial_node, goal_node)

if result:
    print(f"BFS path from {initial_node} to {goal_node}: {result}")
else:
    print(f"No path found from {initial_node} to {goal_node}")
