#ifndef OCR_LINKEDLINES_H
#define OCR_LINKEDLINES_H

typedef struct tagLINES
{
    int start;
    int end;
    struct tagLINES *next;
} LINES;

void push(LINES *head, int start, int end);
void printLines(LINES *head);

#endif //OCR_LINKEDLINES_H
