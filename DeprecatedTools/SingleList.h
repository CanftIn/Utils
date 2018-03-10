/************************************************************************/
/* SingleList.h
*/
/************************************************************************/

#ifndef __SINGLELIST_H__
#define __SINGLELIST_H__

#include "Global.h"

typedef struct SINGLELIST_st
{
	SINGLENODE* pHead;		//头节点
	SINGLENODE* pTail;		//尾节点
	SINGLENODE* pCur;		//当前节点
	UINT		uCount;		//节点个数
}SINGLELIST, *PSINGLELIST;

typedef struct SINGLELIST_ENUM_st
{
	SINGLENODE*	pCur;
	COMPAREFUNC	CompareFunc;
	void*		pMatchData;
}SINLELISST_ENUM;

SINGLELIST* SingleList_Create(void);
INT SingleList_Delete(SINGLELIST* pSingleList, void* pMatchData,
	COMPAREFUNC CompareFunc, DESTROYFUNC DestroyFunc);
void* SingleList_GetAt(SINGLELIST* pSingleList, UINT uIndex);
INT SingleList_Traverse(SINGLELIST* pSingleList, TRAVERSEFUNC TraverseFunc);
UINT SingleList_GetCount(SINGLELIST* pSingleList);
void* SingleList_EnumNext(SINGLELIST* pSingleList);
void SingleList_EnumBegin(SINGLELIST* pSingleList);
void* SingleList_GetTail(SINGLELIST* pSingleList);
void* SingleList_GetHead(SINGLELIST* pSingleList);
void* SingleList_GetCursor(SINGLELIST* pSingleList);
void* SingleList_PopTail(SINGLELIST* pSingleList);
INT Single_InsertTail(SINGLELIST* pSingleList, void* pData);
void* SingleList_PopHead(SINGLELIST* pSingleList);
INT SingleList_InSertHead(SINGLELIST* pSingleList, void* pData);
void SingleList_Destroy(SINGLELIST* pSingleList, DESTROYFUNC DestroyFunc);

#endif