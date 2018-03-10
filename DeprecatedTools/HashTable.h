#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "Global.h"

typedef struct HASHTABLE
{
	SINGLENODE** ppBucket;
	UINT		 uBucketCount;
	UINT		 uNodeCount;

	UINT		 uCurBucketNo;
	SINGLENODE*  pCurEntry;
}HASHTABLE;

HASHTABLE * HashTable_Create(UINT uBucketCount);

void    HashTable_Destroy(HASHTABLE *pTable,
	DESTROYFUNC DestroyFunc);

INT     HashTable_Insert(HASHTABLE *pTable,
	void *pData,
	HASHFUNC HashFunc);

void *  HashTable_Find(HASHTABLE *pTable,
	void *pData,
	HASHFUNC HashFunc,
	COMPAREFUNC CompareFunc);

INT     HashTable_Delete(HASHTABLE *pTable,
	void *pData,
	HASHFUNC HashFunc,
	COMPAREFUNC CompareFunc,
	DESTROYFUNC DataDestroyFunc);

UINT    HashTable_GetNodeCount(HASHTABLE *pTable);

void    HashTable_EnumBegin(HASHTABLE *pTable);
void *  HashTable_EnumNext(HASHTABLE *pTable);


#endif