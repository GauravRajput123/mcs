import heapq
rectangular_objects = [(3, 2)] * 5  
square_objects = [(2, 2)] * 4       

room_width = 10
room_height = 10

room_area = room_width * room_height


class State:
    def __init__(self, objects_placed, unused_area, g_cost=0, h_cost=0):
        self.objects_placed = objects_placed  
        self.unused_area = unused_area        
        self.g_cost = g_cost                 
        self.h_cost = h_cost                  
        self.f_cost = g_cost + h_cost         
        
    def __lt__(self, other):
        return self.f_cost < other.f_cost  

def calculate_heuristic(objects_placed):
    used_area = sum([obj[0] * obj[1] for obj in objects_placed]) 
    unused_area = room_area - used_area 
    return unused_area


def a_star(objects):

    initial_state = State([], room_area, 0, calculate_heuristic([]))
    
    open_list = []
    heapq.heappush(open_list, initial_state)
    
    closed_set = set()
    
    while open_list:
        current_state = heapq.heappop(open_list)
        
        if len(current_state.objects_placed) == len(objects):
            return current_state.objects_placed, current_state.unused_area
        
        for obj in objects:
            new_objects_placed = current_state.objects_placed + [obj]
            new_unused_area = calculate_heuristic(new_objects_placed)
            
            g_cost = current_state.g_cost + 1  
            
            h_cost = new_unused_area
            
            new_state = State(new_objects_placed, new_unused_area, g_cost, h_cost)
            
            if tuple(new_objects_placed) not in closed_set:
                closed_set.add(tuple(new_objects_placed))
                heapq.heappush(open_list, new_state)
    
    return None  

objects = rectangular_objects + square_objects 
solution, unused_area = a_star(objects)

if solution:
    print("Optimal arrangement of objects:", solution)
    print("Unused area in the room:", unused_area)
else:
    print("No solution found.")
