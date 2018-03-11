/*
    C_Library: some useful tools set
    Module: set_test
	Copyright (c) 2018 by CanftIn <wwc7033@gmail.com>
	contact me at http://www.canftin.com
	MIT licence
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/list.h"
#include "../../include/set.h"

static void print_set(const Set *set)
{
    ListElem *member;

    int *data;
    int size;

    fprintf(stdout, "Set size is %d\n", size = set_size(set));

    int i = 0;
    member = list_head(set);

    while (i < size)
    {

        data = list_data(member);
        fprintf(stdout, "set[%03d]=%03d\n", i, *data);
        member = list_next(member);
        i++;
    }

    return;
}

static int match_int(const void *key1, const void *key2)
{
    return !memcmp(key1, key2, sizeof(int));
}

int main(int argc, char **argv)
{
    Set set,
        set1,
        set2;

    int *data,
        retval,
        i;

    set_init(&set, match_int, free);

    fprintf(stdout, "Inserting 10 members\n");

    for (i = 9; i >= 0; i--)
    {
        if ((data = (int *)malloc(sizeof(int))) == NULL)
            return 1;

        *data = i + 1;

        if ((retval = set_insert(&set, data)) < 0)
            return 1;
        else if (retval == 1)
            free(data);
    }

    print_set(&set);

    set_init(&set1, match_int, free);
    set_init(&set2, match_int, free);

    for (i = 9; i >= 0; i--)
    {
        if ((data = (int *)malloc(sizeof(int))) == NULL)
            return 1;

        *data = i + 1;

        if ((retval = set_insert(&set1, data)) < 0)
            return 1;
        else if (retval == 1)
            free(data);

        if (i == 5 || i == 6 || i == 7)
        {
            if ((data = (int *)malloc(sizeof(int))) == NULL)
                return 1;

            *data = i * 10;

            if ((retval = set_insert(&set2, data)) < 0)
                return 1;
            else if (retval == 1)
                free(data);
        }

        else if (i == 3 || i == 1)
        {
            if ((data = (int *)malloc(sizeof(int))) == NULL)
                return 1;

            *data = i;

            if ((retval = set_insert(&set2, data)) < 0)
                return 1;
            else if (retval == 1)
                free(data);
        }
    }

    fprintf(stdout, "Set 1 for testing unions, intersections, and differences\n");
    print_set(&set1);
    fprintf(stdout, "Set 2 for testing unions, intersections, and differences\n");
    print_set(&set2);

    fprintf(stdout, "Determining the union of the two sets\n");

    if (set_union(&set, &set1, &set2) != 0)
        return 1;

    print_set(&set);

    fprintf(stdout, "Destroying the union\n");
    set_destroy(&set);

    fprintf(stdout, "Determining the intersection of the two sets\n");

    if (set_intersection(&set, &set1, &set2) != 0)
        return 1;

    print_set(&set);

    fprintf(stdout, "Destroying the sets\n");
    set_destroy(&set);
    set_destroy(&set1);
    set_destroy(&set2);

    return 0;
}


/*
Test result:
    Inserting 10 members
    Set size is 10
    set[000]=010
    set[001]=009
    set[002]=008
    set[003]=007
    set[004]=006
    set[005]=005
    set[006]=004
    set[007]=003
    set[008]=002
    set[009]=001
    Set 1 for testing unions, intersections, and differences
    Set size is 10
    set[000]=010
    set[001]=009
    set[002]=008
    set[003]=007
    set[004]=006
    set[005]=005
    set[006]=004
    set[007]=003
    set[008]=002
    set[009]=001
    Set 2 for testing unions, intersections, and differences
    Set size is 5
    set[000]=070
    set[001]=060
    set[002]=050
    set[003]=003
    set[004]=001
    Determining the union of the two sets
    Set size is 13
    set[000]=010
    set[001]=009
    set[002]=008
    set[003]=007
    set[004]=006
    set[005]=005
    set[006]=004
    set[007]=003
    set[008]=002
    set[009]=001
    set[010]=070
    set[011]=060
    set[012]=050
    Destroying the union
    Determining the intersection of the two sets
    Set size is 2
    set[000]=003
    set[001]=001
    Destroying the sets

*/