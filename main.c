#include <stdio.h>
#include <stdlib.h>

int round4(int x);
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

// Function to round an int to a multiple of 4
int round4(int x) {
    return x % 4 == 0 ? x : x - x % 4 + 4;
}

void write_bmp(char *filename, char rgb[], int length, int width) {
    int height = (length / 3) / width;

    // Pad the width of the destination to a multiple of 4
    int padded_width = round4(width * 3);

    int bitmap_size = height * padded_width * 3;
    char *bitmap = (char *) malloc(bitmap_size * sizeof(char));
    for (int i = 0; i < bitmap_size; i++) bitmap[i] = 0;

    // For each pixel in the RGB image...
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {

            // For R, G, and B...
            for (int color = 0; color < 3; color++) {

                // Get the index of the destination image
                int index = row * padded_width + col * 3 + color;

                // Set the destination to the value of the src at row, col.
                bitmap[index] = rgb[3*(row * width + col) + (2 - color)];
            }
        }
    }

    char tag[] = { 'B', 'M' };
    int header[] = {
            0, 0, 0x36, 0x28, width, height, 0x180001,
            0, 0, 0x002e23, 0x002e23, 0, 0
    };
    header[0] = sizeof(tag) + sizeof(header) + bitmap_size;
    FILE *fp = fopen(filename, "w+");
    fwrite(&tag, sizeof(tag), 1, fp);
    fwrite(&header, sizeof(header), 1, fp);
    fwrite(bitmap, bitmap_size * sizeof(char), 1, fp);
    fclose(fp);
    free(bitmap);
}