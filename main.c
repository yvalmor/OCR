#include <stdio.h>

#include "bitmap.h"

int main()
{
    BITMAPINFOHEADER bitmapInfoHeader;
    unsigned char *bitmapData;

    bitmapData = LoadBitmapFile("test.bmp", &bitmapInfoHeader);

    printf("%s", bitmapData);

    return 0;
}