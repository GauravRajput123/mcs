from itertools import permutations

def is_valid_assignment(assignment):
    cross = assignment['C']*10000 + assignment['R']*1000 + assignment['O']*100 + assignment['S']*10 + assignment['S']
    roads = assignment['R']*10000 + assignment['O']*1000 + assignment['A']*100 + assignment['D']*10 + assignment['S']
    danger = assignment['D']*100000 + assignment['A']*10000 + assignment['N']*1000 + assignment['G']*100 + assignment['E']*10 + assignment['R']

    return cross + roads == danger

def solve_cryptarithmetic():
    letters = ['C', 'R', 'O', 'S', 'A', 'D', 'N', 'G', 'E']
    digits = range(10)
    valid_assignments = []

    for perm in permutations(digits, len(letters)):
        assignment = dict(zip(letters, perm))
        if is_valid_assignment(assignment):
            valid_assignments.append(assignment)

    return valid_assignments

def print_solutions(solutions):
    for solution in solutions:
        print("  {}{}{}{}{} + {}{}{}{}{} = {}{}{}{}{}{}".format(
            solution['C'], solution['R'], solution['O'], solution['S'], solution['S'],
            solution['R'], solution['O'], solution['A'], solution['D'], solution['S'],
            solution['D'], solution['A'], solution['N'], solution['G'], solution['E'], solution['R']
        ))

if __name__ == "__main__":
    print("Solving Cryptarithmetic Problem: CROSS + ROADS = DANGER")
    
    solutions = solve_cryptarithmetic()

    if solutions:
        print("Valid solutions found:")
        print_solutions(solutions)
    else:
        print("No solution found.")