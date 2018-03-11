/*
    C_Library: some useful tools set
    Module: list benchmark test
	Copyright (c) 2018 by CanftIn <wwc7033@gmail.com>
	contact me at http://www.canftin.com
	MIT licence
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/list.h"

//#define WINDOW
#ifdef WINDOW
#include <Windows.h>
#endif

int main(void)
{
    clock_t start_time, end_time;
    start_time = clock();

#ifdef WINDOW
    DWORD start, stop;
    start = GetTickCount();
#endif

    List list;
    ListElem *element;

    int *data;
    
    list_init(&list, free);

    element = list_head(&list);

    for(int i = 50000000; i > 0; --i)
    {
        if((data = (int *)malloc(sizeof(int))) == NULL)
            return 1;
        *data = i;

        if(list_ins_next(&list, NULL, data) != 0)
            return 1;
    }

    end_time = clock();

#ifdef WINDOW
    stop = GetTickCount();
    printf("insert 100000000 elements cost %lld ms\n", stop - start);
#endif

    fprintf(stdout, "insert 50000000 elements cost %.3f ms\n", difftime(end_time, start_time));

    start_time = clock();
    list_destroy(&list);
    end_time = clock();
    fprintf(stdout, "remove 50000000 elements cost %.3f ms\n", difftime(end_time, start_time));
    return 0;
}

/*
test result:
    insert 50000000 elements cost 5822.000 ms
    remove 50000000 elements cost 4833.000 ms
*/