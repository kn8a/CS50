from cs50 import get_float


def cash():
    y = 0
    x = -1
    # user input
    while x < 0:
        x = get_float("Change owed: $")
    x = round(x * 100)
    
    # count querters
    while x - 25 >= 0:
        y += 1
        x = x - 25
    # count dimes
    while x - 10 >= 0:
        y += 1
        x = x - 10
    # count nickles
    while x - 5 >= 0:
        y += 1
        x = x - 5
    # count pennies
    while x - 1 >= 0:
        y += 1
        x = x - 1
    
    print(y)
    

cash()