#pragma once

#include <QString>
#include <QWidget>
#include <QIcon>
#include <QJsonObject>
#include <QJsonArray>
#include <QtPlugin>

#include "gtappframeinterface.h"

class RobotPkAppInterface: public GtAppFrameInterface
{

public:
	virtual ~RobotPkAppInterface() {}

// 从机器人系统GtAppFrameInterface继承
public: 
	virtual QString getFrameName() { return ""; }		///< 获取名称
	virtual void setPermission(short type) { return; }	///< 设置权限
	virtual void fastHmiLoop() { return; }				///< 界面周期
	virtual void fastLogicLoop() { return; }			///< 逻辑周期

// RobotPK 新增接口
public:
	virtual QIcon getIcon() { return QIcon(); }
	virtual QString getToolTip() { return QString(); }

	/**
	 * @brief		事件-发送通信数据前
	 * @param[in]	data 待发送的数据
	 * @param[out]	extra_data 附加的数据
	 * @param[in]	channel_id 通道号, 从1开始计数（同界面显示）
	 * @return		0 返回0表示正常
	 */
	virtual short beforeSendEvent(const QJsonArray& data, QJsonArray& extra_data, short channel_id=1) { return 0; };

	/**
	 * @brief		事件-发送通信数据后
	 * @param[in]	data 已发送的数据
	 * @param[in]	channel_id 通道号, 从1开始计数（同界面显示）
	 * @return		0 返回0表示正常
	 */
	virtual short afterSendEvent(const QJsonArray& data, short channel_id=1) { return 0; };

	/**
	 * @brief		事件-接收通信数据后
	 * @param[in]	data 接收到的数据
	 * @param[in]	channel_id 通道号, 从1开始计数（同界面显示）
	 * @return		0 返回0表示正常 
	 */
	virtual short afterRecvEvent(const QJsonArray& data, short channel_id=1) { return 0; };	

	/**
	 * @brief		事件-APP之间通信信号
	 * @param[in]	input 接受数据
	 * @param[out]	output 返回的数据
	 * @param[in]	src_id 数据源ID
	 * @return		0 返回0表示正常
	 */
	virtual short interAppCallEvent(const QJsonArray& input, QJsonArray& output, short src_id) { return 0; };


	};

QT_BEGIN_NAMESPACE
#define ROBOT_PK_APP_INTERFACE_IID "robot.pk.app.interface"
Q_DECLARE_INTERFACE(RobotPkAppInterface, ROBOT_PK_APP_INTERFACE_IID);
QT_END_NAMESPACE

