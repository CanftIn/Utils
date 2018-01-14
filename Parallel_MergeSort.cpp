#include "Parallel_MergeSort.h"

#define		MIN_PARALLEL_ARRAY__COUNT	512
#define		MIN_PARALLEL_SORT_COUNT		1024

// int* MergeInt(int *pnData, int nStart1, int nEnd1, int nStart2, int nEnd2)
// {
// 	int i, j, k, nLen;
// 	int* pnNewData;
// 
// 	nLen = nEnd1 - nStart1 + nEnd2 - nStart2 + 2;
// 
// }

void** Serial_Merge(void **ppData, int nStart1, int nEnd1, int nStart2, int nEnd2, COMPAREFUNC func, void **ppOutData)
{
	int i, j, k;

	i = nStart1;
	j = nStart2;
	k = nStart1;

	for (i = nStart1; i <= nEnd1; i++)
	{
		for (; j <= nEnd2; j++)
		{
			if ((*func)(ppData[i], ppData[j]) < 0)
			{
				ppOutData[k] = ppData[i];
				++k;
				break;
			}
			else
			{
				ppOutData[k] = ppData[j];
				++k;
			}
		}
		if (j > nEnd2)
		{
			for (; i <= nEnd1; i++)
			{
				ppOutData[k] = ppData[i];
				++k;
			}
			break;
		}
	}
	if (i > nEnd1)
	{
		for (; j <= nEnd2; j++)
		{
			ppOutData[k] = ppData[j];
			++k;
		}
	}
	return ppOutData;
}












