// 工具类：获取系统内存与cpu状态
// wang.yc
// 20220428

#pragma once

#include "windows.h"

const int Byte2Mb = 1024 * 1024;

typedef struct SystemMemory
{
	short loadPercent;
	double physicalAvailableMb;
	double physicalTotalMb;
	double physicalAvailablePercent;
	double virtualAvailableMb;
	double virtualTotalMb;
	double virtualAvailablePercent;
} TSystemMemory;

// 获取系统内存
inline void GetSystemMemoryStatus(TSystemMemory* pMemoryStatus)
{
#ifdef WINCE
	MEMORYSTATUS status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatus(&status);

	pMemoryStatus->loadPercent = 1.0 * status.dwMemoryLoad;

	pMemoryStatus->physicalAvailableMb = 1.0 * status.dwAvailPhys / Byte2Mb;
	pMemoryStatus->physicalTotalMb = 1.0 * status.dwTotalPhys / Byte2Mb;
	pMemoryStatus->physicalAvailablePercent = status.dwTotalPhys ? 100.0 * status.dwAvailPhys / status.dwTotalPhys : 0;

	pMemoryStatus->virtualAvailableMb = 1.0 * status.dwAvailVirtual / Byte2Mb;
	pMemoryStatus->virtualTotalMb = 1.0 * status.dwTotalVirtual / Byte2Mb;
	pMemoryStatus->virtualAvailablePercent = status.dwTotalVirtual ? 100.0 * status.dwAvailVirtual / status.dwTotalVirtual : 0;
#else
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);

	pMemoryStatus->loadPercent = (short)status.dwMemoryLoad;

	pMemoryStatus->physicalAvailableMb = 1.0 * status.ullAvailPhys / Byte2Mb;
	pMemoryStatus->physicalTotalMb = 1.0 * status.ullTotalPhys / Byte2Mb;
	pMemoryStatus->physicalAvailablePercent = status.ullTotalPhys ? 100.0 * status.ullAvailPhys / status.ullTotalPhys : 0;

	pMemoryStatus->virtualAvailableMb = 1.0 * status.ullAvailVirtual / Byte2Mb;
	pMemoryStatus->virtualTotalMb = 1.0 * status.ullTotalVirtual / Byte2Mb;
	pMemoryStatus->virtualAvailablePercent = status.ullTotalVirtual ? 100.0 * status.ullAvailVirtual / status.ullTotalVirtual : 0;
#endif
}

// 获取系统处理器数量
typedef unsigned long uint32;
inline uint32 GetProcessorNumber()
{
	SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
	return system_info.dwNumberOfProcessors;
}

typedef unsigned long uint64;
static uint64 convert_time_format(const FILETIME* ftime)
{
	LARGE_INTEGER li;

	li.LowPart = ftime->dwLowDateTime;
	li.HighPart = ftime->dwHighDateTime;
	return li.QuadPart;
}

#include "pdh.h"
#pragma comment(lib, "pdh.lib")

static PDH_HQUERY cpuQuery = NULL;
static PDH_HCOUNTER pdhValue;

// document
// https://blog.csdn.net/fengyishang/article/details/46440135?spm=1035.2023.3001.6557&utm_medium=distribute.pc_relevant_bbs_down_v2.none-task-blog-2~default~OPENSEARCH~Rate-2-46440135-bbs-330063094.pc_relevant_bbs_down_cate&depth_1-utm_source=distribute.pc_relevant_bbs_down_v2.none-task-blog-2~default~OPENSEARCH~Rate-2-46440135-bbs-330063094.pc_relevant_bbs_down_cate

inline float GetCpuPercent()
{
#ifdef WINCE
	return 0;
#else

	// 从pdh （performance data helper） 性能监视器获取
	static bool is_first_call = true;
	if (is_first_call)
	{
		is_first_call = false;

		PDH_STATUS status = PdhOpenQuery(NULL, NULL, &cpuQuery);
		if (status == ERROR_SUCCESS)
		{
			// 添加query到计数器中(获取某一刻CPU总的使用时间)
			status = PdhAddCounter(cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &pdhValue);
		}
	}

	double resVlaue = 0;
	PDH_FMT_COUNTERVALUE counterVal;

	// 开始查询：如果执行成功，则返回ERROR_SUCCESS
	PDH_STATUS status = PdhCollectQueryData(cpuQuery);
	if (status == ERROR_SUCCESS)
	{
		status = PdhGetFormattedCounterValue(pdhValue, PDH_FMT_DOUBLE, NULL, &counterVal);
		if (status == ERROR_SUCCESS)
		{
			resVlaue = counterVal.doubleValue;
		}
	}

	return resVlaue;

	// 直接计算
	/*FILETIME f_time_idle;
	FILETIME f_time_kernal;
	FILETIME f_time_user;

	GetSystemTimes(&f_time_idle, &f_time_kernal, &f_time_user);

	uint64 this_idle_time = convert_time_format(&f_time_idle);
	uint64 this_kernal_time = convert_time_format(&f_time_kernal);
	uint64 this_user_time = convert_time_format(&f_time_user);

	static uint64 last_idle_time = 0, last_kernal_time = 0, last_user_time = 0;

	uint64 idle_time = this_idle_time - last_idle_time;
	uint64 kernal_time = this_kernal_time - last_kernal_time;
	uint64 user_time = this_user_time - last_user_time;

	uint64 sys_time = kernal_time + user_time;
	float cpu_load_percent = sys_time ? 1.0 * (sys_time - idle_time) * 100 / sys_time : 0;

	last_idle_time = this_idle_time;
	last_kernal_time = this_kernal_time;
	last_user_time = this_user_time;

	return cpu_load_percent;*/
#endif
}