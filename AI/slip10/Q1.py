from itertools import permutations

def is_valid_assignment(assignment):
    t, w, o, f, u, r = assignment
    return 2 * (100 * t + 10 * w + o) == 1000 * f + 100 * o + 10 * u + r

def solve_cryptarithmetic():
    for perm in permutations(range(10), 6):
        assignment = {'T': perm[0], 'W': perm[1], 'O': perm[2], 'F': perm[3], 'U': perm[4], 'R': perm[5]}
        if assignment['T'] == 0 or assignment['F'] == 0:
            continue

        if is_valid_assignment(assignment):
            print("Solution found:")
            print(f"  T W O\n+ T W O\n-------\n  F O U R")
            print(f"  {assignment['T']} {assignment['W']} {assignment['O']}")
            print(f"+ {assignment['T']} {assignment['W']} {assignment['O']}")
            print("-------")
            print(f"  {assignment['F']} {assignment['O']} {assignment['U']} {assignment['R']}")
            return

    print("No solution found.")

if __name__ == "__main__":
    solve_cryptarithmetic()