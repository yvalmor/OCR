#ifndef LIST_H
#define LIST_H


/**
 * An enum containing the type of the element in a List
 *
 * @see List
 */
typedef enum{
    ParagraphType,
    LineType,
    WordType,
    LetterType
} ElementType;


/**
 * The structure that contains a part of a binarized image
 */
typedef struct ImagePart
{
    int *img;
    int rows;
    int cols;
} ImagePart;


/**
 * The structure that wraps the elements of a List
 *
 * @see List
 */
typedef struct Element {
    void *val;
    struct Element *prev,
                   *next;
} Element;


/**
 * A generic linked list
 */
typedef struct List {
    ElementType eltType;
    unsigned long length;
    struct Element *first,
                   *last;
} List;


/**
 * Creates a new List
 *
 * @author Yvon Morice
 * @return a NULL pointer
 */
List *new_list(void);


/**
 * Check if a List is empty
 *
 * @author Yvon Morice
 * @param list, List
 * @return 1 if it is empty, 0 otherwise
 */
int empty(List *list);


/**
 * Gets the length of a list
 *
 * @author Yvon Morice
 * @param list, List
 * @return the length of list
 */
unsigned long get_length(List *list);


/**
 * Gets the first element of a list
 *
 * @author Yvon Morice
 * @param list, List
 * @return the first Element of list
 */
Element *get_first(List *list);


/**
 * Gets the last element of a list
 *
 * @author Yvon Morice
 * @param list, List
 * @return the last Element of list
 */
Element *get_last(List *list);


/**
 * Pushes an element at the end of a list
 *
 * @author Yvon Morice
 * @param list, List
 * @param x, pointer towards the element we want to push
 * @param elementType
 * @return a pointer towards the head of the list
 */
List *push_last_list(List *list, void *x, ElementType elementType);


/**
 * Pushes an element at the head of a list
 *
 * @author Yvon Morice
 * @param list, List
 * @param x, pointer towards the element we want to push
 * @param elementType
 * @return a pointer towards the head of the list
 */
List *push_first_list(List *list, void *x, ElementType elementType);


/**
 * Removes the last element of a list
 *
 * @author Yvon Morice
 * @param list, List
 * @return NULL if the list becomes or was empty, a pointer towards
 *         the head of the list otherwise
 */
List *pop_last_list(List *list);


/**
 * Removes the first element of a list
 *
 * @author Yvon Morice
 * @param list, List
 * @return NULL if the list becomes or was empty, a pointer towards
 *         the head of the list otherwise
 */
List *pop_first_list(List *list);


/**
 * Gets the ith element of a list
 *
 * @author Yvon Morice
 * @param list, List
 * @param i, int
 * @return the element at the ith position
 */
Element *get_element(List *list, int i);


/**
 * Frees the list
 *
 * @author Yvon Morice
 * @param list, List
 * @return a NULL pointer
 */
List *clear_list(List *list);


#endif
