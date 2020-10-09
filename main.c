#include <stdio.h>
#include <stdlib.h>

int main()
{
    int width = 20;
    int height = 20;

    int pixels[width][height];

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            pixels[i][j] = 0;
        }
    }

    for (int i = 0, int j = 0; i < width && j < height; ++i, ++j) {
        pixels[i][j] = 1;
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            printf("%d ", pixels[i][j]);
        }
        printf("\n");
    }
}