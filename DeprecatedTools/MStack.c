/************************************************************************/
/* MStack.c
*/
/************************************************************************/

#include "MStack.h"

MSTACK* MStack_Create(UINT uStackSize)
{
	MSTACK* pMStack = (MSTACK*)malloc(sizeof(MSTACK));
	if (pMStack != NULL)
	{
		pMStack->pStack = Stack_Create(uStackSize);
		if (pMStack->pStack != NULL)
		{
			/*Ëø*/
			InitializeCriticalSection(&(pMStack->FastLock));
			return pMStack;
		}
		free(pMStack);
	}
	return NULL;
}

void MStack_Destroy(MSTACK* pMStack, DESTROYFUNC DestroyFunc)
{
	if (pMStack != NULL)
	{
		EnterCriticalSection(&(pMStack->FastLock));
		Stack_Destroy(pMStack->pStack, DestroyFunc);
		DeleteCriticalSection(&(pMStack->FastLock));

		free(pMStack);
	}
}

void* MStack_Pop(MSTACK* pMStack)
{
	void* pData;

	EnterCriticalSection(&(pMStack->FastLock));
	pData = Stack_Pop(pMStack->pStack);
	DeleteCriticalSection(&(pMStack->FastLock));

	return pData;
}

INT MStack_Push(MSTACK* pMStack, void* pData)
{
	INT nRet;

	EnterCriticalSection(&(pMStack->FastLock));
	nRet = Stack_Push(pMStack->pStack, pData);
	DeleteCriticalSection(&(pMStack->FastLock));

	return nRet;
}

INT MStack_IsEmpty(MSTACK* pMStack)
{
	INT nRet;

	EnterCriticalSection(&(pMStack->FastLock));
	nRet = Stack_IsEmpty(pMStack->pStack);
	DeleteCriticalSection(&(pMStack->FastLock));

	return nRet;
}















