// 动态加载C接口宏定义
// 20220425
// wang.yc

#pragma once

#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#ifdef WINCE
#define MGetProcAddress GetProcAddressA
#else
#define MGetProcAddress GetProcAddress
#endif

#ifndef GTR_RTN_OK
#define GTR_RTN_OK				0		/*执行正常*/
#endif

#define GTR_RTN_ERR_DLL_LOAD	(-9020)	/*DLL句柄加载失败*/
#define GTR_RTN_ERR_FUN_LOAD	(-9021)	/*DLL函数指针加载失败*/
#define GTR_RTN_ERR_DLL_FREE	(-9022)	/*DLL句柄释放失败*/
#define GTR_RTN_ERR_DLL_PARAM	(-9023)	/*DLL加载使用参数错误*/

// 记录错误日志到char数组
extern char	cGtrErrMsg[512];
#define GTR_API_CHECK(funPtr)	{\
	if(NULL == funPtr){\
	sprintf_s(cGtrErrMsg,"%Function pointer %s is null",#funPtr);\
	return(GTR_RTN_ERR_FUN_LOAD);}}

// 步骤（1）：定义函数GTR_API_DEF
// 例：
// 待导出的函数为:
// extern "C" short _stdcall GTR_PLS_SomeFunc(short *pOutput, short input);
// GTR_API_DEF(GTR_PLS_SomeFunc, short*, short)
#define GTR_API_DEF(funName,...) \
	typedef short (_stdcall * (DEF_ ## funName))(__VA_ARGS__);\
	DEF_ ## funName fp ## funName = NULL;


// 步骤（2）：加载函数GTR_API_LOAD
// 例：
// 1) 定义全局句柄
// HINSTANCE g_dllhandle;
// 2) 加载句柄（配置属性-常规-使用unicode字符集）
// g_dllhandle = LoadLibrary(_T("xxxx.dll"));
// 3) 加载函数
// GTR_API_LOAD(g_dllhandle, GTR_PLS_SomeFunc)
#define GTR_API_LOAD(dllHandle, funName) \
	if(NULL == dllHandle){return GTR_RTN_ERR_DLL_LOAD;} \
	fp ## funName = (DEF_ ## funName) MGetProcAddress(dllHandle, #funName);\
	if(NULL == fp ## funName){return GTR_RTN_ERR_FUN_LOAD;} 


// 步骤（3）：调用函数GTR_API_CALL
// 例：
// short* pOutput;
// short input;
// GTR_API_LOAD(GTR_PLS_SomeFunc, pOutput, input)
#define GTR_API_CALL(funName, ...) \
	if(NULL == fp ## funName){return GTR_RTN_ERR_FUN_LOAD;} \
	return fp ## funName(__VA_ARGS__);