/************************************************************************/
/* SingleList.cpp
*/
/************************************************************************/

#include "SingleList.h"

SINGLELIST* SingleList_Create(void)
{
	SINGLELIST*	pSingleList;

	pSingleList = (SINGLELIST*)malloc(sizeof(SINGLELIST));
	if (pSingleList != NULL)
	{
		pSingleList->pCur = NULL;
		pSingleList->pHead = NULL;
		pSingleList->pTail = NULL;
		pSingleList->uCount = 0;
	}
	return pSingleList;
}

void SingleList_Destroy(SINGLELIST* pSingleList, DESTROYFUNC DestroyFunc)
{
	SINGLENODE*	pNode;
	if (pSingleList)
	{
		pNode = pSingleList->pHead;
		while (pNode != NULL)
		{
			SINGLENODE* pDelNode;
			pDelNode = pNode;
			pNode = pNode->pNext;

			if (DestroyFunc != NULL && pDelNode->pData != NULL)
			{
				(*DestroyFunc)(pDelNode->pData);
			}
			free(pDelNode);
		}
		free(pSingleList);
	}
}

INT SingleList_InSertHead(SINGLELIST* pSingleList, void* pData)
{
	SINGLENODE*	pNode;

	if (pSingleList == NULL || pData == NULL)
	{
		return CAPI_FAILED;
	}

	pNode = (SINGLENODE*)malloc(sizeof(SINGLENODE));
	if (pNode == NULL)
	{
		return CAPI_FAILED;
	}
	pNode->pData = pData;

	pNode->pNext = pSingleList->pHead;
	pSingleList->pHead = pNode;

	if (pSingleList->pTail == NULL)
	{
		pSingleList->pTail = pNode;
	}
	pSingleList->uCount++;
	
	return CAPI_SUCCESS;
}

INT Single_InsertTail(SINGLELIST* pSingleList, void* pData)
{
	SINGLENODE* pNode;

	if (pSingleList == NULL || pData == NULL)
	{
		return CAPI_FAILED;
	}

	pNode = (SINGLENODE*)malloc(sizeof(SINGLENODE));
	if (pNode == NULL)
	{
		return CAPI_FAILED;
	}
	pNode->pData = pData;
	pNode->pNext = NULL;

	if (pSingleList->pTail == NULL)
	{
		pSingleList->pTail = pNode;
		pSingleList->pHead = pNode;
	}
	else
	{
		pSingleList->pTail->pNext = pNode;
		pSingleList->pTail = pNode;
	}
	pSingleList->uCount++;

	return CAPI_SUCCESS;
}

void* SingleList_PopHead(SINGLELIST* pSingleList)
{
	SINGLENODE* pPopNode;
	void*		pPopData;

	if (pSingleList == NULL || pSingleList->pHead == NULL)
	{
		return NULL;
	}
	pPopNode = pSingleList->pHead;
	pPopData = pPopNode->pData;

	if (pSingleList->pCur == pSingleList->pHead)
	{
		pSingleList->pCur = pSingleList->pHead->pNext;
	}
	pSingleList->pHead = pSingleList->pHead->pNext;
	pSingleList->uCount--;

	if (pSingleList->uCount == 0)
	{
		pSingleList->pTail = NULL;
	}
	free(pPopNode);

	return pPopData;
}

void* SingleList_PopTail(SINGLELIST* pSingleList)
{
	SINGLENODE* pPopNode;
	SINGLENODE*	pTailPrevNode;
	void*		pPopData;

	if (pSingleList == NULL || pSingleList->pHead == NULL)
	{
		return NULL;
	}

	pPopNode = pSingleList->pTail;
	pPopData = pPopNode->pData;

	pTailPrevNode = pSingleList->pHead;

	if (pSingleList->pTail == pSingleList->pHead)
	{
		pTailPrevNode = NULL;
		pSingleList->pHead = NULL;
	}
	else
	{
		while (pTailPrevNode != NULL)
		{
			if (pTailPrevNode->pNext == pSingleList->pTail)
			{
				break;
			}
			pTailPrevNode = pTailPrevNode->pNext;
		}
	}
	if (pSingleList->pCur == pSingleList->pTail)
	{
		pSingleList->pCur = pTailPrevNode;
	}
	pSingleList->pTail = pTailPrevNode;

	if (pTailPrevNode != NULL)
	{
		pTailPrevNode->pNext = NULL;
	}
	pSingleList->uCount--;

	free(pPopNode);

	return pPopData;
}

