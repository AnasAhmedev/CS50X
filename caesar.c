#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printCiphertext(int key, string pt);

int main(int argc, string argv[])
{
    int key;
    if (argc == 2)
    {
        for (int i = 0, len = strlen(argv[1]); i < len; i++)
        {
            if (isalpha(argv[1][i]))
            {
                printf("Usage: %s key\n", argv[0]);
                return 1;
            }
        }
        key = atoi(argv[1]);
        if (key > 0)
        {
            string pt = get_string("plaintext: ");
            printCiphertext(key, pt);
        }
        else
        {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
    }
    else
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
}
void printCiphertext(int key, string pt)
{
    printf("ciphertext: ");
    for (int i = 0, len = strlen(pt); i < len; i++)
    {
        if (isupper(pt[i]))
        {
            printf("%c", (pt[i] - 65 + key) % 26 + 65);
        }
        else if (islower(pt[i]))
        {
            printf("%c", (pt[i] - 97 + key) % 26 + 97);
        }
        else if (ispunct(pt[i]) || isblank(pt[i]))
        {
            printf("%c", pt[i]);
        }
        else
        {
            printf("%c", pt[i]);
        }
    }
    printf("\n");
}
