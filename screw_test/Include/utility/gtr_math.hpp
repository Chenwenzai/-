#pragma once

#include <stdlib.h>
#include <math.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////
// �����
enum GtrMathOperator
{
	GTR_MATH_OPERATOR_LT,		// С��<
	GTR_MATH_OPERATOR_LE,		// С�ڵ���<=
	GTR_MATH_OPERATOR_GT,		// ����>
	GTR_MATH_OPERATOR_GE,		// ����>=
	GTR_MATH_OPERATOR_EQ,		// ����=
	GTR_MATH_OPERATOR_NEQ		// ������!=
};

//////////////////////////////////////////////////////////////////////////
// ��ѧ����

// PI
const double kPi = 3.141592653589793238462643383279;

// ���ȼ�����
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
* �ж������Ƿ�Ϊ0
* @param input ����ֵ
* @param precision_level �жϾ��ȣ���GtrPrecisionLevel����
* @return �����Ƿ����
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
* �ж��������Ƿ����
* @param input_a ����ֵa
* @param input_b ����ֵb
* @param precision_level �жϾ��ȣ���GtrPrecisionLevel����
* @return �����Ƿ����
*/
inline bool IsNumEqual(double input_a, double input_b, GtrPrecisionLevel precision_level = kPrecisionNormal)
{
	double diff = input_a - input_b;
	return IsZero(diff, precision_level);
}

/**
* ��ȡmin~max��Χ�ڵ����������
* @param min
* @param max
* @return min~max ��Χ�ڵ����������
*/
inline double GetRandBetween(const double& min, const double& max)
{
	// ������ɣ�
	// ref: https://www.runoob.com/w3cnote/cpp-rand-srand.html

	// ����Ҫ���� min��max��Դ�С
	// Q_ASSERT_X(max >= min, __FUNCTION__, "AWT Fatal Error: max value is lesser than value!");

	double seed = rand() / double(RAND_MAX);	// ��ȡ0~1֮�����������
	return 	seed * (max - min) + min;
}

/**
* ��ȡmin~max��Χ�ڵ��������
* @param min
* @param max
* @return min~max ��Χ�ڵ��������
*/
inline int GetRandIntBetween(const int& min, const int& max)
{
	// ȡ��[min, max] ���������
	return (rand() % (max - min + 1)) + min;
}

/**
* ���ݸ������I/O���
* @param probability ���ʣ�%��
* @return ���ݸ������0��1
*/
inline bool IoFromProbability(const double probability)
{
	double seed = GetRandBetween(0, 100);
	return probability >= seed;
}

/**
* ��ȡ����ֵ
* @param time ʱ�䣨��λms��
* @param amplitude ���
* @param frequency Ƶ�ʣ���λHz��
* @param time_shift ʱ���ͺ󣨵�λms��
* @return amplitude * sin(2 * pi * frequency * (time + time_shift))
*/
inline double GetSineOfTime(const double time, const double& amplitude, const double& frequency, const double& time_shift)
{
	return amplitude * sin(2 * kPi * frequency * (time + time_shift) / 1000.0);
}

/**
* ���ô��м�ֵ�Ĳ���
* @param input	����ֵ
* @param min
* @param max
* @param<output> ����ڷ�Χ�ڵ�����
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
	long size;		//����
	double min;		//��Сֵ
	double max;		//���ֵ
	double range;	//���ֵ
	double sum;		//���ݺ�
	double mean;	//ƽ��ֵ
	double std_dev;	//��׼��

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