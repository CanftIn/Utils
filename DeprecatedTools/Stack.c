// CreateStack.cpp : 定义控制台应用程序的入口点。
//

#include "stack.h"



STACK* Stack_Create(UINT uStackSize)
{
	STACK* pStack;
	if (uStackSize == 0)
	{
		return NULL;
	}
	pStack = (STACK*)malloc(sizeof(struct STACK_at));
	if (pStack != NULL)
	{
		pStack->ppBase = (void**)malloc(uStackSize * sizeof(void*));
		if (pStack->ppBase == NULL)
		{
			free(pStack);
			pStack = NULL;
		}
		else
		{
			pStack->ppBase[0] = NULL;
			pStack->uTop = 0;
			pStack->uStackSize = uStackSize;
		}
	}
	return pStack;
}

void Stack_Destroy(STACK* pStack, DESTROYFUNC DestroyFunc)
{
	if (pStack != NULL)
	{
		if (pStack->ppBase != NULL)
		{
			if (DestroyFunc != NULL)
			{
				UINT i;
				for (i = 0; i < pStack->uTop; i++)
				{
					if (pStack->ppBase[i] != NULL)
					{
						(*DestroyFunc)(pStack->ppBase[i]);
					}
				}
			}
			free(pStack->ppBase);
		}
		free(pStack);
		pStack = NULL;
	}
}

void* Stack_Pop(STACK* pStack)
{
	void* pData;
	if (pStack == NULL || pStack->uTop == 0)
	{
		return NULL;
	}
	pStack->uTop -= 1;
	pData = pStack->ppBase[pStack->uTop];
	return pData;
}

INT Stack_IsEmpty(STACK* pStack)
{
	if (pStack->uTop = 0)
	{
		return 1;
	}
	return 0;
}

INT Stack_Push(STACK* pStack, void* pData)
{
	if (pStack == NULL)
	{
		return CAPI_FAILED;
	}

	if (pStack->uTop >= pStack->uStackSize - 1)
	{
		pStack->ppBase = (void**)realloc(pStack->ppBase, (pStack->uStackSize * 2) * sizeof(void*));
		if (pStack->ppBase == NULL)
		{
			return CAPI_FAILED;
		}
		pStack->uStackSize *= 2;
	}
	pStack->ppBase[pStack->uTop] = pData;
	pStack->uTop += 1;

	return CAPI_SUCCESS;
}
















