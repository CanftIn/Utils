#include "HashList.h"

HASHLIST* HashList_Create(UINT uBucketCount)
{
	HASHLIST*	pHashList;

	if (uBucketCount < MINIUM_BUCKET_COUNT)
	{
		uBucketCount = MINIUM_BUCKET_COUNT;
	}

	pHashList = (HASHLIST*)malloc(sizeof(HASHLIST));

	if (pHashList != NULL)
	{
		pHashList->ppBuckets = (HASHLISTNODE**)malloc(uBucketCount * sizeof(HASHLISTNODE*));
		if (pHashList->ppBuckets == NULL)
		{
			free(pHashList);
			return NULL;
		}
		memset((void*)pHashList->ppBuckets, 0, uBucketCount * sizeof(HASHLISTNODE*));

		pHashList->pHead = NULL;
		pHashList->pTail = NULL;
		pHashList->uBucketCount = uBucketCount;
		pHashList->uNodeCount = 0;
	}
	return pHashList;
}

void HashList_Destroy(HASHLIST *pHashList, DESTROYFUNC DestroyFunc)
{
	UINT uIndex;
	if (pHashList == NULL)
	{
		return;
	}
	for (uIndex = 0; uIndex < pHashList->uBucketCount; uIndex++)
	{
		HASHLISTNODE*	pNode;
		pNode = pHashList->ppBuckets[uIndex];
		while (pNode != NULL)
		{
			HASHLISTNODE* pNodeToFree;
			pNodeToFree = pNode;
			pNode = pNode->pBucketNext;
			if (DestroyFunc != NULL && pNodeToFree->pData != NULL)
			{
				(*DestroyFunc)(pNodeToFree->pData);
			}
			free(pNodeToFree);
		}
	}
	free(pHashList->ppBuckets);
	free(pHashList);
	return;
}

INT HashList_InsertHead(HASHLIST *pHashList, void *pData, HASHFUNC HashFunc)
{
	HASHLISTNODE*	pNode;
	UINT			uBucketIndex;

	if (pHashList == NULL || pData == NULL)
	{
		return CAPI_FAILED;
	}
	
	pNode = (HASHLISTNODE*)malloc(sizeof(HASHLISTNODE));
	if (pNode == NULL)
		return CAPI_FAILED;

	pNode->pData = pData;
	pNode->pBucketNext = NULL;
	pNode->pListPrev = NULL;
	pNode->pListNext = pHashList->pHead;

	uBucketIndex = (*HashFunc)(pData, pHashList->uBucketCount);
	if (pHashList->ppBuckets[uBucketIndex] == NULL)
	{
		pHashList->ppBuckets[uBucketIndex] = pNode;
	}
	else
	{
		HASHLISTNODE*	pTempNode;
		pTempNode = pHashList->ppBuckets[uBucketIndex];
		while (pTempNode->pBucketNext != NULL)
		{
			pTempNode = pTempNode->pBucketNext;
		}
		pTempNode->pBucketNext = pNode;
	}

	if (pHashList->pHead == NULL)
	{
		pHashList->pHead = pNode;
		pHashList->pTail = pNode;
	}
	else
	{
		pNode->pListNext = pHashList->pHead;
		pHashList->pHead->pListPrev = pNode;
		pHashList->pHead = pNode;
	}

	pHashList->uNodeCount += 1;
	return CAPI_SUCCESS;
}

INT	HashList_Delete(HASHLIST *pHashList, void *pData, HASHFUNC HashFunc, COMPAREFUNC HashCompareFunc, DESTROYFUNC DestroyFunc)
{
	HASHLISTNODE*	pNode;
	HASHLISTNODE*	pPrevNode;
	UINT			uIndex;

	if (pHashList == NULL || HashFunc == NULL || HashCompareFunc == NULL)
	{
		return CAPI_FAILED;
	}

	uIndex = (*HashFunc)(pData, pHashList->uBucketCount);
	pNode = pHashList->ppBuckets[uIndex];
	pPrevNode = NULL;

	while (pNode != NULL)
	{
		if ((*HashCompareFunc)(pNode->pData, pData) == 0)
		{
			if (pPrevNode == NULL)
			{
				pHashList->ppBuckets[uIndex] = pNode->pBucketNext;
			}
			else
			{
				pPrevNode->pBucketNext = pNode->pBucketNext;
			}

			if (pNode->pListPrev != NULL)
			{
				pNode->pListPrev->pListNext = pNode->pListNext;
			}
			else
			{
				pHashList->pHead = pNode->pListNext;
			}

			if (pNode->pListNext != NULL)
			{
				pNode->pListNext->pListPrev = pNode->pListPrev;
			}
			else 
			{
				pHashList->pTail = pNode;
			}

			if (pNode->pData != NULL && DestroyFunc != NULL)
			{
				(*DestroyFunc)(pNode->pData);
			}
			free(pNode);

			pHashList->uNodeCount -= 1;
			return CAPI_SUCCESS;
		}
		pPrevNode = pNode;
		pNode = pNode->pBucketNext;
	}

	return CAPI_FAILED;
}

HASHLISTNODE* HashList_FindNode(HASHLIST *pHashList, void *pData, HASHFUNC HashFunc, COMPAREFUNC CompareFunc)
{
	HASHLISTNODE*	pNode;
	UINT			uIndex;

	if (pHashList == NULL || HashFunc == NULL || CompareFunc == NULL)
	{
		return NULL;
	}

	uIndex = (*HashFunc)(pData, pHashList->uBucketCount);
	pNode = pHashList->ppBuckets[uIndex];

	while (pNode != NULL)
	{
		if ((*CompareFunc)(pNode->pData, pData) == 0)
		{
			return pNode;
		}
		pNode = pNode->pBucketNext;
	}
	return NULL;
}

void* HashList_FindData(HASHLIST *pHashList, void *pData, HASHFUNC HashFunc, COMPAREFUNC CompareFunc)
{
	HASHLISTNODE* pNode;
	UINT		  uIndex;

	if (pHashList == NULL || HashFunc == NULL || CompareFunc == NULL)
	{
		return NULL;
	}

	uIndex = (*HashFunc)(pData, pHashList->uBucketCount);
	pNode = pHashList->ppBuckets[uIndex];

	while (pNode != NULL)
	{
		if ((*CompareFunc)(pNode->pData, pData) == 0)
		{
			return pNode->pData;
		}
		pNode = pNode->pBucketNext;
	}
	return NULL;
}

//INT HashList_InsertSort(HASHLIST *pHashList, COMPAREFUNC CompareFunc);










