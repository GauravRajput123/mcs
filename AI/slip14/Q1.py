def sort_sentence(sentence):
    words = sentence.split()
    sorted_words = sorted(words)
    sorted_sentence = ' '.join(sorted_words)
    return sorted_sentence

if __name__ == "__main__":
    input_sentence = input("Enter a sentence: ")
    result = sort_sentence(input_sentence)
    print("Sorted sentence:", result)