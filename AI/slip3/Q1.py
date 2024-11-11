import string

def remove_punctuation(input_string):
   
    cleaned_string = ''.join(char for char in input_string if char not in string.punctuation)
    return cleaned_string

input_string = input("Enter a string: ")

result = remove_punctuation(input_string)
print("String without punctuation:", result)
