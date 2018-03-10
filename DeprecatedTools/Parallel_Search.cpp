/************************************************************************/
/* Parallel_Search.cpp
*/
/************************************************************************/

#include "Global.h"
#include <omp.h>

int Parallel_SearchData(void** ppData, int nLen, void* pData, COMPAREFUNC comp)
{
	int i, k;
	int nRet = -1;
	int nCore = omp_get_num_procs();
	int nStep = nLen / nCore;
#pragma omp parallel for
	for (k = 0; k < nCore; k++)
	{
		int begin = k * nStep;
		int end = (k + 1) * nStep;
		if (k == nCore - 1)
		{
			end = nLen;
		}
		for (i = begin; i < end; i++)
		{
			if ((*comp)(ppData[i], pData) == 0)
			{
				nRet = i;
			}
		}
	}
	return nRet;
}

int Parallel_SearchMaxData(void** ppData, int nLen, COMPAREFUNC comp)
{
	int i, k;
	int nCore = omp_get_num_procs();

	int* pnMax = (int *)malloc(nCore * sizeof(int));

	if (pnMax == NULL)
	{
		return -1;
	}

	int nStep = nLen / nCore;

#pragma omp parallel for
	for (k = 0; k < nCore; k++)
	{
		int begin = k * nStep;
		int end = (k + 1) * nStep;
		if (k == nCore - 1)
		{
			end = nLen;
		}
		int nMax = begin;
		for (i = begin; i < end; i++)
		{
			if ((*comp)(ppData[i], ppData[nMax]) > 0)
			{
				nMax = i;
			}
		}
		pnMax[k] = nMax;
	}
	int nMax = 0;
	for (i = 1; i < nCore; i++)
	{
		if ((*comp)((void*)pnMax[i], (void*)pnMax[nMax]) > 0)
		{
			nMax = i;
		}
	}
	nMax = pnMax[nMax];
	free(pnMax);
	return nMax;
}





















