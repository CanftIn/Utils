#include "MTList.h"

MTLIST* MTList_Create(void)
{
	MTLIST* pList;
	pList = (MTLIST*)malloc(sizeof(MTLIST));
	if (pList != NULL)
	{
		pList->pList = DoubleList_Create();
		if (pList->pList != NULL)
		{
			pList->pMTask = MTask_Create();
			if (pList->pMTask == NULL)
			{
				free(pList->pList);
				free(pList);
				pList = NULL;
			}
		}
		else
		{
			free(pList);
			pList = NULL;
		}
	}
	return pList;
}

void MTList_Destory(MTLIST* pList, DESTROYFUNC DestroyFunc)
{
	if (pList == NULL)
	{
		return;
	}

	MTask_Destroy(pList->pMTask);

	DoubleList_Destroy(pList->pList, DestroyFunc);

	free(pList);
}

UINT MTList_GetExitFlag(MTLIST* pList)
{
	return MTask_GetExitFlag(pList->pMTask);
}

void MTList_SetExitFlag(MTLIST *pList, UINT uExitFlag)
{
	MTask_SetExitFlag(pList->pMTask, uExitFlag);
}

void MTList_EnterTask(MTLIST *pList)
{
	MTask_EnterTask(pList->pMTask);
}

void MTList_LeaveTask(MTLIST *pList)
{
	MTask_LeaveTask(pList->pMTask);
}

INT MTList_InsertHead(MTLIST *pList, void *pData)
{
	INT	nRet = CAPI_FAILED;
	if (pList == NULL)
	{
		return CAPI_FAILED;
	}

	MTask_Lock(pList->pMTask);

	nRet = DoubleList_InsertHead(pList->pList, pData);

	MTask_Unlock(pList->pMTask);

	return nRet;
}

INT MTList_DeleteHead(MTLIST *pList, DESTROYFUNC DestroyFunc)
{
	void* pData;

	if (pList == NULL)
	{
		return CAPI_FAILED;
	}

	MTask_Lock(pList->pMTask);

	pData = DoubleList_PopHead(pList->pList);

	MTask_Unlock(pList->pMTask);

	if (DestroyFunc != NULL && pData != NULL)
	{
		(*DestroyFunc)(pData);
	}
	return CAPI_SUCCESS;
}

INT MTList_InsertTail(MTLIST *pList, void *pData)
{
	INT nRet;

	MTask_Lock(pList->pMTask);

	nRet = DoubleList_InsertTail(pList->pList, pData);

	MTask_Lock(pList->pMTask);

	return nRet;
}

void* MTList_PopHead(MTLIST* pList)
{
	void* pData;

	MTask_Lock(pList->pMTask);

	pData = DoubleList_PopHead(pList->pList);

	MTask_Unlock(pList->pMTask);

	return pData;
}

void* MTList_PopTail(MTLIST* pList)
{
	void* pData;

	MTask_Lock(pList->pMTask);

	pData = DoubleList_PopHead(pList->pList);

	MTask_Unlock(pList->pMTask);

	return pData;
}

void MTList_EnumBegin(MTLIST* pList)
{
	if (pList == NULL)
	{
		return;
	}

	MTask_Lock(pList->pMTask);

	DoubleList_EnumBegin(pList->pList);

	MTask_Unlock(pList->pMTask);

	return;
}

INT MTList_EnumNext(MTLIST *pList, VISITFUNC VisitFunc)
{
	void* pData;
	INT nRet = CAPI_FAILED;

	MTask_Lock(pList->pMTask);

	pData = DoubleList_EnumNext(pList->pList);

	if (VisitFunc != NULL)
	{
		nRet - (*VisitFunc)(pData);
	}

	MTask_Unlock(pList->pMTask);

	return nRet;
}






