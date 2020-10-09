#include <stdio.h>

#include "../hdr/linkedLines.h"

void push(LINES *head, int start, int end)
{
    LINES *current = head;
    while (current -> next != NULL)
        current = current -> next;

    LINES *new = malloc(sizeof(LINES));
    new -> start = start;
    new -> end = end;

    current -> next = new;
}

void printLines(LINES *head)
{
    LINES *current = head;
    while (current -> next != NULL)
    {
        printf("%d %d\n", current -> start, current -> end);
        current = current -> next;
    }
}