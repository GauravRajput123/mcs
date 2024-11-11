from itertools import permutations

def is_valid_assignment(assignment):
    g, o, t, u = assignment['G'], assignment['O'], assignment['T'], assignment['U']
    return g != 0 and t != 0 and (g * 10 + o + t * 10 + o == u * 100 + t * 10 + o)

def solve_cryptarithmetic():
    letters = ['G', 'O', 'T', 'U']
    digits = range(10)
    valid_assignments = []

    for perm in permutations(digits, len(letters)):
        assignment = dict(zip(letters, perm))
        if is_valid_assignment(assignment):
            valid_assignments.append(assignment)

    return valid_assignments

def print_solutions(solutions):
    for solution in solutions:
        print("  {}{} + {}{} = {}{}".format(
            solution['G'], solution['O'],
            solution['T'], solution['O'],
            solution['O'], solution['U']
        ))

if __name__ == "__main__":
    print("Solving Cryptarithmetic Problem: GO + TO = OUT")
    
    solutions = solve_cryptarithmetic()

    if solutions:
        print("Valid solutions found:")
        print_solutions(solutions)
    else:
        print("No solution found.")