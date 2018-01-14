/************************************************************************/
/* Global.h
*/
/************************************************************************/

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "FastLock.h"


#define CAPI_SUCCESS	0
#define CAPI_FAILED		1



typedef unsigned int UINT;


/*
 *	节点结构
 */
typedef struct SINGLENODE_st
{
	struct SINGLENODE_st* pNext;
	void* pData;
}SINGLENODE, *PSINGLENODE;

typedef struct DOUBLENODE_st
{
	struct DOUBLENODE_st* pNext;
	struct DOUBLENODE_st* pPrev;
	void* pData;
}DOUBLENODE;

typedef struct DOUBLELIST_ST
{
	DOUBLENODE* pHead;
	DOUBLENODE* pTail;
	DOUBLENODE* pCur;
	UINT		uCount;
}DOUBLELIST;




/**通用类型数据释放函数

	@param void* pData -要释放的数据	
	@return	 -无
*/
typedef void(*DESTROYFUNC)(void* pData);



/**	通用类型数据比较函数

@param	void *pData1 -要比较的第1个参数
@param	void *pData2 -要比较的第2个参数
@return	INT - 小于0表示pData1小于pData2, 等于0表示pData1等于pData2,
大于0表示pData1大于pData2
*/
typedef INT(*COMPAREFUNC)(void* pData1, void* pData2);



/*通用类型数据的遍历执行函数

	@param	void *pData - 要操作的数据指针
	@return	void - 无
 */
typedef void(*TRAVERSEFUNC)(void *pData);

/**	通用类型数据的遍历执行函数

@param	void *pData - 要操作的数据指针
@return	void - 无
*/
typedef INT(*VISITFUNC)(void *pData);

/**	通用数据拷贝函数

@param	void *pData - 要拷贝的数据
@return	void * - 成功返回拷贝的数据，失败返回NULL
*/
typedef void *(*COPYFUNC)(void *pData);

/**	计算哈希值的回调函数

@param  void *pKey - 要计算哈希值的关键词
@param  UINT uBucketNum - 哈希表中的BUCKET数组大小
@return UINT - 返回计算出的哈希值，一般用作哈希表BUCKET数组下标。
*/
typedef UINT(*HASHFUNC)(void *pKey, UINT uBucketNum);






#define		EVENT		HANDLE

#define EventCreate()	CreateEvent(NULL, TRUE, FALSE, NULL)










#endif
































