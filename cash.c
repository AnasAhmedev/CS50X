#include <cs50.h>
#include <stdio.h>

int calculateNumberOfCoins(int c);

int main(void)
{
    int c, n;

    do
    {
        c = get_int("Change owned? ");
    }
    while (c < 1);

    n = calculateNumberOfCoins(c);

    printf("%i\n", n);
}
int calculateNumberOfCoins(int c)
{
    int n = 0;
    do
    {
        if (c >= 25)
        {
            c = c - 25;
            n++;
        }
        else if (c >= 10 && c < 25)
        {
            c = c - 10;
            n++;
        }
        else if (c >= 5 && c < 10)
        {
            c = c - 5;
            n++;
        }
        else if (c >= 1 && c < 5)
        {
            c = c - 1;
            n++;
        }
    }
    while (c != 0);
    return n;
}
