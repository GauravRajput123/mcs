graph = {
    1: [2, 3, 4],
    2: [1, 4, 5],
    3: [1],
    4: [1, 2, 5],
    5: [2, 4, 6, 7],
    6: [5, 7],
    7: [5, 6]
}

def depth_first_search(graph, start, goal):
    visited = set() 
    stack = [start]  
    while stack:
        
        node = stack.pop()
        
        if node == goal:
            print(f"Goal node {goal} found!")
            return True 
        if node not in visited:
            print(f"Visiting node {node}")
            visited.add(node)    
            for neighbor in reversed(graph[node]):
                if neighbor not in visited:
                    stack.append(neighbor)

    print("Goal node not found.")
    return False
initial_node = 2
goal_node = 7
depth_first_search(graph, initial_node, goal_node)
