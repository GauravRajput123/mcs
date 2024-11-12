import random

# Define responses for the chatbot
responses = {
    "hello": ["Hello!", "Hi there!", "Greetings!", "Hello! How can I help you?"],
    "how are you": ["I'm just a program, so I'm always good!", "I'm doing well, thank you!", "I'm here to assist you!"],
    "what is your name": ["I'm a chatbot created to assist you.", "You can call me ChatBot!", "I'm your virtual assistant."],
    "bye": ["Goodbye!", "See you later!", "Bye! Have a great day!"],
    "default": ["I'm sorry, I didn't understand that.", "Can you rephrase?", "I'm here to help! Could you please clarify?"]
}

# Function to get a response based on the user's message
def get_response(user_input):
    # Convert user input to lowercase for easier matching
    user_input = user_input.lower()

    # Check if any keyword in the user input matches our predefined responses
    for key in responses.keys():
        if key in user_input:
            return random.choice(responses[key])
    
    # If no keyword is found, return a default response
    return random.choice(responses["default"])

# Main chat function
def chat():
    print("ChatBot: Hi! I'm here to chat with you. Type 'bye' to end the conversation.")
    
    while True:
        # Get user input
        user_input = input("You: ")
        
        # Check if the user wants to end the conversation
        if user_input.lower() == "bye":
            print("ChatBot:", get_response("bye"))
            break
        
        # Get the chatbot's response
        response = get_response(user_input)
        print("ChatBot:", response)

# Start the chat
chat()
