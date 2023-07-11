// PLC Standard Function library
// 注意：所有函数如TOF、R_TRIG均为PLC（VPL language）标准语言
// ref:http://www.logicio.com/HTML/

#pragma once
#ifndef GTR_TRIGGER_HPP
#define GTR_TRIGGER_HPP

#include <QTime>

class GtrTrigger
{
public:
	/**
	* 构造函数
	* @param input_value 输入信号，默认使用0作为初始值
	*/
	GtrTrigger(const bool& input_value = 0)
	{
		local_value_ = input_value;
		local_timer_.start();
	}

	//////////////////////////////////////////////////////////////////////////
	// 沿触发函数

	/**
	* 上升沿函数 (R = rise)
	* @param input_value 输入信号
	* @return 若输入为0->1, 返回1; 否则返回0
	*/
	bool R_TRIG(const bool& input_value)
	{
		if (!local_value_ && input_value)
		{
			local_value_ = input_value;
			return 1;
		}
		else
		{
			local_value_ = input_value;
			return 0;
		}
	}

	/**
	* 下降沿函数 (F = fall)
	* @param input_value 输入信号
	* @return 若输入为1->0, 返回1; 否则返回0
	*/
	bool F_TRIG(const bool& input_value)
	{
		if (local_value_ && !input_value)
		{
			local_value_ = input_value;
			return 1;
		}
		else
		{
			local_value_ = input_value;
			return 0;
		}
	}

	/**
	* “非”函数 (DIF = different)
	* @param input_value 输入信号
	* @return 若输入与上次调用时不同, 返回1; 否则返回0
	*/
	bool DIF_TRIG(const bool& input_value)
	{
		if (local_value_ != input_value)
		{
			local_value_ = input_value;
			return 1;
		}
		else
		{
			return 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// timer function 时间相关函数

	/**
	* 高平滤波函数 (T = time, ON = ON/TRUE)
	* @param input_value 输入信号
	* @param continous_time 持续时间，单位为ms
	* @return 若输入为1, 且持续了指定时间，返回1; 否则返回0
	*/
	bool TON(const bool& input_value, const long& continous_time)
	{
		local_value_ = input_value;
		if (!local_value_)
		{
			local_timer_.restart();
		}

		if (local_timer_.elapsed() > continous_time)
		{
			return 1;
		}

		return 0;
	}

	/**
	* 低平滤波函数 (T = time, OF = OFF/FALSE)
	* @param input_value 输入信号
	* @param continous_time 持续时间，单位为ms
	* @return 若输入为0, 且持续了指定时间，返回1; 否则返回0
	*/
	bool TOF(const bool& input_value, const long& continous_time)
	{
		local_value_ = input_value;
		if (local_value_)
		{
			local_timer_.restart();
		}

		if (local_timer_.elapsed() > continous_time)
		{
			return 1;
		}

		return 0;
	}

	/**
	* 脉冲延时函数 (T = time, P = pulse)
	* ref: http://www.logicio.com/HTML/
	* @param input_value 输入信号
	* @param continous_time 持续时间，单位为ms
	* @return 若捕获脉冲（信号上升沿）, 则持续返回1指定时间后，返回0; 否则返回0
	*/
	bool TP(const bool& input_value, const long& continous_time)
	{
		int time_elapsed = local_timer_.elapsed();

		// 捕获到【新的】脉冲信号
		if (time_elapsed >= continous_time &&	// 时间已超过continous_time
			!local_value_ && input_value)		// 上升沿
		{
			local_timer_.restart();
		}

		if (time_elapsed < continous_time)
		{
			return 1;
		}

		return 0;
	}

public:
	/**
	* 设置内部值（一般用于初始化）
	* @param input_value 输入信号
	*/
	void SetValue(const bool& input_value)
	{
		local_value_ = input_value;
	}

	/**
	* 清零内部值
	*/
	void Reset()
	{
		local_value_ = 0;
		local_timer_.restart();
	}

private:
	bool local_value_;
	QTime local_timer_;
};

#endif // GTR_TRIGGER_HPP