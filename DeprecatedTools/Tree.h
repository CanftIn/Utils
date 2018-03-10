#ifndef __TREE_H__
#define __TREE_H__

#include "Global.h"
#include "DoubleList.h"

typedef struct TREE_st
{
	DOUBLELIST*	pLeafList;
	DOUBLELIST* pSubTreeList;
	void*		pProperties;
}TREE, *LPTREE;

typedef int(*COMPAREFUNC)(void *prop1, void *prop2);

// Initialize and destroy functions
TREE *  Tree_Create();

void    Tree_Destroy(
	TREE * pTree,
	DESTROYFUNC LeafDestroyFunc,
	DESTROYFUNC PropDestroyFunc);

// Leaf functions
int     Tree_AddLeaf(TREE * pTree, void *pLeafData);
int     Tree_RemoveLeaf(TREE * pTree,
	void *pLeafData,
	COMPAREFUNC CompareFunc,
	DESTROYFUNC LeafDestroyFunc);

// Properties functions
int     Tree_SetProperties(TREE * pTree,
	void * pProperties,
	DESTROYFUNC PropDestroyFunc);

void *  Tree_GetProperties(TREE * pTree);

// Sub pTree functions
int     Tree_AddSubTree(TREE * pTree, TREE * sub);

int     Tree_RemoveSubTree(
	TREE * pTree,
	TREE * sub,
	DESTROYFUNC leaffunc,
	DESTROYFUNC propfunc);

// Copy function
TREE *    Tree_Copy(
	TREE * pTree,
	COPYFUNC LeafCopyFunc,
	COPYFUNC PropCopyFunc);

// Search functions
TREE *    Tree_FindSubTreeByProp(
	TREE  * pTree,
	void  * pProperties,
	COMPAREFUNC   CompareFunc
	);




#endif