INT SingleList_Delete(SINGLELIST* pSingleList, void* pMatchData,
	COMPAREFUNC CompareFunc, DESTROYFUNC DestroyFunc)
{
	SINGLENODE* pNode;
	SINGLENODE* pPrevNode;

	if (pSingleList == NULL || CompareFunc == NULL)
	{
		return CAPI_FAILED;
	}

	pNode = pSingleList->pHead;
	pPrevNode = pNode;

	while (pNode != NULL)
	{
		if ((*CompareFunc)(pNode->pData, pMatchData) == 0)
		{
			if (pPrevNode == pNode)
			{
				pSingleList->pHead = pNode->pNext;
				if (pSingleList->pTail == pNode)
				{
					pSingleList->pTail = NULL;
					pSingleList->pCur = NULL;
				}
			}
			else
			{
				pPrevNode->pNext = pNode->pNext;
				if (pSingleList->pTail == pNode)
				{
					pSingleList->pTail = pPrevNode;
				}
				if (pSingleList->pCur == pNode)
				{
					pSingleList->pCur = pNode->pNext;
				}
			}
			if (DestroyFunc != NULL && pNode->pData != NULL)
			{
				(*DestroyFunc)(pNode->pData);
			}
			free(pNode);
			break;
		}
		pPrevNode = pNode;
		pNode = pNode->pNext;
	}
	return CAPI_SUCCESS;
}

void* SingleList_GetAt(SINGLELIST* pSingleList, UINT uIndex)
{
	UINT	i;
	SINGLENODE* pNode;

	if (pSingleList == NULL || pSingleList->uCount >= uIndex)
	{
		return NULL;
	}

	pNode = pSingleList->pHead;
	for (i = 0; i < uIndex; i++)
	{
		pNode = pNode->pNext;
	}
	return pNode->pData;
}

UINT SingleList_GetCount(SINGLELIST* pSingleList)
{
	if (pSingleList == NULL)
	{
		return 0;
	}
	return pSingleList->uCount;
}

void* SingleList_GetHead(SINGLELIST* pSingleList)
{
	if (pSingleList == NULL)
	{
		return NULL;
	}
	if (pSingleList->pHead == NULL)
	{
		return NULL;
	}
	return pSingleList->pHead->pData;
}

void* SingleList_GetCursor(SINGLELIST* pSingleList)
{
	if (pSingleList == NULL)
	{
		return NULL;
	}
	if (pSingleList == NULL)
	{
		return NULL;
	}
	return pSingleList->pCur->pData;
}

void* SingleList_GetTail(SINGLELIST* pSingleList)
{
	if (pSingleList == NULL)
	{
		return NULL;
	}
	if (pSingleList->pTail != NULL)
	{
		return pSingleList->pTail->pData;
	}
	else
	{
		return NULL;
	}
}

void SingleList_EnumBegin(SINGLELIST* pSingleList)
{
	pSingleList->pCur = pSingleList->pHead;
	return;
}

void* SingleList_EnumNext(SINGLELIST* pSingleList)
{
	SINGLENODE* pCur;

	pCur = pSingleList->pCur;

	if (pCur == NULL)
	{
		pSingleList->pCur = pCur->pNext;
		return pCur->pData;
	}
	return NULL;
}

INT SingleList_Traverse(SINGLELIST* pSingleList, TRAVERSEFUNC TraverseFunc)
{
	SINGLENODE* pNode;
	if (pSingleList == NULL || TraverseFunc == NULL)
	{
		return CAPI_FAILED;
	}
	pNode = pSingleList->pHead;

	while (pNode != NULL)
	{
		(*TraverseFunc)(pNode->pData);
		pNode = pNode->pNext;
	}
	return CAPI_SUCCESS;
}










