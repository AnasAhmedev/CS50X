#include "helpers.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
    return;
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + (.769 * image[i][j].rgbtGreen) +
                             (.189 * image[i][j].rgbtBlue));

            sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) +
                               (.168 * image[i][j].rgbtBlue));

            sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) +
                              (.131 * image[i][j].rgbtBlue));

            if (sepiaRed > 255)
                sepiaRed = 255;

            else if (sepiaRed < 0)
                sepiaRed = 0;

            if (sepiaGreen > 255)
                sepiaGreen = 255;

            else if (sepiaGreen < 0)
                sepiaGreen = 0;

            if (sepiaBlue > 255)
                sepiaBlue = 255;

            else if (sepiaBlue < 0)
                sepiaBlue = 0;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int temp1 = image[i][j].rgbtRed;
            int temp2 = image[i][j].rgbtGreen;
            int temp3 = image[i][j].rgbtBlue;

            image[i][j] = image[i][width - j - 1];

            image[i][width - j - 1].rgbtRed = temp1;
            image[i][width - j - 1].rgbtGreen = temp2;
            image[i][width - j - 1].rgbtBlue = temp3;
        }
    }
    return;
}

int isValid(int i, int j, int height, int width, RGBTRIPLE image[height][width], float *avgRed,
            float *avgGreen, float *avgBlue)
{
    float numOfPixels = 0, red = 0, green = 0, blue = 0;
    for (int k = -1; k <= 1; k++)
    {
        for (int q = -1; q <= 1; q++)
        {
            int i2 = i + k;
            int j2 = j + q;

            if (i2 >= 0 && i2 < height && j2 >= 0 && j2 < width)
            {
                red += image[i2][j2].rgbtRed;
                green += image[i2][j2].rgbtGreen;
                blue += image[i2][j2].rgbtBlue;
                numOfPixels++;
            }
        }
    }
    *avgRed = red / numOfPixels;
    *avgGreen = green / numOfPixels;
    *avgBlue = blue / numOfPixels;
    return 0;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avgRed, avgGreen, avgBlue;

            isValid(i, j, height, width, image, &avgRed, &avgGreen, &avgBlue);

            copy[i][j].rgbtRed = round(avgRed);
            copy[i][j].rgbtGreen = round(avgGreen);
            copy[i][j].rgbtBlue = round(avgBlue);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}
