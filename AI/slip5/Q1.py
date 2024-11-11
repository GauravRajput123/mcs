import nltk
from nltk.stem import WordNetLemmatizer
from nltk.tokenize import word_tokenize

nltk.download('punkt')
nltk.download('wordnet')

def lemmatize_text(text):
    lemmatizer = WordNetLemmatizer()
    tokens = word_tokenize(text)
    lemmatized_tokens = [lemmatizer.lemmatize(token) for token in tokens]
    lemmatized_text = ' '.join(lemmatized_tokens)
    return lemmatized_text

if __name__ == "__main__":
    input_text = input("Enter a sentence for lemmatization: ")

    lemmatized_result = lemmatize_text(input_text)

    print("\nOriginal Text:", input_text)
    print("Lemmatized Text:", lemmatized_result)