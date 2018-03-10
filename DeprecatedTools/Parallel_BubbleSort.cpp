#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include "Global.h"

void BubbleSort(void** ppData, int nDataLen, COMPAREFUNC func)
{
	int i, j;

	for (i = 0; i < nDataLen - 1; i++)
	{
		for (j = 0; j < nDataLen - i - 1; j++)
		{
			if ((*func)(ppData[j], ppData[j + 1]) > 0)
			{
				void* pData = ppData[j];
				ppData[j] = ppData[j + 1];
				ppData[j + 1] = pData;
			}
		}
	}
	return;
}

void Parallel_BubbleSort(void** ppData, int nDataLen, COMPAREFUNC func)
{
	int i, j;

	for (i = 0; i < nDataLen - 1; i++)
	{
		if ((i & 0x1) == 0)
		{
#pragma omp parallel for
			for (j = 0; j < nDataLen - 1; j += 2)
			{
				if ((*func)(ppData[j], ppData[j + 1]) > 0)
				{
					void* pData = ppData[j];
					ppData[j] = ppData[j + 1];
					ppData[j + 1] = pData;
				}
			}
		}

		else
		{
#pragma omp parallel for
			for (j = 1; j < nDataLen - 1; j += 2)
			{
				if ((*func)(ppData[j], ppData[j + 1]) > 0)
				{
					void* pData = ppData[j];
					ppData[j] = ppData[j + 1];
					ppData[j + 1] = pData;
				}
			}
		}
	}
	return;
}





















