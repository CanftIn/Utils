#include "MTask.h"

MTASK* MTask_Create()
{
	MTASK* pMTask;

	pMTask = (MTASK*)malloc(sizeof(MTASK));

	if (pMTask != NULL)
	{
		InitializeCriticalSection(&(pMTask->FastLock));

		pMTask->pExitEvent = EventCreate();
		if (pMTask->pExitEvent == NULL)
		{
			DeleteCriticalSection(&(pMTask->FastLock));
			free(pMTask);
			return NULL;
		}
		pMTask->uTaskCount = 0;
		pMTask->uExitFlag = MTASK_NO_EXIT;
	}
	return pMTask;
}























