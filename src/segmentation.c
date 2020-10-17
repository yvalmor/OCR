#include <stdlib.h>

#include "../hdr/segmentation.h"

// Prototypes
static LINES *Get_lines(int rows, int columns, const int *pixels);
static void Push_line(LINES *head, int upper, int lower);

static CHARACTERS *Get_char(
        int rows, int columns, const int *pixels, LINES *firstLine);
static void Push_char(CHARACTERS *head, BOUNDS bounds);

// Functions
// Segmentation
CHARACTERS *Segment_image(int rows, int columns, const int *pixels)
{
    LINES *lines = Get_lines(rows, columns, pixels);
    CHARACTERS *characters = Get_char(rows, columns, pixels, lines);

    return characters;
}

// Line segmentation
static LINES *Get_lines(int rows, int columns, const int *pixels)
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
static CHARACTERS *Get_char(
        int rows, int columns, const int *pixels, LINES *firstLine)
{
    LINES *currentLine = firstLine;
    CHARACTERS *first = malloc(sizeof(CHARACTERS));
    first -> next = NULL;
    first -> bounds.upper = 0;

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
            for (int i = currentLine -> upper; i < currentLine -> lower; ++i)
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