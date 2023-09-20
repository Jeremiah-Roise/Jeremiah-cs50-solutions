#include <stdio.h>
#include "helpers.h"
#include <math.h>
#include <string.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (size_t column = 0; column < width; column++)
    {
        for (size_t row = 0; row < height; row++)
        {
            RGBTRIPLE *pixel = &image[row][column];
            float grey = (pixel->rgbtBlue + pixel->rgbtGreen + pixel->rgbtRed) / 3.0;
            grey = round(grey);
            pixel->rgbtBlue = grey;
            pixel->rgbtRed = grey;
            pixel->rgbtGreen = grey;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (size_t column = 0; column < width; column++)
    {
        for (size_t row = 0; row < height; row++)
        {
            RGBTRIPLE pixel = image[row][column];
                
            size_t R = round(.393 * pixel.rgbtRed + .769 * pixel.rgbtGreen + .189 * pixel.rgbtBlue);
            size_t G = round(.349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue);
            size_t B = round(.272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue);
            R = (R > 255) ? 255 : R;
            G = (G > 255) ? 255 : G;
            B = (B > 255) ? 255 : B;
            image[row][column].rgbtRed = R;
            image[row][column].rgbtGreen = G;
            image[row][column].rgbtBlue = B;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    size_t offset = 0;
    if (width % 2 == 0)
    {
        // then the width is an even number.
        // there is no middle column.
        offset = (width - 1) / 2;
    }
    else
    {
        // the width is not an even number.
        // there is a middle column.
        // remove one pixel which is the middle column which will not change
        offset = (width - 3) / 2;
    }
    // write for loop to loop the width*height.
    //  trade pixels one at a time with its mirrored coordinate.
    size_t rightPixelColumnIndex = width;
    for (size_t column = 0; column <= offset; column++)
    {
        rightPixelColumnIndex--;
        for (size_t row = 0; row < height; row++)
        {
            // right pixel.
            // swap
            // left pixel into tmp.
            RGBTRIPLE tmp = image[row][column];
            // left pixel set to right.
            image[row][column] = image[row][rightPixelColumnIndex];
            // right pixel set to tmp.
            image[row][rightPixelColumnIndex] = tmp;
        }
    }
    return;

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (size_t column = 0; column < width; column++)
    {
        for (size_t row = 0; row < height; row++)
        {
            unsigned long R = 0;
            unsigned long G = 0;
            unsigned long B = 0;
            float divisor = 0;

            for (size_t i = 0; i < 3; i++)
            {
                for (size_t j = 0; j < 3; j++)
                {
                    size_t x = column + i - 1;
                    size_t y = row + j - 1;
                    if (y >= 0 && y < height)
                    {
                        if (x >= 0 && x < width)
                        {
                            divisor++;
                            R += image[y][x].rgbtRed;
                            G += image[y][x].rgbtGreen;
                            B += image[y][x].rgbtBlue;
                        }
                    }                
                }
            }

            R = round(R / divisor);
            G = round(G / divisor);
            B = round(B / divisor);
            R = (R > 255) ? 255 : R;
            G = (G > 255) ? 255 : G;
            B = (B > 255) ? 255 : B;
            tmp[row][column].rgbtRed = R;
            tmp[row][column].rgbtGreen = G;
            tmp[row][column].rgbtBlue = B;
        }
    }
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}
