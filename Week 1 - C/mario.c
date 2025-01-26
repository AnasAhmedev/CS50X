#include <cs50.h>
#include <stdio.h>

void make_row(int brick);

int main(void)
{
    int h;
    do
    {
        h = get_int("What's the hight you want? ");
    }
    while (h < 1 || h > 8);

    make_row(h);
}
void make_row(int height)
{
    int p = height;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < p - 1; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
        p--;
    }
}
