#include <stdio.h>

#include "../hdr/bitmap.h"

int main(__attribute((unused)) int argc, __attribute((unused))char **argv)
{
    IMAGE *im = create_Image("truc.bmp");
    PIXEL *pixels = im -> pixels;

    int rows = im -> rows;
    int columns = im -> columns;

    for (int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < columns; ++j)
        {
            unsigned char r = ((pixels + i * columns) + j) -> r;
            printf("%d", r);
        }
        printf("\n");
    }

    return 0;
}
