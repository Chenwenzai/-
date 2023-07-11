#pragma once

#include <QtCore>
#include <QThread>
#include <QTimer>
#include <QDateTime>

class GtrPreciseThread : public QThread
{
	Q_OBJECT

public:
	// �����߳����ڣ�ms��
	void SetLoopTime(int loop_time_ms)
	{
		loop_time_ms_ = loop_time_ms;
	}

	void Restart(int loop_time_ms)
	{
		loop_time_ms_ = loop_time_ms;
		quit();
		wait();
		start();
	}

	// ��ȡ�߳�ƽ�����ڣ�ms��ÿ3000msͳ��һ�Σ�����-1��ʾ����
	double GetMeanLoopTime()
	{
		// ��ƽ��������Ȼ���ں������ֵ��60�룩
		if (mean_loop_time_ms_ > 60000 || mean_loop_time_ms_ < 0)
		{
			return -1;
		}

		return mean_loop_time_ms_;
	}

protected:
	void run()
	{
		p_timer_ = new QTimer(this); // �����ڴ˴������߳��У�new�������ڹ��캯����new
		p_timer_->setTimerType(Qt::PreciseTimer);
		connect(p_timer_, SIGNAL(timeout()), this, SLOT(LocalTimeout()));
		p_timer_->start(loop_time_ms_);
		exec();
	}

private slots:
	void LocalTimeout()
	{
		loop_time_this = QDateTime::currentMSecsSinceEpoch();
		loop_passed_time = loop_time_this - loop_time_last;
		loop_counter_this++;

		if (loop_passed_time > 3000) // ÿ3000msͳ��һ��
		{
			mean_loop_time_ms_ = 1.0 * loop_passed_time / (loop_counter_this - loop_counter_last);
			loop_time_last = loop_time_this;
			loop_counter_last = loop_counter_this;
		}

		emit LoopRun();
	}

signals:
	void LoopRun();

private:
	QTimer* p_timer_ = NULL;
	int loop_time_ms_ = 5;

	// �����ٶ�ͳ��
	qint64 loop_counter_this = 0;
	qint64 loop_counter_last = 0;
	qint64 loop_time_this = 0;
	qint64 loop_time_last = 0;
	qint64 loop_passed_time = 0;
	double mean_loop_time_ms_ = 0;
};