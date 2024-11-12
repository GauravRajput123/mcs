# Graph represented as an adjacency list
graph = {
    1: [2, 3],
    2: [4],
    3: [5],
    4: [5, 6],
    5: [7],
    6: [7],
    7: []
}

# Function to perform DFS
def depth_first_search(graph, start, goal):
    visited = set()  # Set to keep track of visited nodes
    stack = [start]  # Stack to manage the DFS traversal

    while stack:
        # Pop a node from the stack
        node = stack.pop()
        
        # Check if the goal node is reached
        if node == goal:
            print(f"Goal node {goal} found!")
            return True
        
        # If the node hasn't been visited, mark it as visited
        if node not in visited:
            print(f"Visiting node {node}")
            visited.add(node)
            
            # Push neighbors to stack in reverse order to maintain left-to-right traversal
            for neighbor in reversed(graph[node]):
                if neighbor not in visited:
                    stack.append(neighbor)

    # Goal node was not found
    print("Goal node not found.")
    return False

# Run DFS on the graph starting from node 1 and looking for node 7
initial_node = 1
goal_node = 7
depth_first_search(graph, initial_node, goal_node)
