#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printCiphertext(string key, string plaintext);
int checkDuplicate(string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    string key = argv[1];

    if (strlen(key) < 26)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
    }

    for (int i = 0, len = strlen(key); i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (toupper(key[j]) == toupper(key[i]))
            {
                printf("Usage: %s key\n", argv[0]);
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext: ");

    printCiphertext(key, plaintext);
}
void printCiphertext(string key, string plaintext)
{
    printf("ciphertext: ");

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        if (isupper(plaintext[i]))
        {
            printf("%c", toupper(key[plaintext[i] - 65]));
        }
        else if (islower(plaintext[i]))
        {
            printf("%c", tolower(key[plaintext[i] - 97]));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}
