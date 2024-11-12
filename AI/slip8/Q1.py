def count_upper_lower(string):
    upper_count = 0
    lower_count = 0

    for char in string:
        if char.isupper():
            upper_count += 1
        elif char.islower():
            lower_count += 1

    print("Number of uppercase alphabets:", upper_count)
    print("Number of lowercase alphabets:", lower_count)

if __name__ == "__main__":
    user_input = input("Enter a string: ")
    count_upper_lower(user_input)

