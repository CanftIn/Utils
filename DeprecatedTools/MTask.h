#ifndef __MTASK_H__
#define __MTASK_H__

#include "Global.h"

#define MTASK_NO_EXIT	0
#define	MTASK_EXIT		1

typedef struct MTASK_st
{
	FASTLOCK FastLock;
	EVENT	 pExitEvent;

	UINT	 uExitFlag;
	UINT	 uTaskCount;
}MTASK;

MTASK * MTask_Create();
void    MTask_Destroy(MTASK *pMTask);

void    MTask_Lock(MTASK *pMTask);
void    MTask_Unlock(MTASK *pMTask);

UINT    MTask_GetExitFlag(MTASK *pMTask);
void    MTask_SetExitFlag(MTASK *pMTask, UINT uExitFlag);
void    MTask_EnterTask(MTASK *pMTask);
void    MTask_LeaveTask(MTASK *pMTask);





#endif