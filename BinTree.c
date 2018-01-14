#include "BinTree.h"

BINTREE* BinTree_Create()
{
	BINTREE* pBinTree;

	pBinTree = (BINTREE*)malloc(sizeof(BINTREE));

	if (pBinTree != NULL)
	{
		pBinTree->pRoot = NULL;
		pBinTree->uNodeCount = 0;
	}
	return pBinTree;
}

void BinTreeBaseNode_Destroy(BINTREEBASENODE *pRoot, DESTROYFUNC DestroyFunc)
{
	if (pRoot != NULL)
	{
		if (pRoot->pLeft != NULL)
		{
			BinTreeBaseNode_Destroy(pRoot->pLeft, DestroyFunc);
		}
		if (pRoot->pRight != NULL)
		{
			BinTreeBaseNode_Destroy(pRoot->pRight, DestroyFunc);
		}
		if (DestroyFunc != NULL && pRoot->pData != NULL)
		{
			(*DestroyFunc)(pRoot->pData);
		}
		free(pRoot);
	}
}

void BinTree_Destroy(BINTREE *pBinTree, DESTROYFUNC DestroyFunc)
{
	if (pBinTree == NULL)
	{
		return;
	}
	BinTreeBaseNode_Destroy(pBinTree->pRoot, DestroyFunc);
	free(pBinTree);
}

INT	BinTree_Add(BINTREE *pBinTree, void *pData, COMPAREFUNC CompareFunc)
{
	BINTREEBASENODE* pNode;
	BINTREEBASENODE* pNewNode;
	INT				 nRet = 0;

	if (pBinTree == NULL || pData == NULL || CompareFunc == NULL)
		return CAPI_FAILED;

	pNode = pBinTree->pRoot;

	while (pNode != NULL)
	{
		nRet = (*CompareFunc)(pNode->pData, pData);
		if (nRet < 0)
		{
			if (pNode->pRight != NULL)
			{
				pNode = pNode->pRight;
				continue;
			}
		}
		else
		{
			if (pNode->pLeft != NULL)
			{
				pNode = pNode->pLeft;
				continue;
			}
		}
		break;
	}

	pNewNode = (BINTREEBASENODE*)malloc(sizeof(BINTREEBASENODE));
	if (pNewNode == NULL)
	{
		return CAPI_FAILED;
	}
	pNewNode->pLeft = NULL;
	pNewNode->pRight = NULL;
	pNewNode->pData = NULL;

	if (pNode == NULL)
	{
		pBinTree->pRoot = pNewNode;
	}
	else
	{
		if (nRet < 0)
		{
			pNode->pRight = pNewNode;
		}
		else
		{
			pNode->pLeft = pNewNode;
		}
	}
	pBinTree->uNodeCount += 1;
	return CAPI_SUCCESS;
}

void* BinTree_Find(BINTREEBASENODE *pRoot, void *pData, COMPAREFUNC CompareFunc)
{
	BINTREEBASENODE*	pNode;

	pNode = pRoot;

	while (pNode != NULL)
	{
		INT nRet = (*CompareFunc)(pNode->pData, pData);
		if (nRet < 0)
		{
			pNode = pNode->pRight;
		}
		else if (nRet > 0)
		{
			pNode = pNode->pLeft;
		}
		else
		{
			return pNode->pData;
		}
	}
	return NULL;
}

BINTREEBASENODE* BinTree_FindNode(BINTREEBASENODE *pRoot, void *pData, COMPAREFUNC CompareFunc)
{
	BINTREEBASENODE* pNode;
	pNode = pRoot;

	while (pNode != NULL)
	{
		INT nRet = (*CompareFunc)(pNode->pData, pData);
		if (nRet < 0)
		{
			pNode = pNode->pRight;
		}
		else if (nRet > 0)
		{
			pNode = pNode->pLeft;
		}
		else
		{
			return pNode;
		}
	}
	return NULL;
}

INT BinTree_AddLeft(BINTREE *pBinTree, void *pTagNodeData, void *pData, COMPAREFUNC CompareFunc)
{
	BINTREEBASENODE* pNode;
	INT				 nRet;

	if (pBinTree == NULL || pTagNodeData == NULL || pData == NULL || CompareFunc == NULL)
	{
		return CAPI_FAILED;
	}

	pNode = pBinTree->pRoot;
	while (pNode != NULL)
	{
		nRet = (*CompareFunc)(pNode->pData, pTagNodeData);
		if (nRet < 0)
		{
			pNode = pNode->pRight;
		}
		else if (nRet > 0)
		{
			pNode = pNode->pLeft;
		}
		else
		{
			break;
		}
	}
	if (pNode != NULL)
	{
		BINTREEBASENODE* pNewNode;
		pNewNode = (BINTREEBASENODE*)malloc(sizeof(BINTREEBASENODE));
		if (pNewNode != NULL)
		{
			pNewNode->pData = pData;
			pNewNode->pLeft = pNode->pLeft;
			pNewNode->pRight = NULL;
			pNode->pLeft = pNewNode;
			return CAPI_SUCCESS;
		}
	}
	return CAPI_FAILED;
}

