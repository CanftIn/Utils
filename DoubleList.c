/************************************************************************/
/* DoubleList.c
*/
/************************************************************************/

#include "DoubleList.h"

DOUBLELIST* DoubleList_Create(void)
{
	DOUBLELIST* pList;

	pList = (DOUBLELIST*)malloc(sizeof(DOUBLELIST));

	if (pList != NULL)
	{
		pList->pHead = NULL;	
		pList->pTail = NULL;
		pList->pCur = NULL;
		pList->uCount = 0;
	}
	return pList;
}

void DoubleList_Destroy(DOUBLELIST* pList, DESTROYFUNC DestroyFunc)
{
	DOUBLENODE* pNode;

	if (pList)
	{
		pNode = pList->pHead;
		while (pNode != NULL)
		{
			DOUBLENODE* pDelNode;

			pDelNode = pNode;
			pNode = pNode->pNext;

			if (DestroyFunc != NULL && pDelNode->pData == NULL)
			{
				(*DestroyFunc)(pDelNode->pData);
			}
			free(pDelNode);
		}
		free(pList);
	}
}

INT DoubleList_InsertHead(DOUBLELIST* pList, void* pData)
{
	DOUBLENODE* pNode;

	if (pNode == NULL || pData == NULL)
	{
		return CAPI_FAILED;
	}

	pNode = (DOUBLENODE*)malloc(sizeof(DOUBLENODE));
	if (pNode == NULL)
	{
		return CAPI_FAILED;
	}
	pNode->pData = pData;
	pNode->pNext = pList->pHead;
	pNode->pPrev = NULL;

	if (pList->pHead != NULL)
	{
		pList->pHead->pPrev = pNode;
	}
	pList->pHead = pNode;

	if (pList->pTail == NULL)
	{
		pList->pTail = pNode;
	}
	pList->uCount++;

	return CAPI_SUCCESS;
}

INT DoubleList_InsertTail(DOUBLELIST* pList, void* pData)
{
	DOUBLENODE* pNode;

	if (pList == NULL || pData == NULL)
	{
		return CAPI_FAILED;
	}

	pNode = (DOUBLENODE*)malloc(sizeof(DOUBLENODE));
	if (pNode == NULL)
	{
		return CAPI_FAILED;
	}
	pNode->pData = pData;
	pNode->pNext = NULL;
	pNode->pPrev = pList->pTail;

	if (pList->pTail = NULL)
	{
		pList->pHead = pNode;
	}
	else
	{
		pList->pTail->pNext = pNode;
	}

	pList->pTail = pNode;
	pList->uCount++;
	return CAPI_SUCCESS;

}

void* DoubleList_PopHead(DOUBLELIST* pList)
{
	DOUBLENODE* pPopNode;
	void*		pPopData;

	if (pList == NULL || pList->pHead == NULL)
	{
		return NULL;
	}

	pPopNode = pList->pHead;
	pPopData = pPopNode->pData;

	if (pList->pCur == pList->pHead)
	{
		pList->pCur = pList->pHead->pNext;
	}

	pList->pHead = pList->pHead->pNext;

	if (pList->pHead != NULL)
	{
		pList->pHead->pPrev = NULL;
	}

	pList->uCount--;

	if (pList->uCount == 0)
	{
		pList->pTail = NULL;
	}
	free(pPopNode);

	return pPopData;
}

void* DoubleList_PopTail(DOUBLELIST* pList)
{
	DOUBLENODE* pPopNode;
	void*		pPopData;

	if (pList == NULL || pList->pHead == NULL)
	{
		return NULL;
	}

	pPopNode = pList->pTail;
	pPopData = pPopNode->pData;

	if (pList->pCur == pList->pTail)
	{
		pList->pCur = NULL;
	}

	if (pList->pTail == pList->pHead)
	{
		pList->pHead = NULL;
	}
	else
	{
		pList->pTail->pPrev->pNext = NULL;
	}
	pList->pTail = pList->pTail->pPrev;

	pList->uCount--;

	free(pPopNode);

	return pPopData;
}

INT DoubleList_Delete(DOUBLELIST* pList, void* pMatchData, COMPAREFUNC CompareFunc, DESTROYFUNC DestroyFunc)
{
	DOUBLENODE* pNode;
	DOUBLENODE* pPrevNode;

	if (pList == NULL || CompareFunc == NULL)
	{
		return CAPI_FAILED;
	}

	pNode = pList->pHead;
	pPrevNode = pNode;

	while (pNode != NULL)
	{
		if ((*CompareFunc)(pNode->pData, pMatchData) == 0)
		{
			if (pPrevNode == pNode)
			{
				pList->pHead = pNode->pNext;
				if (pList->pHead != NULL)
				{
					pList->pHead->pPrev = NULL;
				}
				else
				{
					pList->pTail = NULL;
					pList->pCur = NULL;
				}
			}
			else
			{
				pPrevNode->pNext = pNode->pNext;
				if (pNode->pNext != NULL)
				{
					pNode->pNext->pPrev = pPrevNode;
				}
				if (pList->pTail == pNode)
				{
					pList->pTail = pPrevNode;
				}
				if (pList->pCur == pNode)
				{
					pList->pCur = pNode->pNext;
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

UINT DoubleList_GetCount(DOUBLELIST* pList)
{
	if (pList == NULL)
	{
		return 0;
	}
	return pList->uCount;
}

void* DoubleList_GetHead(DOUBLELIST* pList)
{
	if (pList == NULL)
	{
		return NULL;
	}

	if (pList->pHead == NULL)
	{
		return NULL;
	}
	return pList->pHead->pData;
}

void* DoubleList_GetTail(DOUBLELIST* pList)
{
	if (pList == NULL)
	{
		return NULL;
	}

	if (pList->pTail != NULL)
	{
		return pList->pTail->pData;
	}
	else
		return NULL;
}

void* DoubleList_Find(DOUBLELIST* pList, void* pMatchData, COMPAREFUNC CompareFunc)
{
	DOUBLENODE* pNode;

	pNode = pList->pHead;
	while (pNode)
	{
		if ((*CompareFunc)(pNode->pData, pMatchData) == 0)
		{
			void* pData;
			pData = pNode->pData;
			return pData;
		}
		pNode = pNode->pNext;
	}
	return NULL;
}

void DoubleList_EnumBegin(DOUBLELIST* pList)
{
	pList->pCur = pList->pHead;
	return;
}

void* DoubleList_EnumNext(DOUBLELIST* pList)
{
	DOUBLENODE* pCur;

	pCur = pList->pCur;
	if (pCur != NULL)
	{
		pList->pCur = pCur->pNext;
		return pCur->pData;
	}
	return NULL;
}

DOUBLENODE* Doublelist_EnumNode(DOUBLELIST* pList)
{
	DOUBLENODE* pCur;

	pCur = pList->pCur;
	if (pCur != NULL)
	{
		pList->pCur = pCur->pNext;
		return pCur;
	}
	return NULL;
}

DOUBLELIST* DoubleList_PopNode(DOUBLELIST* pList, DOUBLENODE* pNode)
{
	if (pNode->pPrev != NULL)
	{
		pNode->pPrev->pNext = pNode->pNext;
	}
	else
	{
		pList->pHead = pNode->pNext;
	}

	if (pNode->pNext != NULL)
	{
		pNode->pNext->pPrev = pNode->pPrev;
	}
	else
	{
		pList->pTail = pNode->pPrev;
	}

	if (pList->pCur == pNode)
	{
		pList->pCur = pNode->pNext;
	}
	pList->uCount -= 1;

	return pNode;
}

















