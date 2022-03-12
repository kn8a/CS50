def grade_counter(phrase):
    letters = 0
    sentences = 0
    words = 1
    grade = 0.00
    
    # counting
    count = 0
    for cur in phrase:
        
        # count letters
        if ord(cur) > 64 and ord(cur) < 91:
            letters += 1
        elif ord(cur) > 96 and ord(cur) < 123:
            letters += 1
        # count sentenses
        elif ord(cur) == 33 or ord(cur) == 46 or ord(cur) == 63:
            sentences += 1
        # count words
        elif ord(cur) == 32:
            words += 1
    
    # grade calculation
    L = float(letters * 100 / words)
    S = float(sentences * 100 / words)
    grade = round(L * 0.0588 - S * 0.296 - 15.8)
    return grade


phrase = input("enter text: ")
grade = grade_counter(phrase)

# grade output
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")