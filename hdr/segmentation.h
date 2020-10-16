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
LINES *Get_lines(int rows, int columns, int pixels[rows][columns]);
void Push_line(LINES *head, int upper, int lower);

CHARACTERS *Get_char(
        int rows, int columns, int pixels[rows][columns], LINES *firstLine);
void Push_char(CHARACTERS *head, BOUNDS bounds);

#endif //OCR_HISTOGRAM_H
