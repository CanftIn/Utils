/************************************************************************/
/* MTList.h
*/
/************************************************************************/

#ifndef __MTLIST_H__
#define __MTLIST_H__

#include "Global.h"
#include "MTask.h"
#include "DoubleList.h"

#define MTLIST_DELETE_NODE	0
#define MTLIST_NO_DELETE	1

typedef struct MTLIST_st
{
	DOUBLELIST* pList;
	MTASK*		pMTask;
}MTLIST;

MTLIST *MTList_Create(void);
void    MTList_Destroy(MTLIST *pList, DESTROYFUNC DestroyFunc);

UINT    MTList_GetExitFlag(MTLIST *pList);
void    MTList_SetExitFlag(MTLIST *pList, UINT uExitFlag);
void    MTList_EnterTask(MTLIST *pList);
void    MTList_LeaveTask(MTLIST *pList);

INT     MTList_InsertHead(MTLIST *pList, void *pData);
INT     MTList_DeleteHead(MTLIST *pList, DESTROYFUNC DestroyFunc);
INT     MTList_InsertTail(MTLIST *pList, void *pData);
void *  MTList_PopHead(MTLIST *pList);
void *  MTList_PopTail(MTLIST *pList);


void    MTList_EnumBegin(MTLIST *pList);
INT     MTList_EnumNext(MTLIST *pList, VISITFUNC VisitFunc);
INT     MTList_EnumNextCopy(MTLIST *pList, VISITFUNC VisitFunc,
	DESTROYFUNC DestroyFunc, COPYFUNC CopyFunc);
INT     MTList_EnumNextAndDelete(MTLIST *pList, VISITFUNC VisitFunc,
	DESTROYFUNC DestroyFunc);




#endif

