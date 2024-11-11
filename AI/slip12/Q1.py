import calendar

def display_calendar(year, month):
    # Display the calendar for the given month and year
    print(calendar.month(year, month))

# Input: year and month from the user
year = int(input("Enter year: "))
month = int(input("Enter month (1-12): "))

# Display the calendar
display_calendar(year, month)
