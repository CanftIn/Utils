/*
    C_Library: some useful tools set
    Module: list_test
	Copyright (c) 2018 by CanftIn <wwc7033@gmail.com>
	contact me at http://www.canftin.com
	MIT licence
*/

#include <stdio.h>
#include <stdlib.h>

#include "../../include/list.h"

/**
 * print list
 **/
static void print_list(const List *list)
{
    ListElem *element;
    int *data;
    int i = 0;
    fprintf(stdout, "List size is %d \n", list_size(list));
    element = list_head(list);

    while(1)
    {
        data = list_data(element);
        fprintf(stdout, "list[%03d]=%03d\n", i, *data);
        i++;

        if(list_is_tail(element))
            break;
        else
            element = list_next(element);
    }
    return;
}

int main(int argc, char **argv)
{
    List list;
    ListElem *element;

    int *data;
    
    list_init(&list, free);

    element = list_head(&list);

    for(int i = 10; i > 0; --i)
    {
        if((data = (int *)malloc(sizeof(int))) == NULL)
            return 1;
        *data = i;

        if(list_ins_next(&list, NULL, data) != 0)
            return 1;
    }

    print_list(&list);

    element = list_head(&list);
    for (int i = 0; i < 7; i++)
        element = list_next(element);

    data = list_data(element);
    fprintf(stdout, "Removing an element after the one containing %03d\n", *data);

    if (list_rem_next(&list, element, (void **)&data) != 0)
        return 1;

    print_list(&list);

    
    fprintf(stdout, "Inserting 011 at the tail of the list\n");

    *data = 11;
    if (list_ins_next(&list, list_tail(&list), data) != 0)
        return 1;

    print_list(&list);

    fprintf(stdout, "Destroying the list\n");
    list_destroy(&list);
    return 0;
}