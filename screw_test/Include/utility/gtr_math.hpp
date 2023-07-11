#pragma once

#include <stdlib.h>
#include <math.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////
// 运算符
enum GtrMathOperator
{
	GTR_MATH_OPERATOR_LT,		// 小于<
	GTR_MATH_OPERATOR_LE,		// 小于等于<=
	GTR_MATH_OPERATOR_GT,		// 大于>
	GTR_MATH_OPERATOR_GE,		// 大于>=
	GTR_MATH_OPERATOR_EQ,		// 等于=
	GTR_MATH_OPERATOR_NEQ		// 不等于!=
};

//////////////////////////////////////////////////////////////////////////
// 数学常量

// PI
const double kPi = 3.141592653589793238462643383279;

// 精度级别定义
enum GtrPrecisionLevel
{
	kPrecisionUltraFine,
	kPrecisionSuperFine,
	kPrecisionFine,
	kPrecisionNormal,
	kPrecisionRough,
	kPrecisionSuperRough,
	kPrecisionUltraRough,
};
const double kEpsilonOfUltraFine = 1e-4;
const double kEpsilonOfSuperFine = 1e-3;
const double kEpsilonOfFine = 1e-2;
const double kEpsilonOfNormal = 1e-1;
const double kEpsilonOfRough = 1;
const double kEpsilonOfSuperRough = 5;
const double kEpsilonOfUltraRough = 10;

/**
* 判断数字是否为0
* @param input 输入值
* @param precision_level 判断精度，由GtrPrecisionLevel定义
* @return 返回是否相等
*/
inline bool IsZero(double input, GtrPrecisionLevel precision_level = kPrecisionNormal)
{
	double kEpsilon;
	switch (precision_level)
	{
	case kPrecisionUltraFine:
	{
		kEpsilon = kEpsilonOfUltraFine;
		break;
	}
	case kPrecisionSuperFine:
	{
		kEpsilon = kEpsilonOfSuperFine;
		break;
	}
	case kPrecisionFine:
	{
		kEpsilon = kEpsilonOfFine;
		break;
	}
	case kPrecisionNormal:
	{
		kEpsilon = kEpsilonOfNormal;
		break;
	}
	case kPrecisionRough:
	{
		kEpsilon = kEpsilonOfRough;
		break;
	}
	case kPrecisionSuperRough:
	{
		kEpsilon = kEpsilonOfSuperRough;
		break;
	}
	case kPrecisionUltraRough:
	{
		kEpsilon = kEpsilonOfUltraRough;
		break;
	}
	default:
		kEpsilon = kEpsilonOfNormal;
		break;
	}

	return (input > 0) ? input<kEpsilon : input>-kEpsilon;
}

/**
* 判断两数字是否相等
* @param input_a 输入值a
* @param input_b 输入值b
* @param precision_level 判断精度，由GtrPrecisionLevel定义
* @return 返回是否相等
*/
inline bool IsNumEqual(double input_a, double input_b, GtrPrecisionLevel precision_level = kPrecisionNormal)
{
	double diff = input_a - input_b;
	return IsZero(diff, precision_level);
}

/**
* 获取min~max范围内的随机浮点数
* @param min
* @param max
* @return min~max 范围内的随机浮点数
*/
inline double GetRandBetween(const double& min, const double& max)
{
	// 随机生成：
	// ref: https://www.runoob.com/w3cnote/cpp-rand-srand.html

	// 不需要考虑 min、max相对大小
	// Q_ASSERT_X(max >= min, __FUNCTION__, "AWT Fatal Error: max value is lesser than value!");

	double seed = rand() / double(RAND_MAX);	// 获取0~1之间随机浮点数
	return 	seed * (max - min) + min;
}

/**
* 获取min~max范围内的随机整数
* @param min
* @param max
* @return min~max 范围内的随机整数
*/
inline int GetRandIntBetween(const int& min, const int& max)
{
	// 取得[min, max] 的随机整数
	return (rand() % (max - min + 1)) + min;
}

/**
* 根据概率输出I/O结果
* @param probability 概率（%）
* @return 根据概率输出0或1
*/
inline bool IoFromProbability(const double probability)
{
	double seed = GetRandBetween(0, 100);
	return probability >= seed;
}

/**
* 获取正弦值
* @param time 时间（单位ms）
* @param amplitude 振幅
* @param frequency 频率（单位Hz）
* @param time_shift 时间滞后（单位ms）
* @return amplitude * sin(2 * pi * frequency * (time + time_shift))
*/
inline double GetSineOfTime(const double time, const double& amplitude, const double& frequency, const double& time_shift)
{
	return amplitude * sin(2 * kPi * frequency * (time + time_shift) / 1000.0);
}

/**
* 设置带有极值的参数
* @param input	输入值
* @param min
* @param max
* @param<output> 输出在范围内的数字
*/
template <typename T>
void SetValueWithLimit(T& output, const T& input, const T& min, const T& max)
{
	if (input > max)
	{
		output = max;
	}
	else if (input < min)
	{
		output = min;
	}
	else
	{
		output = input;
	}
}

struct StatsValue
{
	long size;		//数量
	double min;		//最小值
	double max;		//最大值
	double range;	//峰峰值
	double sum;		//数据和
	double mean;	//平均值
	double std_dev;	//标准差

	StatsValue()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(StatsValue));
	}
};

class StatsComputer
{
public:
	StatsComputer()
	{
		Clear();
	}

	void AddData(double value)
	{
		vec_data_.push_back(value);
		stats_.size++;
		stats_.sum += value;
		stats_.mean = stats_.size ? stats_.sum / stats_.size : 0;

		if (1 == stats_.size)
		{
			stats_.max = value;
			stats_.min = value;
			stats_.range = 0;
			return;
		}
		
		if (value > stats_.max)
		{
			stats_.max = value;
		}
		else if (value < stats_.min)
		{
			stats_.min = value;
		}
		stats_.range = stats_.max - stats_.min;
	}

	StatsValue GetStats()
	{
		if (0 != ComputeStats())
		{
			stats_.Clear();
		}
		return stats_;
	}

	void Clear()
	{
		vec_data_.clear();
		stats_.Clear();
	}

private:
	// return 0 if successful
	short ComputeStats()
	{
		if (0 == stats_.size)
		{
			return -1;
		}

		double sqrt_diff_sum = 0;
		for (int i = 0; i < stats_.size; i++)
		{
			double temp_value = vec_data_[i];
			sqrt_diff_sum += (temp_value - stats_.mean) * (temp_value - stats_.mean);
		}

		stats_.std_dev = sqrt(sqrt_diff_sum / stats_.size);
		return 0;
	}

private:
	std::vector<double> vec_data_;
	StatsValue stats_;
};