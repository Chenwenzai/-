#pragma  once

#pragma comment(lib, "Version.lib")
#include "windows.h"
#include "stdio.h"

#include <QString>
#include <QDebug>
#include "gtr_string.hpp"

struct GtrVersionInfo
{
	short lead;
	short major;
	short minor;
	short patch;
};

class GtrVersion
{
public:
	// return true if sussceesul
	static bool OS_GetDllVersion(char dll_name[100], GtrVersionInfo& version)
	{
		memset(&version, 0, sizeof(version));

		DWORD dwHandle, dwLen;
		UINT BufLen;
		LPTSTR lpData;
		VS_FIXEDFILEINFO* pFileInfo;
		dwLen = GetFileVersionInfoSizeA(dll_name, &dwHandle);
		if (!dwLen)
			return FALSE;
		lpData = (LPTSTR)malloc(dwLen);
		if (!lpData)
			return FALSE;
		if (!GetFileVersionInfoA(dll_name, dwHandle, dwLen, lpData))
		{
			free(lpData);
			return FALSE;
		}
		if (VerQueryValueA(lpData, "\\", (LPVOID*)&pFileInfo, (PUINT)&BufLen))
		{
			version.lead = HIWORD(pFileInfo->dwFileVersionMS);
			version.major = LOWORD(pFileInfo->dwFileVersionMS);
			version.minor = HIWORD(pFileInfo->dwFileVersionLS);
			version.patch = LOWORD(pFileInfo->dwFileVersionLS);

			free(lpData);
			return TRUE;
		}
		free(lpData);
		return FALSE;
	}

	// 获取Dll版本信息
	static short GetDllVersion(QString dll_name, GtrVersionInfo& version_info)
	{
		// get version
		char s_dll_name[100];
		char s_dll_version[100];

		QStrToChar(dll_name, s_dll_name, 100);
		if (!OS_GetDllVersion(s_dll_name, version_info))
		{
			qDebug() << QString("Version is NULL for dll name[%1]").arg(dll_name);
			return -1;
		}
		return 0;
	}

	// 版本信息转换为字符串
	static QString VersionInfoToQtStr(const GtrVersionInfo& version_info)
	{
		QString version = QString("v%1.%2.%3.%4").arg(version_info.lead).arg(version_info.major)
			.arg(version_info.minor).arg(version_info.patch);
		return version;
	}

	// 字符数组转换为版本信息
	static short CharArrayToVersion(const char version_char[100], GtrVersionInfo& version_info)
	{
		QString version_str = CharToQStr(version_char);
		QStringList str_list = version_str.split(".");
		if (str_list.size() < 4)
		{
			qDebug() << QString("dll version [%1] has wrong format!")
				.arg(version_str);
			return -1;
		}
		version_info.lead = str_list[0].toShort();
		version_info.major = str_list[1].toShort();
		version_info.minor = str_list[2].toShort();
		version_info.patch = str_list[3].toShort();
		return 0;
	}

	// 版本是否相等
	static bool IsEqual(const GtrVersionInfo& version_info_a, const GtrVersionInfo& version_info_b)
	{
		return version_info_a.lead == version_info_b.lead &&
			version_info_a.major == version_info_b.major &&
			version_info_a.minor == version_info_b.minor &&
			version_info_a.patch == version_info_b.patch;
	}
};