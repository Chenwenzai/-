#pragma once
#ifndef GTR_STRING_H
#define GTR_STRING_H

#include "windows.h"
#include <QtGlobal>
#include <QString>
#include <QTextCodec>
#include <string>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#define QT5
#elif QT_VERSION >= QT_VERSION_CHECK(4, 0, 0)
#define QT4
#else
#error // 非法QT版本, 编译器报错
#endif

enum GtrCharType
{
	kCharTypeAuto,
	kCharTypeUtf8,
	kCharTypeLocal8Bit,
	kCharTypeGBK,
};

// std::string 转 QString
inline QString StdStrToQStr(const std::string& input_str, GtrCharType type = kCharTypeAuto)
{
	char* temp_char = (char*)input_str.c_str();
	QString temp_str = QString(temp_char);
	return temp_str;
}

// QString 转 std::string
inline std::string QStrToStdStr(const QString& input_str, GtrCharType type = kCharTypeAuto)
{
	std::string temp_std;
	QByteArray temp_ba;
	if (kCharTypeUtf8 == type)
	{
		temp_ba = input_str.toUtf8();
	}
	else if (kCharTypeLocal8Bit == type)
	{
		temp_ba = input_str.toLocal8Bit();
	}
	else
	{
#if defined(QT5)
		temp_ba = input_str.toUtf8();
#elif defined(QT4)
		temp_ba = input_str.toLocal8Bit();
#endif
	}

	const char* temp_char = temp_ba.constData();
	temp_std = std::string(temp_char);

	return temp_std;
}

// char[] 转 QString
inline QString CharToQStr(const char* input_char, GtrCharType type = kCharTypeAuto)
{
	if (kCharTypeUtf8 == type)
	{
		return QString::fromUtf8(input_char);
	}

	if (kCharTypeLocal8Bit == type)
	{
		return QString::fromLocal8Bit(input_char);
	}

	if (kCharTypeGBK == type)
	{
		QTextCodec* p_code_gbk = QTextCodec::codecForName("gbk");
		QTextCodec* p_code_utf8 = QTextCodec::codecForName("UTF-8");

		QString str = p_code_gbk->toUnicode(input_char);
		QByteArray utf8_ba = p_code_utf8->fromUnicode(str);
		return QString(utf8_ba);
	}

#if defined(QT5)
	return QString::fromUtf8(input_char);
#elif defined(QT4)
	return QString::fromLocal8Bit(input_char);
#endif
}

// QString[] 转 char
inline void QStrToChar(const QString& input_str, char* output_char, short char_size, GtrCharType type = kCharTypeAuto)
{
	QByteArray temp_ba;
	if (kCharTypeUtf8 == type)
	{
		temp_ba = input_str.toUtf8();
	}
	else if (kCharTypeLocal8Bit == type)
	{
		temp_ba = input_str.toLocal8Bit();
	}
	else
	{
#if defined(QT5)
		temp_ba = input_str.toUtf8();
#elif defined(QT4)
		temp_ba = input_str.toLocal8Bit();
#endif
	}
	temp_ba.resize(char_size - 1);
	strcpy_s(output_char, char_size, temp_ba.constData());
}

// QString BGK编码 转 utf8编码
inline QString QtGbkToUtf8(const QString& input)
{
	QTextCodec* p_gbk = QTextCodec::codecForName("GBK");
	QTextCodec* p_utf8 = QTextCodec::codecForName("UTF-8");

	QByteArray ba = input.toLocal8Bit();
	QString unicode_str = p_gbk->toUnicode(ba);
	QByteArray utf_ba = p_utf8->fromUnicode(unicode_str);

	return QString(utf_ba);
}

// QString utf8编码 转 BGK编码
inline QString QtUtf8ToGbk(const QString& input)
{
	QTextCodec* p_gbk = QTextCodec::codecForName("GBK");
	QTextCodec* p_utf8 = QTextCodec::codecForName("UTF-8");

	QByteArray ba = input.toLocal8Bit();
	QString unicode_str = p_utf8->toUnicode(ba);
	QByteArray gbk_ba = p_gbk->fromUnicode(unicode_str);

	return QString(gbk_ba);
}

#endif //GTR_STRING_H