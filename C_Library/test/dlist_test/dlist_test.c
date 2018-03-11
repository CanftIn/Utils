/*
    C_Library: some useful tools set
    Module: dlist_test
	Copyright (c) 2018 by CanftIn <wwc7033@gmail.com>
	contact me at http://www.canftin.com
	MIT licence
*/

#include <stdio.h>
#include <stdlib.h>

#include "../../include/dlist.h"

/**
 * print list
 **/
static void print_list(const DList *list)
{
    DListElem *element;
    int *data;
    int i = 0;
    fprintf(stdout, "List size is %d \n", dlist_size(list));
    element = dlist_head(list);

    while(1)
    {
        data = dlist_data(element);
        fprintf(stdout, "list[%03d]=%03d\n", i, *data);
        i++;

        if(dlist_is_tail(element))
            break;
        else
            element = dlist_next(element);
    }
    return;
}

int main(int argc, char **argv) 
{
    DList list;
    DListElem *element;

    int *data;
    dlist_init(&list, free);

    element = dlist_head(&list);
    for(int i = 10; i > 0; --i)
    {
        if((data = (int *)malloc(sizeof(int))) == NULL)
            return 1;
        
        *data = i;
        if(dlist_ins_next(&list, dlist_head(&list), data) != 0)
            return 1;
    }

    print_list(&list);

    *data = 13;

    fprintf(stdout, "insert 13 \n");
    if (dlist_ins_prev(&list, dlist_head(&list), data) != 0)
        return 1;
    print_list(&list);

    fprintf(stdout, "remove head \n");
    if (dlist_remove(&list, dlist_head(&list), (void **)&data) != 0)
        return 1;

    print_list(&list);
    dlist_destroy(&list);

    return 0;
}


/*
test result:
    List size is 10
    list[000]=010
    list[001]=001
    list[002]=002
    list[003]=003
    list[004]=004
    list[005]=005
    list[006]=006
    list[007]=007
    list[008]=008
    list[009]=009
    insert 13
    List size is 11
    list[000]=013
    list[001]=010
    list[002]=013
    list[003]=002
    list[004]=003
    list[005]=004
    list[006]=005
    list[007]=006
    list[008]=007
    list[009]=008
    list[010]=009
    remove head
    List size is 10
    list[000]=010
    list[001]=013
    list[002]=002
    list[003]=003
    list[004]=004
    list[005]=005
    list[006]=006
    list[007]=007
    list[008]=008
    list[009]=009

*/