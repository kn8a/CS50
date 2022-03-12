#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop height
    for (int h = 0; h < height; h++)
    {
        //loop width
        for (int w = 0; w < width; w++)
        {
            float avg = (image[h][w].rgbtBlue + image[h][w].rgbtRed + image[h][w].rgbtGreen) / 3.0;

            //Average of 3 pixels and give all RBG same value
            image[h][w].rgbtBlue = round(avg);
            image[h][w].rgbtRed = round(avg);
            image[h][w].rgbtGreen = round(avg);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //loop height
    for (int h = 0; h < height; h++)
    {
        //loop width
        for (int w = 0; w < width; w++)
        {
            //create RBG variables
            float r = .393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue;
            float b = .272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue;
            float g = .349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue;
            if (b > 255)
            {
                b = 255;
            }
            if (r > 255)
            {
                r = 255;
            }
            if (g > 255)
            {
                g = 255;
            }

            //apply variables
            image[h][w].rgbtRed = round(r);
            image[h][w].rgbtBlue = round(b);
            image[h][w].rgbtGreen = round(g);
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //loop height
    for (int h = 0; h < height; h++)
    {
        //Temp arrays
        int tempr[width - 1];
        int tempb[width - 1];
        int tempg[width - 1];

        //loop width
        for (int w = 0; w < width; w++)
        {
            //capture to temporary arrays
            tempr[w] = image[h][w].rgbtRed;
            tempb[w] = image[h][w].rgbtBlue;
            tempg[w] = image[h][w].rgbtGreen;
        }

        //populate arrays in reverse
        int i = 0;
        for (int rev = width - 1; rev >= 0; rev--)
        {
            image[h][rev].rgbtRed = tempr[i];
            image[h][rev].rgbtBlue = tempb[i];
            image[h][rev].rgbtGreen = tempg[i];
            i++;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    float r = 0;
    float b = 0;
    float g = 0;

    //loop height
    for (int h = 0; h < height; h++)
    {
        //loop width
        for (int w = 0; w < width; w++)
        {
            //edges
            //top edge
            if (h == 0 && w > 0 && w < width - 1)
            {
                r = (image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h][w + 1].rgbtRed + 
                     image[h + 1][w - 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed) / 6.0;
                b = (image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + 
                     image[h + 1][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue) / 6.0;
                g = (image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + 
                     image[h + 1][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen) / 6.0;
                temp[h][w].rgbtRed = round(r);
                temp[h][w].rgbtBlue = round(b);
                temp[h][w].rgbtGreen = round(g);
            }
            //bottom edge
            else if (h == height - 1 && w > 0 && w < width - 1)
            {
                r = (image[height - 2][w - 1].rgbtRed + image[height - 2][w].rgbtRed + image[height - 2][w + 1].rgbtRed +
                     image[height - 1][w - 1].rgbtRed + image[height - 1][w].rgbtRed + image[height - 1][w + 1].rgbtRed) / 6.0;
                b = (image[height - 2][w - 1].rgbtBlue + image[height - 2][w].rgbtBlue + image[height - 2][w + 1].rgbtBlue +
                     image[height - 1][w - 1].rgbtBlue + image[height - 1][w].rgbtBlue + image[height - 1][w + 1].rgbtBlue) / 6.0;
                g = (image[height - 2][w - 1].rgbtGreen + image[height - 2][w].rgbtGreen + image[height - 2][w + 1].rgbtGreen +
                     image[height - 1][w - 1].rgbtGreen + image[height - 1][w].rgbtGreen + image[height - 1][w + 1].rgbtGreen) / 6.0;
                temp[h][w].rgbtRed = round(r);
                temp[h][w].rgbtBlue = round(b);
                temp[h][w].rgbtGreen = round(g);
            }
            //left edge
            else if (w == 0 && h > 0 && h < height - 1)
            {
                r = (image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed + image[h][w].rgbtRed + 
                     image[h][w + 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed) / 6.0;
                b = (image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue + image[h][w].rgbtBlue + 
                     image[h][w + 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue) / 6.0;
                g = (image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen + image[h][w].rgbtGreen + 
                     image[h][w + 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen) / 6.0;
                temp[h][w].rgbtRed = round(r);
                temp[h][w].rgbtBlue = round(b);
                temp[h][w].rgbtGreen = round(g);
            }
            //right edge
            else if (w == width - 1 && h > 0 && h < height - 1)
            {
                r = (image[h - 1][width - 2].rgbtRed + image[h - 1][width - 1].rgbtRed + image[h][width - 2].rgbtRed +
                     image[h][width - 1].rgbtRed + image[h + 1][width - 2].rgbtRed + image[h + 1][width - 1].rgbtRed) / 6.0;
                b = (image[h - 1][width - 2].rgbtBlue + image[h - 1][width - 1].rgbtBlue + image[h][width - 2].rgbtBlue +
                     image[h][width - 1].rgbtBlue + image[h + 1][width - 2].rgbtBlue + image[h + 1][width - 1].rgbtBlue) / 6.0;
                g = (image[h - 1][width - 2].rgbtGreen + image[h - 1][width - 1].rgbtGreen + image[h][width - 2].rgbtGreen +
                     image[h][width - 1].rgbtGreen + image[h + 1][width - 2].rgbtGreen + image[h + 1][width - 1].rgbtGreen) / 6.0;
                temp[h][w].rgbtRed = round(r);
                temp[h][w].rgbtBlue = round(b);
                temp[h][w].rgbtGreen = round(g);
            }

            //corners
            //corner top left
            else if (h == 0 && w == 0)
            {
                r = (image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed) / 4.0;
                b = (image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue) / 4.0;
                g = (image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen) / 4.0;
                temp[h][w].rgbtRed = round(r);
                temp[h][w].rgbtBlue = round(b);
                temp[h][w].rgbtGreen = round(g);
            }
            //corner top right
            else if (h == 0 && w == width - 1)
            {
                r = (image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h + 1][w].rgbtRed) / 4.0;
                b = (image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue) / 4.0;
                g = (image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h + 1][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen) / 4.0;
                temp[h][w].rgbtRed = round(r);
                temp[h][w].rgbtBlue = round(b);
                temp[h][w].rgbtGreen = round(g);
            }
            //corner bottom left
            else if (h == height - 1 && w == 0)
            {
                r = (image[height - 2][w].rgbtRed + image[height - 2][w + 1].rgbtRed + 
                     image[height - 1][w].rgbtRed + image[height - 1][w + 1].rgbtRed) / 4.0;
                b = (image[height - 2][w].rgbtBlue + image[height - 2][w + 1].rgbtBlue + 
                     image[height - 1][w].rgbtBlue + image[height - 1][w + 1].rgbtBlue) / 4.0;
                g = (image[height - 2][w].rgbtGreen + image[height - 2][w + 1].rgbtGreen + 
                     image[height - 1][w].rgbtGreen + image[height - 1][w + 1].rgbtGreen) / 4.0;
                temp[h][w].rgbtRed = round(r);
                temp[h][w].rgbtBlue = round(b);
                temp[h][w].rgbtGreen = round(g);
            }
            //cornet bottom right
            else if (h == height - 1 && w == width - 1)
            {
                r = (image[height - 2][width - 2].rgbtRed + image[height - 2][width - 1].rgbtRed + 
                     image[height - 1][width - 2].rgbtRed + image[height - 1][width - 1].rgbtRed) / 4.0;
                b = (image[height - 2][width - 2].rgbtBlue + image[height - 2][width - 1].rgbtBlue + 
                     image[height - 1][width - 2].rgbtBlue + image[height - 1][width - 1].rgbtBlue) / 4.0;
                g = (image[height - 2][width - 2].rgbtGreen + image[height - 2][width - 1].rgbtGreen + 
                     image[height - 1][width - 2].rgbtGreen + image[height - 1][width - 1].rgbtGreen) / 4.0;
                temp[h][w].rgbtRed = round(r);
                temp[h][w].rgbtBlue = round(b);
                temp[h][w].rgbtGreen = round(g);
            }

            //middle pixels
            else if (h >= 1 && w >= 1 && h < height - 1 && w < width - 1)
            {
                r = (image[h - 1][w - 1].rgbtRed + image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed +
                     image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h][w + 1].rgbtRed +
                     image[h + 1][w - 1].rgbtRed + image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed) / 9.0;
                b = (image[h - 1][w - 1].rgbtBlue + image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue +
                     image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue +
                     image[h + 1][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue) / 9.0;
                g = (image[h - 1][w - 1].rgbtGreen + image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen +
                     image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen +
                     image[h + 1][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen) / 9.0;
                temp[h][w].rgbtRed = round(r);
                temp[h][w].rgbtBlue = round(b);
                temp[h][w].rgbtGreen = round(g);
            }
        }
    }
    //apply to image
    //loop height
    for (int h = 0; h < height; h++)
    {
        //loop width
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen;
        }
    }
    return;
}