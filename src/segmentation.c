#include <stdlib.h>

#include "../hdr/segmentation.h"

// Line segmentation
LINES *Get_lines(int rows, int columns, int *pixels)
{
    int histogram[rows];

    int sum;
    int mean_val = 0;
    for (int i = 0; i < rows; ++i)
    {
        sum = 0;
        for (int j = 0; j < columns; ++j)
            sum += *((pixels + i * rows) + j);
        mean_val += sum;
        histogram[i] = sum;
    }

    int threshold = mean_val / rows;

    LINES *first = malloc(sizeof(LINES));
    first -> next = NULL;

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

void Push_line(LINES *head, int upper, int lower)
{
    if (head -> next == NULL)
    {
        head -> upper = upper;
        head -> lower = lower;
        return;
    }

    LINES *current = head;
    while (current -> next != NULL)
        current = current -> next;

    LINES *new = malloc(sizeof(LINES));
    new -> upper = upper;
    new -> lower = lower;
    new -> next = NULL;

    current -> next = new;
}


// Character segmentation
CHARACTERS *Get_char(
        int rows, int columns, int *pixels, LINES *firstLine)
{
    LINES *currentLine = firstLine;
    CHARACTERS *first = malloc(sizeof(CHARACTERS));
    first -> next = NULL;

    int histogram[columns];
    int sum;
    int mean_val;
    int threshold;

    while (currentLine != NULL)
    {
        mean_val = 0;

        for (int j = 0; j < columns; ++j)
        {
            sum = 0;
            for (int i = 0; i < rows; ++i)
                sum += *((pixels + i * rows) + j);

            histogram[j] = sum;
            mean_val += sum;
        }

        threshold = mean_val/columns;

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

void Push_char(CHARACTERS *head, BOUNDS bounds)
{
    if (head -> next == NULL)
    {
        head -> bounds = bounds;
        return;
    }

    CHARACTERS *current = head;
    while (current -> next != NULL)
        current = current -> next;

    CHARACTERS *new = malloc(sizeof(CHARACTERS));
    new -> bounds = bounds;
    new -> next = NULL;

    current -> next = new;
}