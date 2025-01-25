from cs50 import get_string


def countLetters(text):
    l = 0
    for char in text:
        if char.isalpha():
            l += 1
    return l


def countWords(text):
    w = 0
    for char in text:
        if char.isspace():
            w += 1
    return w+1


def countSentences(text):
    s = 0
    for char in text:
        if char in ['!', '.', '?']:
            s += 1
    return s


text = get_string("Text: ")

letters = countLetters(text)
words = countWords(text)
sentences = countSentences(text)

l = letters / words*100
s = sentences / words*100

index = round(0.0588 * l - 0.296 * s - 15.8)

if (index < 1):
    print("Before Grade 1")
elif (index > 16):
    print("Grade 16+")
else:
    print(f"Grade {index}")
