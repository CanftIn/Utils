#ifndef __BINTREE_H__
#define __BINTREE_H__

#include "Global.h"

typedef struct BINTREENODE_st
{
	struct BINTREENODE_st* pLeft;
	struct BINTREENODE_st* pRight;
	void*	pData;
}BINTREENODE;

typedef struct BINTREEBASENODE_st
{
	struct BINTREEBASENODE_st*	pLeft;
	struct BINTREEBASENODE_st*	pRight;
	struct BINTREEBASENODE_st*	pParent;
	INT							nMagic;
	void*						pData;
	UINT						uCount;
}BINTREEBASENODE;

typedef struct BINTREE_st
{
	BINTREEBASENODE*	pRoot;
	UINT				uNodeCount;
}BINTREE;

BINTREE *BinTree_Create(void);
void BinTreeBaseNode_Destroy(BINTREEBASENODE *pBINTREEBASENODE,
	DESTROYFUNC DestroyFunc);
void    BinTree_Destroy(BINTREE *pBinTree, DESTROYFUNC DestroyFunc);

INT     BinTree_Add(BINTREE *pBinTree, void *pData, COMPAREFUNC CompareFunc);
void *BinTree_Find(BINTREEBASENODE *pRoot, void *pData, COMPAREFUNC CompareFunc);
BINTREEBASENODE *BinTree_FindNode(BINTREEBASENODE *pRoot, void *pData, COMPAREFUNC CompareFunc);
INT     BinTree_AddLeft(BINTREE *pBinTree, void *pTagNodeData,
	void *pData, COMPAREFUNC CompareFunc);
INT     BinTree_AddRight(BINTREE *pBinTree, void *pTagNodeData,
	void *pData, COMPAREFUNC CompareFunc);
INT     BinTree_Delete(BINTREE *pBinTree, void *pData,
	COMPAREFUNC CompareFunc,
	DESTROYFUNC DestroyFunc);

void BinTree_RotateLeft(BINTREEBASENODE *pANode, BINTREEBASENODE **ppRoot);
void BinTree_RotateRight(BINTREEBASENODE *pANode, BINTREEBASENODE **ppRoot);

void BinTree_CheckParent(BINTREEBASENODE *pRootNode);

INT BinTree_Insert(BINTREEBASENODE **pRoot, void *pData, COMPAREFUNC CompareFunc, INT nMagic);

void BinTree_InOrderTraverse(BINTREE *pTree, VISITFUNC VisitFunc);
void BinTree_PreOrderTraverse(BINTREE *pTree, VISITFUNC VisitFunc);
void BinTree_PostOrderTraverse(BINTREE *pTree, VISITFUNC VisitFunc);



#endif