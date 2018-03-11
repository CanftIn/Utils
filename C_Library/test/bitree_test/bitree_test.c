/*
    C_Library: some useful tools set
    Module: bitree_test
	Copyright (c) 2018 by CanftIn <wwc7033@gmail.com>
	contact me at http://www.canftin.com
	MIT licence
*/

#include <stdio.h>
#include <stdlib.h>

#include "../../include/bitree.h"

static void print_preorder(const BiTreeNode *node)
{
    if (!bitree_is_eob(node))
    {
        fprintf(stdout, "Node=%03d\n", *(int *)bitree_data(node));

        if (!bitree_is_eob(bitree_left(node)))
            print_preorder(bitree_left(node));

        if (!bitree_is_eob(bitree_right(node)))
            print_preorder(bitree_right(node));
    }
    return;
}

static void print_inorder(const BiTreeNode *node)
{
    if (!bitree_is_eob(node))
    {
        if (!bitree_is_eob(bitree_left(node)))
            print_inorder(bitree_left(node));

        fprintf(stdout, "Node=%03d\n", *(int *)bitree_data(node));

        if (!bitree_is_eob(bitree_right(node)))
            print_inorder(bitree_right(node));
    }
    return;
}

static void print_postorder(const BiTreeNode *node)
{
    if (!bitree_is_eob(node))
    {
        if (!bitree_is_eob(bitree_left(node)))
            print_postorder(bitree_left(node));

        if (!bitree_is_eob(bitree_right(node)))
            print_postorder(bitree_right(node));

        fprintf(stdout, "Node=%03d\n", *(int *)bitree_data(node));
    }
    return;
}

static int insert_int(BiTree *tree, int i)
{
    BiTreeNode *node,
        *prev;
    int direction,
        *data;

    node = tree->root;
    direction = 0;

    while (!bitree_is_eob(node))
    {
        prev = node;
        if (i == *(int *)bitree_data(node))
        {
            return -1;
        }
        else if (i < *(int *)bitree_data(node))
        {
            node = bitree_left(node);
            direction = 1;
        }
        else
        {
            node = bitree_right(node);
            direction = 2;
        }
    }

    if ((data = (int *)malloc(sizeof(int))) == NULL)
        return -1;

    *data = i;

    if (direction == 0)
        return bitree_ins_left(tree, NULL, data);

    if (direction == 1)
        return bitree_ins_left(tree, prev, data);

    if (direction == 2)
        return bitree_ins_right(tree, prev, data);

    return -1;
}

static BiTreeNode *search_int(BiTree *tree, int i)
{

    BiTreeNode *node;
    node = bitree_root(tree);

    while (!bitree_is_eob(node))
    {
        if (i == *(int *)bitree_data(node))
        {
            return node;
        }
        else if (i < *(int *)bitree_data(node))
        {
            node = bitree_left(node);
        }
        else
        {
            node = bitree_right(node);
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{

    BiTree tree;
    BiTreeNode *node;

    int i;

    bitree_init(&tree, free);

    fprintf(stdout, "Inserting some nodes\n");

    if (insert_int(&tree, 20) != 0)
        return 1;

    if (insert_int(&tree, 10) != 0)
        return 1;

    if (insert_int(&tree, 30) != 0)
        return 1;

    if (insert_int(&tree, 15) != 0)
        return 1;

    if (insert_int(&tree, 25) != 0)
        return 1;

    if (insert_int(&tree, 70) != 0)
        return 1;

    if (insert_int(&tree, 80) != 0)
        return 1;

    if (insert_int(&tree, 23) != 0)
        return 1;

    if (insert_int(&tree, 26) != 0)
        return 1;

    if (insert_int(&tree, 5) != 0)
        return 1;

    fprintf(stdout, "Tree size is %d\n", bitree_size(&tree));
    fprintf(stdout, "(Preorder traversal)\n");
    print_preorder(bitree_root(&tree));

    fprintf(stdout, "(Postorder traversal)\n");
    print_postorder(bitree_root(&tree));

    fprintf(stdout, "(inorder traversal)\n");
    print_inorder(bitree_root(&tree));

    fprintf(stdout, "Destroying the tree\n");
    bitree_destroy(&tree);

    return 0;
}

/*
Test result:
    Inserting some nodes
    Tree size is 10
    (Preorder traversal)
    Node=020
    Node=010
    Node=005
    Node=015
    Node=030
    Node=025
    Node=023
    Node=026
    Node=070
    Node=080
    (Postorder traversal)
    Node=005
    Node=015
    Node=010
    Node=023
    Node=026
    Node=025
    Node=080
    Node=070
    Node=030
    Node=020
    (inorder traversal)
    Node=005
    Node=010
    Node=015
    Node=020
    Node=023
    Node=025
    Node=026
    Node=030
    Node=070
    Node=080
    Destroying the tree

*/