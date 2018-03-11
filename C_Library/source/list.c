/*
    C_Library: some useful tools set
    Module: list
	Copyright (c) 2018 by CanftIn <wwc7033@gmail.com>
	contact me at http://www.canftin.com
	MIT licence
*/

#include <string.h>                 /* memset */
#include "../include/list.h"

/**
 * list: init
 **/
void list_init(List *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

/**
 * list: destroy all elements
 **/
void list_destroy(List *list)
{
    void *data;
    while(list_size(list) > 0)
    {
        if(list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL)
        {
            list->destroy(data);
        }
    }
    memset(list, 0, sizeof(list));
}

/**
 * list: insert new element after target element
 **/
int list_ins_next(List *list, ListElem *element, const void *data)
{
    ListElem *new_element;
    if((new_element = (ListElem *)malloc(sizeof(ListElem))) == NULL)
        return -1;

    new_element->data = (void *)data;
    if(element == NULL)
    {
        if(list_size(list) == 0)
            list->tail = new_element;
        
        //insert at head node
        new_element->next = list->head;
        list->head = new_element;
    }
    else
    {
        if(element->next == NULL)
            list->tail = new_element;
        
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;
    return 0;
}

/**
 * list: remove element after target element from list
 **/
int list_rem_next(List *list, ListElem *element, void **data)
{
    ListElem *old_element;

    if(list_size(list) == 0)
        return -1;
    
    if(element == NULL)
    {
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;

        if(list_size(list) == 1)
            list->tail = NULL;
    }
    else
    {
        if(element->next == NULL)
            return -1;

        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;

        if(element->next == NULL)
            list->tail = element;
    }
    list->size--;
    free(old_element);
    return 0;
}
