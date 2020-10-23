#include "../hdr/processing.h"

void toGrayscale(IMAGE image, int *intensity)
{
    int r, g, b;

    int rows = image.rows;
    int columns = image.columns;

    for (int i = 0;i<rows;i++)
    {
        for (int j = 0;j<columns;j++)
        {
            r = (image.pixels + i * rows + j)-> r;
            g = (image.pixels + i * rows + j)-> g;
            b = (image.pixels + i * rows + j)-> b;
            Uint8 average = 0.3*r + 0.59*g + 0.11*b;
            (intensity + i * rows + j) = average;
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
            int value = *(intensity + i * rows + j);
            printf("%d", value);

            if (value >= 127)
                (intensity + i * rows + j) = 255;
            else
                (intensity + i * rows + j) = 0;
        }
    }
}