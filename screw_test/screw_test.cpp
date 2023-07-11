#include "screw_test.h"
#include "screw_date.h"
screw_test::screw_test(QWidget *parent)
{
    ui.setupUi(this);
	InitGui();
}

void screw_test::InitLocals()
{

}

void screw_test::InitGui()
{
	ui.pushButton_id->setIcon(QIcon(":Res/Icon/menu/Field-number.png"));

	ui.pushButton_getParam->setIcon(QIcon(":Res/Icon/menu/upload.png"));
	ui.pushButton_sendParam->setIcon(QIcon(":Res/Icon/menu/download.png"));

	ui.pushButton_info->setIcon(QIcon(":Res/Icon/menu/info-circle.png"));
	ui.pushButton_info->setText("");

	SelectPage(0);
}


void screw_test::SendCmd(QString& key, QString& param)
{
    new_cmd_js_.append(key + "?" + param);
}

void screw_test::fastHmiLoop()
{
	if (!isVisible())
	{
		return;
	}


}

void screw_test::SelectPage(short index)
{
	if (index < 0 || index > 6)
	{
		return;
	}

	ui.pushButton_page0->setIcon(0 == index ? QIcon(":Res/Icon/menu/detail-fill.png") : QIcon(":Res/Icon/menu/detail.png"));
	ui.pushButton_page1->setIcon(1 == index ? QIcon(":Res/Icon/menu/left-square-fill.png") : QIcon(":Res/Icon/menu/left-square.png"));
	ui.pushButton_page2->setIcon(2 == index ? QIcon(":Res/Icon/menu/down-square-fill.png") : QIcon(":Res/Icon/menu/down-square.png"));
	ui.pushButton_page3->setIcon(3 == index ? QIcon(":Res/Icon/menu/right-square-fill.png") : QIcon(":Res/Icon/menu/right-square.png"));
	ui.pushButton_page4->setIcon(4 == index ? QIcon(":Res/Icon/menu/dashboard-fill.png") : QIcon(":Res/Icon/menu/dashboard.png"));
	ui.pushButton_page5->setIcon(5 == index ? QIcon(":Res/Icon/menu/date-fill.png") : QIcon(":Res/Icon/menu/date.png"));
	//ui_.pushButton_page5->setIcon(5 == index ? QIcon(":Res/Icon/menu/robot-fill.png") : QIcon(":Res/Icon/menu/robot.png"));

	ui.stackedWidget_main->setCurrentIndex(index);
	ui.label_screwBegin_2->setPixmap(QPixmap(":Res/Icon/craft_pic/screw_little.png"));

	switch (1) {
	case 0:
		// 当 value 等于 0 时执行的操作，即 OK 的情况
		// 可以在这里编写代码来处理你想要执行的逻辑
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		// 当 value 在 1 到 6 之间（包括 1 和 6）时执行的操作，即 NG 的情况
		// 可以在这里编写代码来处理你想要执行的逻辑
		break;
	default:
		// 其他情况的处理，如果需要的话
		break;
	}
	bool isImage1 = false;
	// 根据当前状态切换图片
	if (isImage1) 
	{
		QPixmap image2(":Res/Icon/menu/screw-OK.png");
		ui.label->setPixmap(image2);
	}
	else {
		QPixmap image1(":Res/Icon/menu/screw-NG.png");
		ui.label->setPixmap(image1);
	}
}

