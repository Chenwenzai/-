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

// �ӻ�����ϵͳGtAppFrameInterface�̳�
public: 
	virtual QString getFrameName() { return ""; }		///< ��ȡ����
	virtual void setPermission(short type) { return; }	///< ����Ȩ��
	virtual void fastHmiLoop() { return; }				///< ��������
	virtual void fastLogicLoop() { return; }			///< �߼�����

// RobotPK �����ӿ�
public:
	virtual QIcon getIcon() { return QIcon(); }
	virtual QString getToolTip() { return QString(); }

	/**
	 * @brief		�¼�-����ͨ������ǰ
	 * @param[in]	data �����͵�����
	 * @param[out]	extra_data ���ӵ�����
	 * @param[in]	channel_id ͨ����, ��1��ʼ������ͬ������ʾ��
	 * @return		0 ����0��ʾ����
	 */
	virtual short beforeSendEvent(const QJsonArray& data, QJsonArray& extra_data, short channel_id=1) { return 0; };

	/**
	 * @brief		�¼�-����ͨ�����ݺ�
	 * @param[in]	data �ѷ��͵�����
	 * @param[in]	channel_id ͨ����, ��1��ʼ������ͬ������ʾ��
	 * @return		0 ����0��ʾ����
	 */
	virtual short afterSendEvent(const QJsonArray& data, short channel_id=1) { return 0; };

	/**
	 * @brief		�¼�-����ͨ�����ݺ�
	 * @param[in]	data ���յ�������
	 * @param[in]	channel_id ͨ����, ��1��ʼ������ͬ������ʾ��
	 * @return		0 ����0��ʾ���� 
	 */
	virtual short afterRecvEvent(const QJsonArray& data, short channel_id=1) { return 0; };	

	/**
	 * @brief		�¼�-APP֮��ͨ���ź�
	 * @param[in]	input ��������
	 * @param[out]	output ���ص�����
	 * @param[in]	src_id ����ԴID
	 * @return		0 ����0��ʾ����
	 */
	virtual short interAppCallEvent(const QJsonArray& input, QJsonArray& output, short src_id) { return 0; };


	};

QT_BEGIN_NAMESPACE
#define ROBOT_PK_APP_INTERFACE_IID "robot.pk.app.interface"
Q_DECLARE_INTERFACE(RobotPkAppInterface, ROBOT_PK_APP_INTERFACE_IID);
QT_END_NAMESPACE