INT BinTree_AddRight(BINTREE *pBinTree, void *pTagNodeData, void *pData, COMPAREFUNC CompareFunc)
{
	BINTREEBASENODE* pNode;
	INT				 nRet;

	if (pBinTree == NULL || pTagNodeData == NULL || pData == NULL || CompareFunc == NULL)
	{
		return CAPI_FAILED;
	}

	pNode = pBinTree->pRoot;
	while (pNode != NULL)
	{
		nRet = (*CompareFunc)(pNode->pData, pTagNodeData);
		if (nRet < 0)
		{
			pNode = pNode->pRight;
		}
		else if (nRet > 0)
		{
			pNode = pNode->pLeft;
		}
		else
		{
			break;
		}
	}
	if (pNode != NULL)
	{
		BINTREEBASENODE* pNewNode;
		pNewNode = (BINTREEBASENODE*)malloc(sizeof(BINTREEBASENODE));
		if (pNewNode != NULL)
		{
			pNewNode->pData = pData;
			pNewNode->pLeft = NULL;
			pNewNode->pRight = pNode->pRight;
			pNode->pRight = pNewNode;
			return CAPI_SUCCESS;
		}
	}
	return CAPI_FAILED;
}

INT BinTree_Delete(BINTREE *pBinTree, void *pData, COMPAREFUNC CompareFunc, DESTROYFUNC DestroyFunc)
{
	BINTREEBASENODE* pNode;
	BINTREEBASENODE* pMaxNode;
	INT				 nRet;

	if (pBinTree == NULL || pBinTree->pRoot == NULL || pData == NULL || CompareFunc == NULL)
	{
		return CAPI_FAILED;
	}

	pNode = pBinTree->pRoot;
	while (pNode != NULL)
	{
		nRet = (*CompareFunc)(pNode->pData, pData);
		if (nRet < 0)
		{
			pNode = pNode->pRight;
		}
		else if (nRet > 0)
		{
			pNode = pNode->pLeft;
		}
		else
		{
			break;
		}
	}
	
	if (pNode == NULL)
	{
		return CAPI_FAILED;
	}

	if (pNode->pLeft != NULL && pNode->pRight != NULL)
	{
		pMaxNode = pNode->pLeft;
		while (pMaxNode->pRight != NULL)
		{
			pMaxNode = pMaxNode->pRight;
		}
		if (DestroyFunc != NULL && pNode->pData != NULL)
		{
			(*DestroyFunc)(pNode->pData);
		}
		pNode->pData = pMaxNode->pData;
		if (pMaxNode == pNode->pLeft)
		{
			pNode->pLeft = pMaxNode->pLeft;
			if (pMaxNode->pLeft != NULL)
			{
				pMaxNode->pLeft->pParent = pNode;
			}
		}
		else
		{
			pMaxNode->pParent->pRight = pMaxNode->pLeft;
			if(pMaxNode->pLeft != NULL)
			{
				pMaxNode->pLeft->pParent = pMaxNode->pParent;
			}
		}
		free(pMaxNode);

		return CAPI_SUCCESS;
	}

	if (pNode->pLeft != NULL)
	{
		pMaxNode = pNode->pLeft;
	}
	else
	{
		pMaxNode = pNode->pRight;
	}

	if (pNode == pBinTree->pRoot)
	{
		pBinTree->pRoot = pMaxNode;
		if (pMaxNode != NULL)
		{
			pMaxNode->pParent = NULL;
		}
	}
	else
	{
		if (pNode->pParent->pLeft == pNode)
		{
			pNode->pParent->pLeft = pMaxNode;
		}
		else
		{
			pNode->pParent->pRight = pMaxNode;
		}
		if (pMaxNode != NULL)
		{
			pMaxNode->pParent = pNode->pParent;
		}
	}
	if (DestroyFunc != NULL && pNode->pData != NULL)
	{
		(*DestroyFunc)(pNode->pData);
	}
	free(pNode);
	return CAPI_SUCCESS;
}

void BinTree_RotateLeft(BINTREEBASENODE *pANode, BINTREEBASENODE **ppRoot)
{
	BINTREEBASENODE*	pBNode;
	pBNode = pANode->pRight;

	pANode->pRight = pBNode->pLeft;
	if (pBNode->pLeft != NULL)
	{
		pBNode->pLeft->pParent = pANode;
	}

	pBNode->pParent = pANode->pParent;
	if (pANode == *ppRoot)
	{
		*ppRoot = pBNode;
	}
	else if (pANode == pANode->pParent->pLeft)
	{
		pANode->pParent->pLeft = pBNode;
	}
	else
	{
		pANode->pParent->pRight = pBNode;
	}
	pBNode->pLeft = pANode;
	pANode->pParent = pBNode;
}



















