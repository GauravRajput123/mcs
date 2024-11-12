import random

def hangman():
    secret_word = random.choice(["python", "hangman", "programming", "computer", "science", "algorithm"])
    guessed_letters, attempts = set(), 6
    
    while attempts > 0 and set(secret_word) > guessed_letters:
        print("Current word:", ''.join(letter if letter in guessed_letters else '_' for letter in secret_word))
        guess = input("Guess a letter: ").lower()
        guessed_letters.add(guess)
        attempts -= guess not in secret_word

    print(f"{'Congratulations!' if set(secret_word) <= guessed_letters else 'Sorry, you ran out of attempts. The word was: ' + secret_word}")

if __name__ == "__main__":
    hangman()