from cs50 import get_int

#pyramid function
def pyramid():
    num = usernum()
    i = 0
    #line loop
    for i in range(0, (num)):
        s = num - i - 1
        #space loop
        for sp in range(s, 0, -1):
            print(" ", end="")
        j = 0
        #pound sign loop
        for j in range(0, i + 1):
            print("#", end="")
        print("")

# ask user size of pyramid
def usernum():
    while True:
        num = get_int("Enter size of pyramid: ")
        if num > 0 and num < 9:
            break
    return num


pyramid()