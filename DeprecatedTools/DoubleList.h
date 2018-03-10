/************************************************************************/
/* DoubleList.h
*/
/************************************************************************/

#ifndef __DOUBLELIST_H__
#define __DOUBLELIST_H__
#include "Global.h"

DOUBLELIST* DoubleList_Create(void);
void DoubleList_Destroy(DOUBLELIST* pList, DESTROYFUNC DestroyFunc);
INT DoubleList_InsertTail(DOUBLELIST* pList, void* pData);
INT DoubleList_InsertHead(DOUBLELIST* pList, void* pData);
void* DoubleList_PopHead(DOUBLELIST* pList);
void* DoubleList_PopTail(DOUBLELIST* pList);
INT DoubleList_Delete(DOUBLELIST* pList, void* pMatchData, COMPAREFUNC CompareFunc, DESTROYFUNC DestroyFunc);
UINT DoubleList_GetCount(DOUBLELIST* pList);
void* DoubleList_GetHead(DOUBLELIST* pList);

void* DoubleList_GetTail(DOUBLELIST* pList);
void* DoubleList_Find(DOUBLELIST* pList, void* pMatchData, COMPAREFUNC CompareFunc);
void DoubleList_EnumBegin(DOUBLELIST* pList);
void* DoubleList_EnumNext(DOUBLELIST* pList);
DOUBLENODE* Doublelist_EnumNode(DOUBLELIST* pList);
DOUBLELIST* DoubleList_PopNode(DOUBLELIST* pList, DOUBLENODE* pNode);
DOUBLELIST *    DoubleList_Copy(DOUBLELIST *pList, COPYFUNC CopyFunc);
#endif











