#include <stdlib.h>
#include "../hdr/list.h"

List *new_list(void)
{
    return NULL;
}

int empty(List *list)
{
    return list == NULL || list->length == 0 ? 1 : 0;
}

size_t get_length(List *list)
{
    return empty(list) ? 0 : list->length;
}

Element *get_first(List *list)
{
    return empty(list) ? NULL : list->first;
}

Element *get_last(List *list)
{
    return empty(list) ? NULL : list->last;
}

List *push_last_list(List *list, void *x, ElementType elementType)
{
    Element *elt;
    elt = malloc(sizeof(*elt));

    if (elt == NULL)
    {
        exit(1);
    }

    elt->val = x;
    elt->prev = NULL;
    elt->next = NULL;

    if (empty(list))
    {
        list = malloc(sizeof(*list));

        if (list == NULL)
            exit(1);

        list->eltType = elementType;
        list->length = 0;
        list->first = elt;
        list->last = elt;
    }
    else
    {
        if (elementType != list->eltType)
            exit(1);

        list->last->next = elt;
        elt->prev = list->last;
        list->last = elt;
    }

    (list->length)++;

    return list;
}

List *push_first_list(List *list, void *x, ElementType elementType)
{
    Element *elt;
    elt = malloc(sizeof(*elt));

    if (elt == NULL)
    {
        exit(1);
    }

    elt->val = x;
    elt->prev = NULL;
    elt->next = NULL;

    if (empty(list))
    {
        list = malloc(sizeof(*list));

        if (list == NULL)
            exit(1);

        list->eltType = elementType;
        list->length = 0;
        list->first = elt;
        list->last = elt;
    }
    else
    {
        if (elementType != list->eltType)
            exit(1);

        list->first->prev = elt;
        elt->next = list->first;
        list->first = elt;
    }

    list->length++;

    return list;
}

List *pop_last_list(List *list)
{
    if (empty(list))
    {
        return new_list();
    }

    if (list->first == list->last)
    {
        free(list);
        list = NULL;
        return new_list();
    }

    Element *temp = list->last;

    list->last = list->last->prev;
    list->last->next = NULL;

    temp->next = NULL;
    temp->prev = NULL;

    free(temp);
    temp = NULL;

    list->length--;
    return list;
}

List *pop_first_list(List *list)
{
    if (empty(list))
    {
        return new_list();
    }

    if (list->first == list->last)
    {
        free(list);
        list = NULL;
        return new_list();
    }

    Element *temp = list->first;

    list->first = list->first->next;
    list->first->prev = NULL;

    temp->next = NULL;
    temp->prev = NULL;

    free(temp);
    temp = NULL;

    list->length--;
    return list;
}

Element *get_element(List *list, int i)
{
    unsigned long index = i;

    if (index >= list->length)
        exit(1);

    Element *elt = list->first;

    while (i-- > 0)
        elt = elt->next;

    return elt;
}

List *clear_list(List *list)
{
    while (!empty(list))
        list = pop_last_list(list);

    return new_list();
}
