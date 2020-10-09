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

    pixels[0][0] = 1;
    pixels[1][1] = 1;
    pixels[2][2] = 1;
    pixels[3][3] = 1;
    pixels[4][4] = 1;
    pixels[5][5] = 1;


    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            printf("%d ", pixels[i][j]);
        }
        printf("\n");
    }
}