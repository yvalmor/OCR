#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "../hdr/segmentation.h"
#include "../hdr/UI.h"

int main(int argc, char **argv)
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
            {0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
            {0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0},
            {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0},
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

    CHARACTERS *firstChar = Segment_image(rows, columns, *pixels, lines);

    CHARACTERS *current = firstChar;

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

    // GTK+ initialisation
    gtk_init(&argc, &argv);

    if (setup() == 1)
        return 1;

    // Main loop
    gtk_main();

    return EXIT_SUCCESS;
}