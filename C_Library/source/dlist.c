/*
    C_Library: some useful tools set
    Module: dlist
	Copyright (c) 2018 by CanftIn <wwc7033@gmail.com>
	contact me at http://www.canftin.com
	MIT licence
*/

#include <stdlib.h>
#include <string.h>

#include "../include/dlist.h"

void dlist_init(DList *dlist, void (*destroy)(void *data))
{
    dlist->size = 0;
    dlist->destroy = destroy;
    dlist->head = NULL;
    dlist->tail = NULL;
};

void dlist_destroy(DList *dlist)
{
    void *data;

    while(dlist_size(dlist) > 0)
    {
        if(dlist_remove(dlist, dlist_tail(dlist), (void **)&data) == 0 && dlist->destroy != NULL)
            dlist->destroy(data);
    }
    memset(dlist, 0, sizeof(DList));
    return;
}

int dlist_ins_next(DList *dlist, DListElem *element, const void *data)
{
    DListElem *new_element;

    if (element == NULL && dlist_size(dlist) != 0)
        return -1;

    if((new_element = (DListElem *)malloc(sizeof(DListElem))) == NULL)
        return -1;

    new_element->data = (void *)data;

    if(dlist_size(dlist) == 0)
    {
        dlist->head = new_element;
        dlist->head->next = NULL;
        dlist->head->prev = NULL;
        dlist->tail = new_element;
    }
    else
    {
        new_element->next = element->next;
        new_element->prev = element;

        if(element->next != NULL)
            element->next->prev = new_element;
        else
            dlist->tail = new_element;
            
        element->next = new_element;
    }

    dlist->size++;
    return 0;
}

int dlist_ins_prev(DList *dlist, DListElem *element, const void *data)
{
    DListElem *new_element;

    if (element == NULL && dlist_size(dlist) != 0)
        return -1;

    if((new_element = (DListElem *)malloc(sizeof(DListElem))) == NULL)
        return -1;

    new_element->data = (void *)data;

    if(dlist_size(dlist) == 0)
    {
        dlist->head = new_element;
        dlist->head->next = NULL;
        dlist->head->prev = NULL;
        dlist->tail = new_element;
    }
    else
    {
        new_element->next = element;
        new_element->prev = element->prev;

        if(element->prev != NULL)
            element->prev->next = new_element;
        else
            dlist->head = new_element;

        element->prev = new_element;
    }

    dlist->size++;
    return 0;
}

int dlist_remove(DList *dlist, DListElem *element, void **data)
{
    if (element == NULL && dlist_size(dlist) != 0)
        return -1;

    *data = element->data;

    if(element == dlist->head)
    {
        dlist->head = element->next;
        
        if(dlist->head == NULL)
            dlist->tail = NULL;
        else
            element->next->prev = NULL;
    }
    else
    {
        element->prev->next = element->next;

        if(element->next == NULL)
            dlist->tail = element->prev;
        else
            element->next->prev = element->prev;
    }

    free(element);
    dlist->size--;
    return 0;
}