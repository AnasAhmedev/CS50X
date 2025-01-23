#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./recover FILE\n");
        return 1;
    }

    FILE *inptr = fopen(argv[1], "r");

    if (inptr == NULL)
    {
        printf("File not found.\n");
        return 1;
    }

    unsigned char buffer[BLOCK_SIZE];

    int jpg = 0;

    FILE *outptr = NULL;

    char image[8];

    while (fread(buffer, 1, BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            sprintf(image, "%03i.jpg", jpg);

            outptr = fopen(image, "w");

            if (outptr == NULL)
            {
                printf("Failed\n");
                fclose(inptr);
                return 1;
            }

            jpg++;
        }

        if (outptr != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, outptr);
        }
    }

    if (outptr != NULL)
    {
        fclose(outptr);
    }

    fclose(inptr);

    return 0;
}
