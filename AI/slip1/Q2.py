import sys
def dfs(graph, start,goal,visited=None):
    if visited is None:
        visited = set()

    visited.add(start)
    print("Visited node:", start)
    if start==goal:
        sys.exit()
        
    for neighbor in graph[start]:
        
        
        if neighbor not in visited:
            dfs(graph, neighbor,goal,visited)
        

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

# Specify the initial node
start_node = 1
goal_node =8
print("Depth First Search starting from node", start_node)
dfs(graph,start_node,goal_node)