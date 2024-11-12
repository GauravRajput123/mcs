import itertools

def solve_cryptarithmetic():
    # Define the letters involved
    letters = 'GOTU'
    
    # Generate all possible unique digit assignments
    for perm in itertools.permutations(range(10), len(letters)):
        # Assign digits to each letter
        G, O, T, U = perm
        
        # Ensure G and T are non-zero (to avoid leading zeros in GO and TO)
        if G == 0 or T == 0:
            continue
        
        # Calculate GO, TO, and OUT as numbers
        GO = G * 10 + O
        TO = T * 10 + O
        OUT = O * 100 + U * 10 + T
        
        # Check if GO + TO equals OUT
        if GO + TO == OUT:
            return {'G': G, 'O': O, 'T': T, 'U': U,  'GO': GO, 'TO': TO, 'OUT': OUT}

solution = solve_cryptarithmetic()
if solution:
    print("Solution found!")
    print(f"GO: {solution['GO']}")
    print(f"TO: {solution['TO']}")
    print(f"OUT: {solution['OUT']}")
    print("Digit assignments:")
    for letter, digit in solution.items():
        if letter not in ['GO', 'TO', 'OUT']:
            print(f"{letter} = {digit}")
else:
    print("No solution found.")
