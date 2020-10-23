#include "../hdr/processing.h"

void toGrayscale(IMAGE image, int intensity[image.rows][image.columns])
{
    int r, g, b;

    int rows = image.rows;
    int columns = image.columns;

    for (int i = 0;i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            r = (image.pixels + i * rows + j)-> r;
            g = (image.pixels + i * rows + j)-> g;
            b = (image.pixels + i * rows + j)-> b;

            Uint8 average = 0.3*r + 0.59*g + 0.11*b;

            intensity[i][j] = average;
        }
    }
}

void toBlackAndWhite(IMAGE image, int intensity[image.rows][image.columns])
{
    int rows = image.rows;
    int columns = image.columns;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int value = intensity[i][j];

            if (value >= 127)
                intensity[i][j] = 1;
            else
                intensity[i][j] = 0;
        }
    }
}

void toMatrix(char *text, int rows, int columns, int *matrix)
{
    int index = 0;

    int val;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            val = *(matrix + i * rows + j);
            index += sprintf(&text[index], "%2d ", val);
        }
        index += sprintf(&text[index], "\n");
    }
}