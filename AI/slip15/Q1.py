import random

class MonkeyBananaProblem:
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.monkey_position = (rows - 1, 0)
        self.banana_position = (0, cols - 1)
        self.bananas_collected = 0

    def move(self, direction):
        if direction == 'up' and self.monkey_position[0] > 0:
            self.monkey_position = (self.monkey_position[0] - 1, self.monkey_position[1])
        elif direction == 'down' and self.monkey_position[0] < self.rows - 1:
            self.monkey_position = (self.monkey_position[0] + 1, self.monkey_position[1])
        elif direction == 'left' and self.monkey_position[1] > 0:
            self.monkey_position = (self.monkey_position[0], self.monkey_position[1] - 1)
        elif direction == 'right' and self.monkey_position[1] < self.cols - 1:
            self.monkey_position = (self.monkey_position[0], self.monkey_position[1] + 1)

        if self.monkey_position == self.banana_position:
            self.bananas_collected += 1
            self.place_banana()

    def place_banana(self):
        self.banana_position = (random.randint(0, self.rows - 1), random.randint(0, self.cols - 1))

    def print_state(self):
        for i in range(self.rows):
            for j in range(self.cols):
                if (i, j) == self.monkey_position:
                    print('M', end=' ')
                elif (i, j) == self.banana_position:
                    print('B', end=' ')
                else:
                    print('.', end=' ')
            print()

if __name__ == "__main__":
    rows = int(input("Enter the number of rows in the room: "))
    cols = int(input("Enter the number of columns in the room: "))

    monkey_banana_problem = MonkeyBananaProblem(rows, cols)

    while True:
        monkey_banana_problem.print_state()
        print(f"Bananas collected: {monkey_banana_problem.bananas_collected}")

        if monkey_banana_problem.monkey_position == monkey_banana_problem.banana_position:
            print("Congratulations! Monkey reached the banana.")
            break

        direction = input("Enter the direction to move (up/down/left/right): ")
        monkey_banana_problem.move(direction.lower())