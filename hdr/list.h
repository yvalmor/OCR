#ifndef LIST_H
#define LIST_H


typedef enum{
    ParagraphType,
    LineType,
    WordType,
    LetterType
} ElementType;



typedef struct ImagePart
{
    int *img;
    int rows;
    int cols;
} ImagePart;

typedef struct Element {
    void *val;
    struct Element *prev,
                   *next;
} Element;

typedef struct List {
    ElementType eltType;
    unsigned long length;
    struct Element *first,
                   *last;
} List;



List new_list(void);

int empty(List list);

unsigned long get_length(List list);

Element *get_first(List list);

Element *get_last(List list);

List push_last_list(List list, void *x, ElementType elementType);

List push_first_list(List list, void *x, ElementType elementType);

List pop_last_list(List list);

List pop_first_list(List list);

Element *get_element(List list, int i);

List clear_list(List list);


#endif
