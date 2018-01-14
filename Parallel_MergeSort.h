#ifndef __PARALLEL_MERGESORT_H__
#define __PARALLEL_MERGESORT_H__
#include "Global.h"

void** Serial_Merge(void **ppData, int nStart1, int nEnd1, int nStart2, int nEnd2,
	COMPAREFUNC func, void **ppOutData);

int * MergeInt(int *pnData, int nStart1, int nEnd1, int nStart2, int nEnd2);

void Serial_MergeSort(void **ppData, int nBegin, int nEnd, COMPAREFUNC func);

void Serial_Merge2(void **ppData, int nStart1, int nStart2, int nEnd2, COMPAREFUNC func);
void Serial_Merge3(void **ppData, int nStart1, int nStart2, int nEnd2, COMPAREFUNC func);

void Parallel_MergeSort(void **ppData, int nLen, COMPAREFUNC func);
void Parallel_MergeSort2(void **ppData, int nLen,
	int nTurn, COMPAREFUNC func);

#endif