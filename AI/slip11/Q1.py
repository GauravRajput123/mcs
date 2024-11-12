def means_end_analysis(start, goal):
    steps = []  
    current = start  

   
    while current != goal:
        if len(current) < len(goal):
            
            next_step = current + goal[len(current)]
            steps.append(f"Add '{goal[len(current)]}' to get '{next_step}'")
        elif len(current) > len(goal):
           
            next_step = current[:-1]
            steps.append(f"Remove '{current[-1]}' to get '{next_step}'")
        else:
            
            for i in range(len(current)):
                if current[i] != goal[i]:
                    next_step = current[:i] + goal[i] + current[i + 1:]
                    steps.append(f"Change '{current[i]}' to '{goal[i]}' at position {i} to get '{next_step}'")
                    break

        
        current = next_step

    
    print("Transformation steps:")
    for step in steps:
        print(step)

start_string = "cat"
goal_string = "dog"
means_end_analysis(start_string, goal_string)
