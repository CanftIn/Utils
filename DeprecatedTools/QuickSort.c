/************************************************************************/
/* QuickSort.c
*/
/************************************************************************/

#include "QuickSort.h"

void* GetMid(void *p1, void *p2, void* p3, COMPAREFUNC Comp)
{
	void* pMid;
	if ((*Comp)(p1, p2) > 0)
	{
		if ((*Comp)(p2, p3) > 0)
		{
			pMid = p2;
		}
		else
		{
			if ((*Comp)(p1, p3) > 0)
			{
				pMid = p3;
			}
			else
			{
				pMid = p1;
			}
		}
	}
	else
	{
		if ((*Comp)(p1, p3) > 0)
		{
			pMid = p3;
		}
		else
		{
			if ((*Comp)(p2, p3) > 0)
			{
				pMid = p3;
			}
			else
			{
				pMid = p2;
			}
		}
	}
	return pMid;
}

UINT Split(void** ppData, UINT uStart, UINT uEnd, COMPAREFUNC CompareFunc)
{
	void* pSelData;
	UINT uLow;
	UINT uHigh;

	uLow = uStart;
	uHigh = uEnd;

	pSelData = ppData[uLow];
	while (uLow < uHigh)
	{
		while ((*CompareFunc)(ppData[uHigh], pSelData) > 0 && uLow != uHigh)
		{
			--uHigh;
		}
		if (uHigh != uLow)
		{
			ppData[uLow] = ppData[uHigh];
			++uLow;
		}
		while ((*CompareFunc)(ppData[uLow], pSelData) < 0 && uLow != uHigh)
		{
			++uLow;
		}
		if (uLow != uHigh)
		{
			ppData[uHigh] = ppData[uLow];
			--uHigh;
		}
	}
	ppData[uLow] = pSelData;

	return uLow;

}























