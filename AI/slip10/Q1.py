import itertools

def solve_cryptarithmetic():
    # We need to map T, W, O, F, U, R to digits (0-9) with the constraint TWO + TWO = FOUR
    letters = 'TWOFUR'
    
    # Generate all possible unique digit assignments
    for perm in itertools.permutations(range(10), len(letters)):
        # Assign digits to each letter
        T, W, O, F, U, R = perm
        
        # Calculate TWO and FOUR as numbers
        TWO = T * 100 + W * 10 + O
        FOUR = F * 1000 + O * 100 + U * 10 + R
        
        # Check if TWO + TWO equals FOUR
        if TWO + TWO == FOUR:
            return {'T': T, 'W': W, 'O': O, 'F': F, 'U': U, 'R': R, 'TWO': TWO, 'FOUR': FOUR}

solution = solve_cryptarithmetic()
if solution:
    print("Solution found!")
    print(f"TWO: {solution['TWO']}")
    print(f"FOUR: {solution['FOUR']}")
    print("Digit assignments:")
    for letter, digit in solution.items():
        if letter not in ['TWO', 'FOUR']:
            print(f"{letter} = {digit}")
else:
    print("No solution found.")
