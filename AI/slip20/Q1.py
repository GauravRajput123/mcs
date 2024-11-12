#pip install chatterbot chatterbot_corpus


from chatterbot import ChatBot
from chatterbot.trainers import ChatterBotCorpusTrainer

# Create a chat bot
college_bot = ChatBot("CollegeBot")

# Create a new trainer for the chat bot
trainer = ChatterBotCorpusTrainer(college_bot)

# Train the chat bot on the English language corpus data
trainer.train("chatterbot.corpus.english")

# Additional training data for college-related information
trainer.train([
    "What is your college?",
    "I am a virtual assistant and don't belong to any specific college.",
    "Tell me about your college life.",
    "I don't have a physical presence, so I don't experience college life.",
    # Add more training data related to your college
])

# Create a function to interact with the bot
def chat_with_college_bot():
    print("College Bot: Hi! I'm your College Bot. Ask me anything about college.")
    while True:
        user_input = input("You: ")
        if user_input.lower() == 'exit':
            print("College Bot: Goodbye!")
            break
        response = college_bot.get_response(user_input)
        print("College Bot:", response)

if __name__ == "__main__":
    chat_with_college_bot()
