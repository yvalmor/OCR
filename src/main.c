#include <stdio.h>
#include <stdlib.h>

#include "../hdr/segmentation.h"

int main()
{
    const int rows = 20;
    const int columns = 20;

    int placeholder[20][20] = {
            {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    int pixels[rows][columns];
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            pixels[i][j] = placeholder[i][j];

    LINES *lines = Get_lines(rows, columns, *pixels);
    CHARACTERS *characters = Get_char(rows, columns, *pixels, lines);

    CHARACTERS *current = characters;

    int upper;
    int lower;
    int left;
    int right;

    while (current != NULL)
    {
        upper = (current -> bounds).upper;
        lower = (current -> bounds).lower;
        left = (current -> bounds).left;
        right = (current -> bounds).right;

        printf("word: %d %d %d %d\n", upper, lower, left, right);

        for (int i = upper; i < lower ; ++i)
        {
            for (int j = left; j < right; ++j)
            {
                printf("%d", pixels[i][j]);
            }
            printf("\n");
        }

        printf("\n");

        current = current -> next;
    }
}