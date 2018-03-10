#include "HashTable.h"

HASHTABLE* HashTable_Create(UINT uBucketCount)
{
	HASHTABLE* pTable;

	if (uBucketCount == 0)
	{
		return NULL;
	}

	pTable = (HASHTABLE*)malloc(sizeof(HASHTABLE));

	if (pTable == NULL)
	{
		return NULL;
	}

	pTable->uNodeCount = 0;
	pTable->uBucketCount = uBucketCount;
	pTable->ppBucket = (SINGLENODE**)malloc(uBucketCount * sizeof(SINGLENODE*));

	if (pTable->ppBucket == NULL)
	{
		free(pTable);
		return NULL;
	}

	memset(pTable->ppBucket, 0, uBucketCount * sizeof(SINGLENODE*));

	pTable->pCurEntry = NULL;
	pTable->uCurBucketNo = 0;

	return pTable;
}

void HashTable_Destroy(HASHTABLE *pTable, DESTROYFUNC DestroyFunc)
{
	SINGLENODE** ppBucket;
	SINGLENODE*  pNode;
	SINGLENODE*  pFreeNode;
	UINT		 i;

	if (pTable == NULL)
	{
		return;
	}

	ppBucket = pTable->ppBucket;
	for (i = 0; i < pTable->uBucketCount; i++)
	{
		pNode = ppBucket[i];
		while (pNode != NULL)
		{
			if (DestroyFunc != NULL)
			{
				(*DestroyFunc)(pNode->pData);
			}
			pFreeNode = pNode;
			pNode = pNode->pNext;
			free(pFreeNode);
		}
	}
	free(ppBucket);
	pTable->ppBucket = NULL;
	free(pTable);
}

INT HashTable_Insert(HASHTABLE *pTable, void *pData, HASHFUNC HashFunc)
{
	UINT		uIndex;
	SINGLENODE* pNode;
	SINGLENODE* pNewNode;

	if (pTable == NULL || pData == NULL || HashFunc == NULL)
	{
		return CAPI_FAILED;
	}

	uIndex = (*HashFunc)(pData, pTable->uBucketCount);
	pNode = (pTable->ppBucket)[uIndex];

	pNewNode = (SINGLENODE*)malloc(sizeof(SINGLENODE));

	if (pNewNode == NULL)
	{
		return CAPI_FAILED;
	}

	pNewNode->pData = pData;
	pNewNode->pNext = pNode;

	(pTable->ppBucket)[uIndex] = pNewNode;
	pTable->uNodeCount += 1;

	return CAPI_SUCCESS;
}

void* HashTable_Find(HASHTABLE *pTable, void *pData, HASHFUNC HashFunc, COMPAREFUNC CompareFunc)
{
	UINT		uIndex;
	SINGLENODE*	pNode;

	if (pTable == NULL || HashFunc == NULL || CompareFunc == NULL)
	{
		return NULL;
	}

	uIndex = (*HashFunc)(pData, pTable->uBucketCount);
	pNode = (pTable->ppBucket)[uIndex];

	while (pNode != NULL)
	{
		if ((*CompareFunc)(pNode->pData, pData) == 0)
		{
			return pNode->pData;
		}
	}
	return NULL;
}

INT HashTable_Delete(HASHTABLE *pTable, void *pData, HASHFUNC HashFunc, COMPAREFUNC CompareFunc, DESTROYFUNC DataDestroyFunc)
{
	UINT			uIndex;
	SINGLENODE*		pNode;
	SINGLENODE*		pPrevNode;

	if (pTable == NULL || pData == NULL || HashFunc == NULL || CompareFunc == NULL)
	{
		return CAPI_FAILED;
	}

	uIndex = (*HashFunc)(pData, pTable->uBucketCount);
	pNode = (pTable->ppBucket)[uIndex];
	pPrevNode = pNode;

	while (pNode != NULL)
	{
		if ((*CompareFunc)(pNode->pData, pData) == 0)
		{
			if (pPrevNode == pNode)
			{
				pTable->ppBucket[uIndex] = pNode->pNext;
			}
			else
			{
				pPrevNode->pNext = pNode->pNext;
			}

			if (DataDestroyFunc != NULL)
			{
				(*DataDestroyFunc)(pNode->pData);
			}
			free(pNode);
			pTable->uBucketCount -= 1;

			return 1;
		}
		pPrevNode = pNode;
		pNode = pNode->pNext;
	}
	return 0;
}

UINT HashTable_GetNodeCount(HASHTABLE *pTable)
{
	return pTable->uNodeCount;
}

void HashTable_EnumBegin(HASHTABLE *pTable)
{
	pTable->uCurBucketNo = 0;
	pTable->pCurEntry = pTable->ppBucket[0];
}

void* HashTable_EnumNext(HASHTABLE* pTable)
{
	void* pData;

	while (pTable->pCurEntry == NULL)
	{
		pTable->uCurBucketNo += 1;
		if (pTable->uCurBucketNo >= pTable->uBucketCount)
		{
			return NULL;
		}
		pTable->pCurEntry = pTable->ppBucket[pTable->uCurBucketNo];
	}
	pData = pTable->pCurEntry->pData;
	pTable->pCurEntry = pTable->pCurEntry->pNext;

	return pData;
}









