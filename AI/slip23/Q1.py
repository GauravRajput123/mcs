def tower_of_hanoi(n, source, target, auxiliary):
    if n > 0:
        # Move n-1 disks from source to auxiliary peg using target peg
        tower_of_hanoi(n - 1, source, auxiliary, target)

        # Move the nth disk from source to target peg
        print(f"Move disk {n} from {source} to {target}")

        # Move the n-1 disks from auxiliary peg to target peg using source peg
        tower_of_hanoi(n - 1, auxiliary, target, source)

if __name__ == "__main__":
    num_disks = int(input("Enter the number of disks: "))

    tower_of_hanoi(num_disks, 'A', 'C', 'B')