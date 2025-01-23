#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int countLetters(string text);
int countWords(string text);
int countSentences(string text);

int main(void)
{

    string text = get_string("Text: ");
    int letters = countLetters(text);
    int words = countWords(text);
    int sentences = countSentences(text);

    printf("%i\n", letters);
    printf("%i\n", words);
    printf("%i\n", sentences);

    float l = (float) letters / (float) words * 100;
    float s = (float) sentences / (float) words * 100;

    int index = round(0.0588 * l - 0.296 * s - 15.8);
    // printf("%i\n", index);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int countLetters(string text)
{
    int l = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]) && text[i] != 32)
        {
            l++;
        }
    }
    return l;
}
int countWords(string text)
{
    int w = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isblank(text[i]))
        {
            w++;
        }
    }
    return w + 1;
}
int countSentences(string text)
{
    int s = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            s++;
        }
    }
    return s;
}
