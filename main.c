#include <stdio.h>
#include <stdlib.h>

void write_bmp(char *filename, char rgb[], int length, int width);

int main()
{
    char fr[] = {
            0, 85, 164,    // Bleu
            255, 255, 255, // Blanc
            239, 65, 53,   // Rouge
            0, 85, 164,
            255, 255, 255,
            239, 65, 53,
    };
    write_bmp("french_flag.bmp", fr, sizeof(fr) / sizeof(char), 3);
}

void write_bmp(char *filename, char rgb[], int length, int width)
{

    // Calculate the image height from its width and the array length
    int height = (length / 3) / width;

    // The size of the pixel data. For now, use width + 1 to handle
    // row padding.
    int bitmap_size =  3 * height * (width + 1);

    // The pixel data is now variable-length, so we need to use
    // malloc.
    char *bitmap = (char *) malloc(bitmap_size * sizeof(char));

    // Zeroing out the data will set all the pixels to black.
    for (int i = 0; i < bitmap_size; i++) bitmap[i] = 0;

    char tag[] = { 'B', 'M' };
    int header[] = {
            0,                   // File size... update at the end.
            0, 0x36, 0x28,
            width, height,       // Image dimensions in pixels

            0x180001, 0, 0, 0x002e23, 0x002e23, 0, 0,
    };
    // Update file size: just the sum of the sizes of the arrays
    // we write to disk.
    header[0] = sizeof(tag) + sizeof(header) + bitmap_size;

    FILE *fp = fopen(filename, "w+");
    fwrite(&tag, sizeof(tag), 1, fp);
    fwrite(&header, sizeof(header), 1, fp);

    // Malloc returns a pointer, so we no longer need to get the
    // adress of bitmap
    fwrite(bitmap, bitmap_size * sizeof(char), 1, fp);
    fclose(fp);

    free(bitmap);
}