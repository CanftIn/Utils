/*
    C_Library: some useful tools set
    Module: dlist
	Copyright (c) 2018 by CanftIn <wwc7033@gmail.com>
	contact me at http://www.canftin.com
	MIT licence
*/

#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

typedef struct DListElem
{
    void *data;
    struct DListElem *prev;
    struct DListElem *next;
}DListElem;

typedef struct DList
{
    size_t size;
    void (*destroy)(void *data);
    DListElem *head;
    DListElem *tail;
}DList;

void dlist_init(DList *dlist, void (*destroy)(void *data));

void dlist_destroy(DList *dlist);

int dlist_ins_next(DList *dlist, DListElem *element, const void *data);

int dlist_ins_prev(DList *dlist, DListElem *element, const void *data);

int dlist_remove(DList *dlist, DListElem *element, void **data);

#define dlist_size(dlist) (dlist->size)

#define dlist_head(dlist) ((dlist)->head)

#define dlist_tail(dlist) ((dlist)->tail)

#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)

#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)

#define dlist_data(element) ((element)->data)

#define dlist_prev(element) ((element)->prev)

#define dlist_next(element) ((element)->next)

#endif // !DLIST_H