void screw_test::fastLogicLoop()
{

}
short screw_test::afterRecvEvent(const QJsonArray& data, short channel_id/*=1*/)
{
	if (!isVisible())
	{
		return 0;
	}

	short js_num = data.size();
	for (int i = 0; i < js_num; i++)
	{
		QString temp_str = data.at(i).toString();
		if (temp_str.contains("get2303"))
		{
			QStringList ls = temp_str.split('?')[1].split(","); //分割数据
			if (ls.size() >= 31)
			{
				//转化工艺参数
				//基础参数
				short screwId = ls[0].toDouble();                 //拧紧工艺号
				double screw_pitch = ls[1].toDouble();            //螺距
				double turns_limit = ls[2].toDouble();            //极限圈数
				double max_z_distance = ls[3].toDouble();         //Z轴给进深度
				double torque_min = ls[4].toDouble();             //空转扭矩
				double torque_hold = ls[5].toDouble();            //极限扭矩
				double max_allow_time = ls[6].toDouble();         //最长允许时间
				//校准参数
				double torque_judge_time = ls[7].toDouble();      //扭矩判断时间
				double torque_hode_time = ls[8].toDouble();       //扭矩保持时间
				double torque_calibration = ls[9].toDouble();     //扭矩校准系数
				double torque_excursion = ls[10].toDouble();      //扭矩偏移系数
				//拧紧前
				double turns_before = ls[11].toDouble();          //拧前反转圈数
				double velocity_before = ls[12].toDouble();       //拧前反转速度
				//寻牙
				double torque_thread = ls[13].toDouble();         //入牙扭矩
				double turns_thread = ls[14].toDouble();          //入牙前设置的运动圈数
				bool thread_z_enable = ls[15].toDouble();         //寻牙进给允许
				//拧紧中
				double torque_eligible = ls[16].toDouble();       //合格扭矩
				double turns_lock_reversal = ls[17].toDouble();   //卡死后反转圈数
				bool screw_z_enable = ls[18].toDouble();          //拧紧进给允许
				double turns_start = ls[19].toDouble();           //开始段圈数
				double velocity_start = ls[20].toDouble();        //开始段速度
				double turns_middle = ls[21].toDouble();          //中间段圈数
				double velocity_middle = ls[22].toDouble();       //中间段速度
				double turns_eligible = ls[23].toDouble();        //合格圈数
				double velocity_end = ls[24].toDouble();          //末尾段速度
				//拧紧后
				double turns_after = ls[25].toDouble();           //拧后反转圈数
				double velocity_after = ls[26].toDouble();        //拧后反转速度
				//旋转轴驱动参数
				double current_2_torque = ls[27].toDouble();      //主轴力矩常数
				double rated_current = ls[28].toDouble();         //主轴额定电流
				double max_current = ls[29].toDouble();           //最大电流
				double velocity_maximum = ls[30].toDouble();      //最大转速

				//现实工艺参数到界面
				//基础参数
				ui.SB_screw_ID->setValue(screwId);
				ui.DSB_screw_pitch->setValue(screw_pitch);
				ui.DSB_turns_limit->setValue(turns_limit);
				ui.DSB_max_z_distance->setValue(max_z_distance);
				ui.DSB_torque_min->setValue(torque_min);
				ui.DSB_torque_hold->setValue(torque_hold);
				ui.DSB_max_allow_time->setValue(max_allow_time);
				//校准参数
				ui.DSB_torque_judge_time->setValue(torque_judge_time);
				ui.DSB_torque_hode_time->setValue(torque_hode_time);
				ui.DSB_torque_calibration->setValue(torque_calibration);
				ui.DSB_torque_excursion->setValue(torque_excursion);
				//拧紧前
				ui.DSB_turns_before_3->setValue(turns_before);
				ui.DSB_velocity_before_3->setValue(velocity_before);
				//寻牙
				ui.DSB_torque_thread_4->setValue(torque_thread);
				ui.DSB_turns_thread_4->setValue(turns_thread);
				ui.DSB_find_z_distance_on->setValue(thread_z_enable);
				//拧紧中
				ui.DSB_torque_eligible_2->setValue(torque_eligible);
				ui.DSB_lock_reversal_2->setValue(turns_lock_reversal);
				ui.DSB_mid_z_distance_on->setValue(screw_z_enable);
				ui.DSB_turns_start_2->setValue(turns_start);
				ui.DSB_velocity_start_2->setValue(velocity_start);
				ui.DSB_turns_middle_2->setValue(turns_middle);
				ui.DSB_velocity_middle_2->setValue(velocity_middle);
				ui.DSB_turns_eligible_2->setValue(turns_eligible);
				ui.DSB_velocity_end_2->setValue(velocity_end);
				//拧紧后
				ui.DSB_turns_before_4->setValue(turns_after);
				ui.DSB_velocity_before_4->setValue(velocity_after);
				//旋转轴驱动参数
				ui.DSB_current_2_torque->setValue(current_2_torque);
				ui.DSB_rated_current->setValue(rated_current);
				ui.DSB_max_current->setValue(max_current);
				ui.DSB_velocity_maximum->setValue(velocity_maximum);
			}
		}

	}
	return 0;
}

short screw_test::beforeSendEvent(const QJsonArray& data, QJsonArray& extra_data, short channel_id/*=1*/)
{
	if (!isVisible())
	{
		return 0;
	}

	extra_data = new_cmd_js_;
	new_cmd_js_ = QJsonArray();
	return 0;
}

