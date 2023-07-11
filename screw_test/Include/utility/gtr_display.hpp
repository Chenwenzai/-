#pragma once

#ifndef GTR_DISPLAY_H
#define GTR_DISPLAY_H

#include <QtCore>
#include <QWidget>
#include <QLCDNumber>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>

#include "gtr_math.hpp"

class GtrDisplay
{
public:
	GtrDisplay::GtrDisplay(QLabel* input_object, short input_precision = 1)
	{
		InitLocals();
		p_object_label_ = input_object;
		SetPrecision(input_precision);
	}

	GtrDisplay::GtrDisplay(QLCDNumber* input_object, short input_precision = 1)
	{
		InitLocals();
		p_object_lcd_ = input_object;
		SetPrecision(input_precision);
	}

	GtrDisplay::GtrDisplay(QDoubleSpinBox* input_object, short input_precision = 1)
	{
		InitLocals();
		p_object_double_spinbox_ = input_object;
		SetPrecision(input_precision);
	}

	GtrDisplay::GtrDisplay(QSpinBox* input_object)
	{
		InitLocals();
		p_object_spinbox_ = input_object;
	}

	~GtrDisplay() {};

private:
	void InitLocals()
	{
		p_object_lcd_ = NULL;
		p_object_double_spinbox_ = NULL;
		p_object_spinbox_ = NULL;
		p_object_label_ = NULL;
		display_value_ = DBL_MIN;
		double_precision_ = 1;
	}

public:
	void SetPrecision(short input_precision)
	{
		double_precision_ = input_precision;
	}
	void SetDoubleValue(double input_value, bool force_set = false)
	{
		if (p_object_label_)
		{
			if (!IsNumEqual(display_value_, input_value, kPrecisionFine))
			{
				display_value_ = input_value;
				p_object_label_->setText(QString::number(display_value_, 'f', double_precision_));
			}
			return;
		}
		else if (p_object_lcd_)
		{
			if (!IsNumEqual(display_value_, input_value, kPrecisionFine))
			{
				display_value_ = input_value;
				p_object_lcd_->display(QString::number(display_value_, 'f', double_precision_));
			}
			return;
		}

		else if (p_object_double_spinbox_)
		{
			if (!IsNumEqual(display_value_, input_value, kPrecisionFine))
			{
				display_value_ = input_value;
				p_object_double_spinbox_->setValue(display_value_);
			}
			return;
		}

		else if (p_object_spinbox_)
		{
			if (!IsNumEqual(display_value_, input_value, kPrecisionFine))
			{
				display_value_ = input_value;
				p_object_spinbox_->setValue(display_value_);
			}
			return;
		}
		return;	
	}

private:
	QLabel* p_object_label_;
	QLCDNumber* p_object_lcd_;
	QDoubleSpinBox* p_object_double_spinbox_;
	QSpinBox* p_object_spinbox_;
	double display_value_;
	short double_precision_;
};

//void SetLabelColor(QLabel* p_object, bool is_true, bool is_false_and_no_color=1, bool is_true_and_green=1);
//void SetPushButtonColor(QPushButton* p_object, bool is_true, bool is_false_and_no_color=1, bool is_true_and_green=1);

// has a maximum number of 5 colors
//enum GtrLabelColor
//{
//	GTR_COLOR_NULL = 0,
//	GTR_COLOR_GREEN = 1,
//	GTR_COLOR_YELLOW = 2,
//	GTR_COLOR_RED = 3,
//};

//class GtrQtColoredObject
//{
//public:
//	GtrQtColoredObject();
//	~GtrQtColoredObject();
//	void SetObject(QLabel* input_object);
//	void SetObject(QPushButton* input_object);
//	void SetColor(short input_value, GtrLabelColor display_color);
//	void SetValue(short input_value, bool force_set=false);
//	short GetValue();
//
//private:
//	QLabel* p_object_label_;
//	QPushButton* p_object_pushButton_;
//	short object_value_;
//	GtrLabelColor color_for_value_neg_1_;
//	GtrLabelColor color_for_value_0_;
//	GtrLabelColor color_for_value_1_;
//	GtrLabelColor color_for_value_2_;
//	GtrLabelColor color_for_value_3_;
//};

//void SetLabelColor(QLabel* p_object, bool is_true, bool is_false_and_no_color, bool is_true_and_green)
//{
//	if (1 == is_true)
//	{
//		if (is_true_and_green)
//		{
//			p_object->setStyleSheet("background-color:#00c957;");
//		}
//		else
//		{
//			p_object->setStyleSheet("background-color:rgb(255,0,0);");
//		}
//
//	}
//	else
//	{
//		if (is_false_and_no_color)
//		{
//			p_object->setStyleSheet("background-color:;");
//		}
//		else
//		{
//			p_object->setStyleSheet("background-color:rgb(255,0,0);");
//		}
//	}
//}
//
//void SetPushButtonColor(QPushButton* p_object, bool is_true, bool is_false_and_no_color, bool is_true_and_green)
//{
//	if (1 == is_true)
//	{
//		if (is_true_and_green)
//		{
//			p_object->setStyleSheet("background-color:#00c957;");
//		}
//		else
//		{
//			p_object->setStyleSheet("background-color:rgb(255,0,0);");
//		}
//
//	}
//	else
//	{
//		if (is_false_and_no_color)
//		{
//			p_object->setStyleSheet("background-color:;");
//		}
//		else
//		{
//			p_object->setStyleSheet("background-color:rgb(255,0,0);");
//		}
//	}
//}


