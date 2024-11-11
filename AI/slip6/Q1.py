import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize

nltk.download('stopwords')
nltk.download('punkt')

def remove_stop_words(text):
    stop_words = set(stopwords.words('english'))
    words = word_tokenize(text)
    filtered_words = [word for word in words if word.lower() not in stop_words]
    return ' '.join(filtered_words)

def read_text_from_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        return file.read()

if __name__ == "__main__":
    file_path = input("Enter the path to the text file: ")

    try:
        passage = read_text_from_file(file_path)
        cleaned_passage = remove_stop_words(passage)

        print("\nOriginal Passage:")
        print(passage)

        print("\nPassage after Removing Stop Words:")
        print(cleaned_passage)
    except FileNotFoundError:
        print("File not found. Please check the file path.")