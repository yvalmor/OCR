#ifndef OCR_HISTOGRAM_H
#define OCR_HISTOGRAM_H

// Structures
typedef struct tagBOUNDS
{
    int upper;
    int lower;
    int left;
    int right;
} BOUNDS;

typedef struct tagLINES
{
    int upper;
    int lower;
    struct tagLINES *next;
} LINES;

typedef struct tagCHARACTERS
{
    BOUNDS bounds;
    struct tagCHARACTERS *next;
} CHARACTERS;

// Prototypes
CHARACTERS *Segment_image(int rows, int columns, const int *pixels);

#endif //OCR_HISTOGRAM_H
