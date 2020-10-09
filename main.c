#include <stdio.h>

#include "bitmap.h"

int main(int argc, char **argv)
{
    BITMAPINFOHEADER  bitmapInfoHeader;
    unsigned char *bitmapData;

    bitmapData = LoadBitmapFile("test.bmp", &bitmapInfoHeader);

    printf("%s", bitmapData);
}