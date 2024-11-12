import heapq

def a_star_search(graph, start, goal):
    """
    Implements the A* search algorithm.

    Args:
        graph: A dictionary representing the graph, where keys are nodes and values are dictionaries of neighbors and their edge weights.
        start: The starting node.
        goal: The goal node.

    Returns:
        A tuple containing the shortest path and its total cost, or None if no path is found.
    """

    open_set = [(0, start)]  # Priority queue of (f_score, node)
    closed_set = set()
    came_from = {}
    g_score = {node: float('infinity') for node in graph}
    g_score[start] = 0
    f_score = {node: float('infinity') for node in graph}
    f_score[start] = heuristic_cost_estimate(start, goal)

    while open_set:
        current = heapq.heappop(open_set)[1]
        if current == goal:
            return reconstruct_path(came_from, current), g_score[current]

        closed_set.add(current)

        for neighbor, cost in graph[current].items():
            tentative_g_score = g_score[current] + cost
            if neighbor in closed_set and tentative_g_score >= g_score[neighbor]:
                continue
            if neighbor not in [item[1] for item in open_set] or tentative_g_score < g_score[neighbor]:
                came_from[neighbor] = current
                g_score[neighbor] = tentative_g_score
                f_score[neighbor] = g_score[neighbor] + heuristic_cost_estimate(neighbor, goal)
                heapq.heappush(open_set, (f_score[neighbor], neighbor))

    return None, float('infinity')

def reconstruct_path(came_from, current):
    """
    Reconstructs the path from the start node to the goal node.

    Args:
        came_from: A dictionary mapping nodes to their predecessors.
        current: The goal node.

    Returns:
        The path from the start node to the goal node.
    """

    path = [current]
    while current in came_from:
        current = came_from[current]
        path.append(current)
    path.reverse()
    return path

def heuristic_cost_estimate(a, b):
    """
    Heuristic function to estimate the cost from node a to node b.

    In this example, we'll use the Manhattan distance as a simple heuristic.
    You can replace this with a more informed heuristic for better performance.

    Args:
        a: The starting node.
        b: The goal node.

    Returns:
        The estimated cost from a to b.
    """

    # Replace this with a more suitable heuristic for your specific problem
    # For now, we'll use a simple estimate:
    return abs(ord(a) - ord(b))

# Example usage with the provided graph
graph = {
    'A': {'B': 9, 'C': 4, 'D': 7},
    'B': {'A': 9, 'C': 14, 'E': 11},
    'C': {'A': 4, 'B': 14, 'D': 18, 'E': 17, 'F': 12},
    'D': {'A': 7, 'C': 18, 'F': 14},
    'E': {'B': 11, 'C': 17, 'F': 9, 'G': 5},
    'F': {'C': 12, 'D': 14, 'E': 9, 'G': 8},
    'G': {'E': 5, 'F': 8}
}

start = 'A'
goal = 'G'

path, cost = a_star_search(graph, start, goal)

if path:
    print("Shortest path:", path)
    print("Total cost:", cost)
else:
    print("No path found.")