void screw_test::on_pushButton_getParam_clicked()
{
	QString screw_ID = QString::number(ui.SB_screw_ID->value());
	QString key = "get2303";
	QString value = QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,%22,%23,%24,%25,%26,%27,%28,%29,%30,%31")
		.arg(screw_ID).arg(1).arg(2).arg(3).arg(4).arg(5).arg(6)
		.arg(7).arg(8).arg(9).arg(10).arg(11).arg(12).arg(13).arg(14).arg(15)
		.arg(16).arg(17).arg(18).arg(19).arg(20).arg(21).arg(22).arg(23).arg(24)
		.arg(25).arg(26).arg(27).arg(28).arg(29).arg(30);
	SendCmd(key, value);
}

void screw_test::on_pushButton_sendParam_clicked()
{
	//数据检查
	double max_current_my = ui.DSB_max_current->value();
	double current_2_torque_my = ui.DSB_current_2_torque->value();
	double torque_hold_my = ui.DSB_torque_hold->value();
	double torque_eligible_my = ui.DSB_torque_eligible_2->value();
	if (torque_hold_my > (max_current_my * current_2_torque_my / 1.414))
	{

		torque_hold_my = 0;
		ui.DSB_torque_hold->setValue(torque_hold_my);
	}
	if (torque_eligible_my >= torque_hold_my)
	{
		torque_eligible_my = 0;
		ui.DSB_torque_eligible_2->setValue(torque_eligible_my);
	}

	QString key = "set2303";
	//基础参数
	QString screwId = QString::number(ui.SB_screw_ID->value());
	QString screw_pitch = QString::number(ui.DSB_screw_pitch->value());
	QString turns_limit = QString::number(ui.DSB_turns_limit->value());
	QString max_z_distance = QString::number(ui.DSB_max_z_distance->value());
	QString torque_min = QString::number(ui.DSB_torque_min->value());
	QString torque_hold = QString::number(ui.DSB_torque_hold->value());
	QString max_allow_time = QString::number(ui.DSB_max_allow_time->value());
	//校准参数
	QString torque_judge_time = QString::number(ui.DSB_torque_judge_time->value());
	QString torque_hode_time = QString::number(ui.DSB_torque_hode_time->value());
	QString torque_calibration = QString::number(ui.DSB_torque_calibration->value());
	QString torque_excursion = QString::number(ui.DSB_torque_excursion->value());
	//拧紧前
	QString turns_before = QString::number(ui.DSB_turns_before_3->value());
	QString velocity_before = QString::number(ui.DSB_velocity_before_3->value());
	//寻牙
	QString torque_thread = QString::number(ui.DSB_torque_thread_4->value());
	QString turns_thread = QString::number(ui.DSB_turns_thread_4->value());
	QString thread_z_enable = QString::number(ui.DSB_mid_z_distance_on->value());
	//拧紧中
	QString torque_eligible = QString::number(ui.DSB_torque_eligible_2->value());
	QString turns_lock_reversal = QString::number(ui.DSB_lock_reversal_2->value());
	QString screw_z_enable = QString::number(ui.DSB_mid_z_distance_on->value());
	QString turns_start = QString::number(ui.DSB_turns_start_2->value());
	QString velocity_start = QString::number(ui.DSB_velocity_start_2->value());
	QString turns_middle = QString::number(ui.DSB_turns_middle_2->value());
	QString velocity_middle = QString::number(ui.DSB_velocity_middle_2->value());
	QString turns_eligible = QString::number(ui.DSB_turns_eligible_2->value());
	QString velocity_end = QString::number(ui.DSB_velocity_end_2->value());
	//拧紧后
	QString turns_after = QString::number(ui.DSB_turns_before_4->value());
	QString velocity_after = QString::number(ui.DSB_velocity_before_4->value());
	//驱动参数
	QString current_2_torque = QString::number(ui.DSB_current_2_torque->value());
	QString velocity_maximum = QString::number(ui.DSB_velocity_maximum->value());

	QString value = QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,%22,%23,%24,%25,%26,%27,%28,%29")
		.arg(screwId).arg(screw_pitch).arg(turns_limit).arg(max_z_distance).arg(torque_min)
		.arg(torque_hold).arg(max_allow_time).arg(torque_judge_time).arg(torque_hode_time)
		.arg(torque_calibration).arg(torque_excursion).arg(turns_before).arg(velocity_before)
		.arg(torque_thread).arg(turns_thread).arg(thread_z_enable).arg(torque_eligible)
		.arg(turns_lock_reversal).arg(screw_z_enable).arg(turns_start).arg(velocity_start)
		.arg(turns_middle).arg(velocity_middle).arg(turns_eligible).arg(velocity_end)
		.arg(turns_after).arg(velocity_after).arg(current_2_torque).arg(velocity_maximum);
	SendCmd(key, value);
}

screw_test::~screw_test()
{}
