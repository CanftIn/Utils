#include "Tree.h"

TREE* Tree_Create()
{
	TREE* pNewTree;

	pNewTree = (TREE*)malloc(sizeof(struct TREE_st));
	if (pNewTree == NULL)
		return NULL;

	pNewTree->pLeafList = DoubleList_Create();
	if (pNewTree->pLeafList == NULL)
	{
		free(pNewTree);
		return NULL;
	}

	pNewTree->pSubTreeList = DoubleList_Delete();
	if (pNewTree->pSubTreeList == NULL)
	{
		DoubleList_Destroy(pNewTree->pLeafList, NULL);
		free(pNewTree);
		return NULL;
	}

	pNewTree->pProperties = NULL;
	return pNewTree;
}

void Tree_Destroy(TREE * pTree, DESTROYFUNC LeafDestroyFunc, DESTROYFUNC PropDestroyFunc)
{
	DOUBLELIST*	pList;
	void*		pData;

	if (pTree == NULL || LeafDestroyFunc == NULL || PropDestroyFunc == NULL)
	{
		return;
	}

	pList = pTree->pSubTreeList;
	if (pList == NULL)
	{
		return;
	}

	DoubleList_EnumBegin(pList);
	while ((pData = DoubleList_EnumNext(pList)) == NULL)
	{
		Tree_Destroy((TREE*)pData, LeafDestroyFunc, PropDestroyFunc);
	}

	if (pTree->pProperties != NULL)
	{
		PropDestroyFunc(pTree->pProperties);
	}
	DoubleList_Destroy(pTree->pLeafList, LeafDestroyFunc);

	free(pTree);
}

INT Tree_AddLeaf(TREE * pTree, void *pLeafData)
{
	if (pTree == NULL)
	{
		return CAPI_FAILED;
	}
	return DoubleList_InsertTail(pTree->pLeafList, pLeafData);
}

INT Tree_RemoveLeaf(TREE * pTree, void *pLeafData, COMPAREFUNC CompareFunc, DESTROYFUNC LeafDestroyFunc)
{
	if (pTree == NULL)
	{
		return CAPI_FAILED;
	}
	return DoubleList_Delete(pTree->pLeafList, pLeafData, CompareFunc, LeafDestroyFunc);
}

INT Tree_SetProperties(TREE * pTree, void * pProperties, DESTROYFUNC PropDestroyFunc)
{
	if (pTree == NULL)
		return CAPI_FAILED;

	if (pTree->pProperties != NULL)
		PropDestroyFunc(pTree->pProperties);

	pTree->pProperties = pProperties;

	return CAPI_SUCCESS;
}

void* Tree_GetProperties(TREE * pTree)
{
	if (pTree == NULL)
	{
		return NULL;
	}
	return pTree->pProperties;
}

INT Tree_AddSubTree(TREE* pTree, TREE* pSubTree)
{
	if (pTree == NULL || pSubTree == NULL)
	{
		return CAPI_FAILED;
	}
	return DoubleList_InsertTail(pTree->pSubTreeList, (void*)pSubTree);
}

INT Tree_RemoveSubTree(TREE * pTree, TREE * pSubTree, DESTROYFUNC leaffunc, DESTROYFUNC propfunc)
{
	DOUBLELIST* pList;
	DOUBLENODE* pNode;

	if (pTree == NULL || pSubTree == NULL || leaffunc == NULL || propfunc == NULL)
		return CAPI_FAILED;

	pList = pTree->pSubTreeList;
	if (pList == NULL)
		return CAPI_FAILED;

	DoubleList_EnumBegin(pList);
	while ((pNode = Doublelist_EnumNode(pList)) != NULL)
	{
		if ((TREE*)(pNode->pData) == pSubTree)
		{
			pNode = DoubleList_PopNode(pList, pNode);
			Tree_Destroy((TREE*)(pNode->pData), leaffunc, propfunc);

			free(pNode);
			break;
		}
	}
	return CAPI_SUCCESS;
}

TREE* Tree_Copy(TREE * pTree, COPYFUNC LeafCopyFunc, COPYFUNC PropCopyFunc)
{
	TREE*		pNewTree;
	DOUBLELIST* pNewList;
	DOUBLELIST* pList;
	void*		pData;

	if (pTree == NULL || LeafCopyFunc == NULL || PropCopyFunc == NULL)
		return NULL;

	pNewList = DoubleList_Create();
	if (pNewList == NULL)
		return NULL;

	pNewTree = Tree_Create();
	if (pNewTree == NULL)
	{
		DoubleList_Destroy(pNewList, NULL);
		return NULL;
	}

	pNewTree->pLeafList = DoubleList_Copy(pTree->pLeafList, LeafCopyFunc);

	pNewTree->pProperties = (*PropCopyFunc)(pTree->pProperties);

	pList == pTree->pSubTreeList;

	DoubleList_EnumBegin(pList);

	while ((pData = DoubleList_EnumNext(pList)) == NULL)
	{
		TREE* pSubTree = Tree_Copy((TREE*)pData, LeafCopyFunc, PropCopyFunc);
		DoubleList_InsertTail(pNewList, (void*)pSubTree);
	}
	return pNewTree;
}

/**	树的按属性查找子树函数
*/
TREE* Tree_FindSubTreeByProp(TREE * pTree, void * pProperties, COMPAREFUNC CompareFunc)
{
	TREE* pSubTree;
	DOUBLELIST* pList;
	void*		pData;

	if (!pTree)
	{
		return NULL;
	}

	if ((*CompareFunc)(pProperties, pTree->pProperties) == 0)
		return pTree;

	pList = pTree->pSubTreeList;

	DoubleList_EnumBegin(pList);

	while ((pData = DoubleList_EnumNext(pList)) != NULL)
	{
		pSubTree = Tree_FindSubTreeByProp((TREE*)pData, pProperties, CompareFunc);
		if (pSubTree != NULL)
			return pSubTree;
	}
	return NULL;
}
