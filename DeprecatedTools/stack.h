
#ifndef __STACK_H__
#define __STACK_H__

#include "Global.h"




typedef struct STACK_at
{
	void** ppBase;
	UINT uTop;
	unsigned uStackSize;
}STACK;

STACK* Stack_Create(UINT uStackSize);
void Stack_Destroy(STACK* pStack, DESTROYFUNC DestroyFunc);
void* Stack_Pop(STACK* pStack);
INT Stack_Push(STACK* pStack, void* pData);
INT Stack_IsEmpty(STACK* pStack);





#endif