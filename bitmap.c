#include <stdlib.h>
#include <stdio.h>

#include "bitmap.h"

unsigned char *LoadBitmapFile(char *filename,
                              BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr;
    BITMAPFILEHEADER bitmapFileHeader;
    unsigned char *bitmapImage;
    int imageIdx = 0;
    unsigned char tempRGB;

    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
        return NULL;

    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

    if (bitmapFileHeader.bfType != 0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }

    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

    bitmapImage = malloc(bitmapInfoHeader -> biSizeImage);

    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    fread(bitmapImage, bitmapInfoHeader -> biSizeImage, filePtr);

    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    for (imageIdx = 0; imageIdx < bitmapInfoHeader -> biSizeImage; imageIdx += 3)
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    fclose(filePtr);
    return bitmapImage;
}