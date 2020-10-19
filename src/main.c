#include <stdio.h>

#include "../hdr/bitmap.h"

int main(__attribute((unused)) int argc, __attribute((unused))char **argv)
{
    printf("ok1");
    IMAGE *i = create_Image("truc.bmp");
    printf("ok2");
    PIXEL *pixels = i -> pixels;
    printf("ok3");

    int rows = i -> rows;
    int columns = i -> columns;

    for (int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < columns; ++j)
        {
            unsigned char r = ((pixels + i * rows) + j) -> r;
            printf("%d", r);
        }
        printf("\n");
    }

    return 0;
}
