from collections import deque

def water_jug_bfs():
    
    jug1_capacity, jug2_capacity = 4, 3
    target = 2
    visited = set()  
    queue = deque()  

    queue.append((0, 0))
    visited.add((0, 0))

    steps = []

    while queue:
       
        jug1, jug2 = queue.popleft()

        if jug2 == target:
            steps.append((jug1, jug2))
            print("Solution sequence of states (jug1, jug2):")
            for step in steps:
                print(step)
            return
 
        steps.append((jug1, jug2))

        possible_actions = [
            (jug1_capacity, jug2),               
            (jug1, jug2_capacity),              
            (0, jug2),                          
            (jug1, 0),                           
            (jug1 - min(jug1, jug2_capacity - jug2), jug2 + min(jug1, jug2_capacity - jug2)),  # Pour Jug1 -> Jug2
            (jug1 + min(jug2, jug1_capacity - jug1), jug2 - min(jug2, jug1_capacity - jug1)),  # Pour Jug2 -> Jug1
        ]
 
        for new_jug1, new_jug2 in possible_actions:
            if (new_jug1, new_jug2) not in visited:
                queue.append((new_jug1, new_jug2))
                visited.add((new_jug1, new_jug2))

    print("No solution found.")
water_jug_bfs()
