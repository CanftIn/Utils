/*
    C_Library: some useful tools set
    Module: list
	Copyright (c) 2018 by CanftIn <wwc7033@gmail.com>
	contact me at http://www.canftin.com
	MIT licence
*/

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct ListElem
{
    void *data;
    struct ListElem *next;
}ListElem;

typedef struct List
{
    size_t size;
    int (*match)(const void *key1, const void *key2);       /* use in set */
    void (*destroy)(void *data);
    ListElem *head;
    ListElem *tail;
}List;

/**
 * Interface
 **/
void list_init(List *list, void (*destroy)(void *data));

void list_destroy(List *list);

int list_ins_next(List *list, ListElem *element, const void *data);

int list_rem_next(List *list, ListElem *element, void **data);

#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_is_head(list, element) ((list)->head == (element) ? 1 : 0)

#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)

#define list_data(element) ((element)->data)

#define list_next(element) ((element)->next)


#endif // !LIST_H
