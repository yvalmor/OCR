#include "../hdr/processing.h"

void toGrayscale(IMAGE image, int *intensity)
{
    int r, g, b;

    int rows = image.rows;
    int columns = image.columns;

    for (int i = 0;i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            r = (image.pixels + i * columns + j)-> r;
            g = (image.pixels + i * columns + j)-> g;
            b = (image.pixels + i * columns + j)-> b;

            Uint8 average = 0.3*r + 0.59*g + 0.11*b;

            *(intensity + i * columns + j) = average;
        }
    }
}

void toBlackAndWhite(IMAGE image, int *intensity)
{
    int rows = image.rows;
    int columns = image.columns;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int value = *(intensity + i * columns + j);

            if (value < 127)
                *(intensity + i * columns + j) = 0;
            else
                *(intensity + i * columns + j) = 1;
        }
    }
}

void to_matrix_bw(char *text, int rows, int columns, int *matrix)
{
    int index = 0;

    int val;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            val = *(matrix + i * columns + j);
            index += sprintf(&text[index], "%2d ", val);
        }
        index += sprintf(&text[index], "\n");
    }
}
