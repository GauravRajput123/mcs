def objective_function(x):
    return -x**2 + 4*x

def hill_climbing(max_iterations=1000, step_size=0.01):
    current_x = 0.0  # Starting point
    current_value = objective_function(current_x)

    for _ in range(max_iterations):
        next_x = current_x + step_size
        next_value = objective_function(next_x)

        if next_value > current_value:
            current_x = next_x
            current_value = next_value
        else:
            break

    return current_x, current_value

if __name__ == "__main__":
    result_x, result_value = hill_climbing()

    print(f"Optimal x: {result_x}")
    print(f"Maximum value: {result_value}")