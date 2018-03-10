#ifndef __HASHLIST_H__
#define __HASHLIST_H__

#define MINIUM_BUCKET_COUNT		32

#include "Global.h"

typedef struct HASHLISTNODE_st
{
	struct HASHLISTNODE_st* pListNext;
	struct HASHLISTNODE_st* pListPrev;
	struct HASHLISTNODE_st* pBucketNext;
	void*		pData;
}HASHLISTNODE;

typedef struct HASHLIST_st
{
	HASHLISTNODE**	ppBuckets;
	UINT			uBucketCount;
	HASHLISTNODE*	pHead;
	HASHLISTNODE*	pTail;
	UINT			uNodeCount;
}HASHLIST;



HASHLIST *HashList_Create(UINT uBucketCount);

void HashList_Destroy(HASHLIST *pHashList,
	DESTROYFUNC DestroyFunc);

INT HashList_InsertHead(HASHLIST *pHashList, void *pData, HASHFUNC HashFunc);

INT HashList_Delete(HASHLIST *pHashList,
	void           *pData,
	HASHFUNC        HashFunc,
	COMPAREFUNC     HashCompareFunc,
	DESTROYFUNC     DestroyFunc);


HASHLISTNODE *HashList_FindNode(HASHLIST *pHashList,
	void *pData,
	HASHFUNC HashFunc,
	COMPAREFUNC CompareFunc);

void *HashList_FindData(HASHLIST *pHashList,
	void *pData,
	HASHFUNC HashFunc,
	COMPAREFUNC CompareFunc);

INT HashList_InsertSort(HASHLIST *pHashList, COMPAREFUNC CompareFunc);


UINT        HashStr(void *str, UINT str_len, UINT numBuckets);
UINT        HashStrCompare(void *str1, UINT str1_len, void *str2, UINT str2_len);
void        HashFree(void *pData, UINT uDataLen);











#endif

