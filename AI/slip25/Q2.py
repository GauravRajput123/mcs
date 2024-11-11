import heapq

goal_state = (1, 2, 3, 4, 5, 6, 7, 8, 0)

moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]  

def manhattan_distance(state):
    distance = 0
    for i in range(9):
        if state[i] != 0:
            goal_pos = goal_state.index(state[i])
            current_pos = i
    
            distance += abs(current_pos // 3 - goal_pos // 3) + abs(current_pos % 3 - goal_pos % 3)
    return distance

def a_star(initial_state):
    
    open_list = []
    heapq.heappush(open_list, (0 + manhattan_distance(initial_state), 0, initial_state, []))  
    
    visited = set()
    visited.add(initial_state)

    while open_list:
        f, g, current_state, path = heapq.heappop(open_list)
        
        if current_state == goal_state:
            return path
        
        zero_index = current_state.index(0)
        zero_row, zero_col = zero_index // 3, zero_index % 3
        
        for dr, dc in moves:
            new_row, new_col = zero_row + dr, zero_col + dc
            
            if 0 <= new_row < 3 and 0 <= new_col < 3:
                
                new_zero_index = new_row * 3 + new_col
                
                new_state = list(current_state)
                new_state[zero_index], new_state[new_zero_index] = new_state[new_zero_index], new_state[zero_index]
                new_state = tuple(new_state)
                
                if new_state not in visited:
                    visited.add(new_state)
                    new_g = g + 1  
                    f_cost = new_g + manhattan_distance(new_state)  
                    heapq.heappush(open_list, (f_cost, new_g, new_state, path + [new_state]))
    
    return None  

def print_state(state):
    for i in range(0, 9, 3):
        print(state[i:i+3])
    print()

initial_state = (1, 2, 3, 4, 5, 6, 7, 8, 0)

solution = a_star(initial_state)

if solution:
    print("Solution steps:")
    for step in solution:
        print_state(step)
else:
    print("No solution found")
