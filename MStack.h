/************************************************************************/
/* MStack.h
*/
/************************************************************************/


#ifndef __MSTACK_H__
#define __MSTACK_H__

#include "stack.h"


typedef struct MSTACK_st
{
	STACK*	pStack;
	FASTLOCK	FastLock;
}MSTACK;

MSTACK* MStack_Create(UINT uStackSize);
void MStack_Destroy(MSTACK* pMStack, DESTROYFUNC DestroyFunc);
void* MStack_Pop(MSTACK* pMStack);
INT MStack_Push(MSTACK* pMStack, void* pData);
INT MStack_IsEmpty(MSTACK* pMStack);



#endif