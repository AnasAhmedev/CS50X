from cs50 import get_float


def calculateNumberOfCoins(c):
    n = 0
    c = c*100

    while (c > 0):
        if (c >= 25):
            c -= 25
            n += 1
        elif (c >= 10 and c < 25):
            c -= 10
            n += 1
        elif (c >= 5 and c < 10):
            c -= 5
            n += 1
        elif (c >= 1 and c < 5):
            c -= 1
            n += 1
    return n


while True:
    c = get_float("Change owned? ")
    if (c > 0):
        break

n = calculateNumberOfCoins(c)
print(n)
