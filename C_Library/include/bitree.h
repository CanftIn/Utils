/*
    C_Library: some useful tools set
    Module: bitree
	Copyright (c) 2018 by CanftIn <wwc7033@gmail.com>
	contact me at http://www.canftin.com
	MIT licence
*/

#ifndef BITREE_H
#define BITREE_H

#include <stdlib.h>

#include "../include/list.h"

typedef struct BiTreeNode
{
    void *data;
    struct BiTreeNode *right;
    struct BiTreeNode *left;
}BiTreeNode;

typedef struct BiTree
{
    size_t size;
    int (*compare)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    BiTreeNode *root;
}BiTree;

void bitree_init(BiTree *tree, void (*destroy)(void *data));

void bitree_destroy(BiTree *tree);

int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data);

int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data);

void bitree_rem_left(BiTree *tree, BiTreeNode *node);

void bitree_rem_right(BiTree *tree, BiTreeNode *node);

int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);

#define bitree_size(tree) ((tree)->size)

#define bitree_root(tree) ((tree)->root)

#define bitree_is_eob(node) ((node) == NULL)

#define bitree_is_leaf(node) ((node)->left == NULL && (node)->rigth == NULL)

#define bitree_data(node) ((node)->data)

#define bitree_left(node) ((node)->left)

#define bitree_right(node) ((node)->right)


/*  traverse  */

int preorder(const BiTreeNode *node, List *list);

int inorder(const BiTreeNode *node, List *list);

int postorder(const BiTreeNode *node, List *list);

#endif // !BITREE_H