//GtrQtColoredObject::GtrQtColoredObject()
//{
//	p_object_label_ = NULL;
//	p_object_pushButton_ = NULL;
//
//	object_value_ = 0;
//
//	// default: value_neg_1 = red color
//	color_for_value_neg_1_ = GTR_COLOR_RED;
//
//	// default: value_0 = no color
//	color_for_value_0_ = GTR_COLOR_NULL;
//
//	// default: value_1 = green color
//	color_for_value_1_ = GTR_COLOR_GREEN;
//
//	// default: value_2, 3 = no color
//	color_for_value_2_ = GTR_COLOR_NULL;
//	color_for_value_3_ = GTR_COLOR_NULL;
//
//}
//
//GtrQtColoredObject::~GtrQtColoredObject()
//{
//	p_object_label_ = NULL;
//	p_object_pushButton_ = NULL;
//}
//
//void GtrQtColoredObject::SetObject(QLabel* input_object)
//{
//	p_object_label_ = input_object;
//
//	// display something
//	object_value_ = 0;
//	p_object_label_->setProperty("status","");
//}
//
//void GtrQtColoredObject::SetObject(QPushButton* input_object)
//{
//	p_object_pushButton_ = input_object;
//
//	// display something
//	object_value_ = 0;
//	p_object_pushButton_->setProperty("type","craftStatus_gray");
//}
//
//void GtrQtColoredObject::SetColor(short input_value, GtrLabelColor display_color)
//{
//	switch(input_value)
//	{
//	case -1:
//		color_for_value_neg_1_ = display_color;
//		break;
//
//	case 0:
//		color_for_value_0_ = display_color;
//		break;
//
//	case 1:
//		color_for_value_1_ = display_color;
//		break;
//
//	case 2:
//		color_for_value_2_ = display_color;
//		break;
//
//	case 3:
//		color_for_value_3_ = display_color;
//		break;
//
//	default:
//		break;
//	}
//
//	// make this color effective
//	SetValue(object_value_,true);
//}
//
//void GtrQtColoredObject::SetValue(short input_value, bool force_set/*=false*/)
//{
//	if (force_set||(input_value != object_value_))
//	{
//		if (NULL!=p_object_label_)
//		{
//			p_object_label_->style()->unpolish(p_object_label_);
//		}
//		if (NULL!=p_object_pushButton_)
//		{
//			p_object_pushButton_->style()->unpolish(p_object_pushButton_);
//		}
//
//		object_value_ = input_value;
//		short color_output = 0;
//		switch (input_value)
//		{
//		case -1:
//			color_output = color_for_value_neg_1_;
//			break;
//		case 0:
//			color_output = color_for_value_0_;
//			break;
//		case 1:
//			color_output = color_for_value_1_;
//			break;
//		case 2:
//			color_output = color_for_value_2_;
//			break;
//		case 3:
//			color_output = color_for_value_3_;
//			break;
//		}
//
//		switch(color_output)
//		{
//		case GTR_COLOR_NULL:
//			if (NULL!=p_object_label_)
//			{
//				//p_object_label_->setStyleSheet("background-color:;");
//				p_object_label_->setProperty("status","");
//			}
//			if (NULL!=p_object_pushButton_)
//			{
//				p_object_pushButton_->setProperty("type","craftStatus_gray");
//			}
//			break;
//
//		case GTR_COLOR_GREEN:
//			if (NULL!=p_object_label_)
//			{
//				p_object_label_->setProperty("status","green");
//			}
//			if (NULL!=p_object_pushButton_)
//			{
//				p_object_pushButton_->setProperty("type","craftStatus_green");
//			}
//			break;
//
//		case GTR_COLOR_RED:
//			if (NULL!=p_object_label_)
//			{
//				p_object_label_->setProperty("status","red");
//			}
//			if (NULL!=p_object_pushButton_)
//			{
//				p_object_pushButton_->setProperty("type","craftStatus_red");
//			}
//			break;
//
//		case GTR_COLOR_YELLOW:
//			if (NULL!=p_object_label_)
//			{
//				p_object_label_->setProperty("status","orange");
//			}
//			if (NULL!=p_object_pushButton_)
//			{
//				p_object_pushButton_->setProperty("type","craftStatus_orange");
//			}
//			break;
//
//		default:
//			return;
//		}
//
//		if (NULL!=p_object_label_)
//		{
//			p_object_label_->style()->polish(p_object_label_);
//			p_object_label_->update();
//		}
//
//		if (NULL!=p_object_pushButton_)
//		{
//			p_object_pushButton_->style()->polish(p_object_pushButton_);
//		}
//	}
//
//}
//
//short GtrQtColoredObject::GetValue()
//{
//	return object_value_;
//}

#endif //GTR_DISPLAY_H