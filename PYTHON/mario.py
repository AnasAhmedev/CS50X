from cs50 import get_int


def makePyramid(height):
    for i in range(height):
        for j in range(height-i-1):
            print(" ", end="")
        for k in range(i+1):
            print("#", end="")
        print()


stop = True
while (stop):
    height = get_int("height? ")
    if (height > 0 and height < 9):
        stop = False

makePyramid(height)
