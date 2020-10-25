#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../hdr/segmentation.h"

// Prototypes
static LINES *Get_lines(int rows, int columns, const int *pixels);
static void Push_line(LINES *head, int upper, int lower);

static CHARACTERS *Get_char(
        int rows, int columns, const int *pixels, LINES *firstLine);
static void Push_char(CHARACTERS *head, BOUNDS bounds);


// Functions
// Image segmentation

/**
 * Segments the image and returns the rectangle containing the characters
 *
 * @author Yvon Morice
 * @param rows, the number of rows of pixels in the image
 * @param columns, the number of columns of pixels in the image
 * @param pixels, the matrix of pixels after the binarization of the image
 * @return a linked list of the rectangle containing the characters
 */
CHARACTERS *Segment_image(int rows, int columns, int *pixels)
{
    LINES *lines = Get_lines(rows, columns, pixels);
    CHARACTERS *characters = Get_char(rows, columns, pixels, lines);

    return characters;
}

// Line segmentation

/**
 * Segments the image into different lines
 *
 * @author Yvon Morice
 * @param rows, the number of rows of pixels in the image
 * @param columns, the number of columns of pixels in the image
 * @param pixels, the matrix of pixels after the binarization of the image
 * @return a linked list of the lines as rectangles
 *         (we only save the upper and lower bounds of the rectangle)
 */
static LINES *Get_lines(int rows, int columns, const int *pixels)
{
    int histogram[rows];

    int sum;
    int mean_val = 0;
    for (int i = 0; i < rows; ++i)
    {
        sum = 0;
        for (int j = 0; j < columns; ++j) {
            sum += *((pixels + i * rows) + j);
        }
        mean_val += sum;
        histogram[i] = sum;
    }

    int threshold = mean_val / rows;


    LINES *first = malloc(sizeof(LINES));
    first -> next = NULL;
    first -> upper = 0;

    int start;
    int end;

    for (int i = 0; i < rows; ++i)
    {
        if (histogram[i] > threshold)
        {
            start = i++;

            while (i < rows && histogram[i++] > threshold)
                ;

            end = i - 1;

            Push_line(first, start, end);
        }
    }

    return first;
}

/**
 * Pushes a new element into the linked list of lines
 *
 * @author Yvon Morice
 * @param head, the first line of the list
 * @param upper, the upper bound value of the new element
 * @param lower, the lower bound value of the new element
 */
static void Push_line(LINES *head, int upper, int lower)
{
    if (head -> upper == 0)
    {
        head -> upper = upper;
        head -> lower = lower;
        return;
    }

    LINES *current = head;
    while (current -> next != NULL)
        current = current -> next;

    current -> next = malloc(sizeof(LINES));
    current -> next -> upper = upper;
    current -> next -> lower = lower;
    current -> next -> next = NULL;
}

// Character segmentation

/**
 * Segments the image into different characters using
 * the lines determined with Get_lines.
 *
 * @author Yvon Morice
 * @param rows, the number of rows of pixels in the image
 * @param columns, the number of columns of pixels in the image
 * @param pixels, the matrix of pixels after the binarization of the image
 * @param firstLine, the first element of the linked list of lines
 * @return the first element of the linked list of characters
 */
static CHARACTERS *Get_char(
        int rows, int columns, const int *pixels, LINES *firstLine)
{
    LINES *currentLine = firstLine;
    CHARACTERS *first = malloc(sizeof(CHARACTERS));
    first -> next = NULL;
    first -> bounds.upper = 0;
    first -> bounds.lower = 0;

    int histogram[columns];
    int sum, mean_val, threshold;

    while (currentLine != NULL)
    {
        mean_val = 0;

        for (int j = 0; j < columns; ++j)
        {
            sum = 0;
            for (int i = currentLine -> upper; i < currentLine -> lower; ++i)
                sum += *((pixels + i * rows) + j);

            histogram[j] = sum;
            mean_val += sum;
        }

        threshold = mean_val / columns;

        int left;

        for (int j = 0; j < columns; ++j)
        {
            if (histogram[j] > threshold)
            {
                left = j++;

                while (j < columns && histogram[j++] > threshold)
                    ;

                BOUNDS bounds =
                        {
                                currentLine -> upper, currentLine -> lower, left, j - 1
                        };

                Push_char(first, bounds);
            }
        }

        currentLine = currentLine -> next;
    }

    return first;
}

/**
 * Pushes a new element into the linked list of characters
 *
 * @author Yvon Morice
 * @param head, the first character of the list
 * @param bounds, the bounds of the rectangle containing the character
 */
static void Push_char(CHARACTERS *head, BOUNDS bounds)
{
    if (head -> bounds.upper == 0)
    {
        head -> bounds = bounds;
        return;
    }

    CHARACTERS *current = head;
    while (current -> next != NULL)
        current = current -> next;

    current -> next = malloc(sizeof(CHARACTERS));
    current -> next -> bounds = bounds;
    current -> next -> next = NULL;
}

// Save

/**
 * Saves the result of the segmentation in a file
 *
 * @param text, the string that will contain the result
 * @param rows, the number of rows of pixels in the image
 * @param matrix, the values of the pixels after having been binarized
 * @param firstChar, the linked list of characters
 */
int Save_segmentation(int rows, const int *matrix, CHARACTERS *firstChar)
{
    FILE *file;
    char *filename = "seg.txt";

    if ((file = fopen(filename, "w+")) == NULL)
    {
        printf("Impossible to open the file \"%s\"", filename);
        return 1;
    }

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

        fprintf(file, "word: %3d %3d %3d %3d\n", upper, lower, left, right);

        for (int i = upper; i < lower ; ++i)
        {
            for (int j = left; j < right; ++j)
            {
                fprintf(file, "%d", *(matrix + i * rows + j));
            }
            fprintf(file, "\n");
        }

        fprintf(file, "\n");

        current = current -> next;
    }

    fclose(file);
    printf("file: \"%s\": saved successfully!\n", filename);
    return 0;
}