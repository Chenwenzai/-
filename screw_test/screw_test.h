#pragma once

#include <QtWidgets/QWidget>
#include "ui_screw_test.h"
#include "./Include/robot_pk_qt.h"

class screw_test : public RobotPkAppInterface
{
    Q_OBJECT
        Q_INTERFACES(RobotPkAppInterface)
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
        Q_PLUGIN_METADATA(IID ROBOT_PK_APP_INTERFACE_IID)
#endif

public:
    screw_test(QWidget *parent = nullptr);
    ~screw_test();

public:
    QString getFrameName() { return "工艺"; }
    QIcon getIcon() { return QIcon(":/Res/Icon/iconfont/wrench.png"); }
    QString getToolTip() { return "工艺"; }

	void SelectPage(short index);
private:
    void InitLocals();
    void InitGui();

public slots:
	void on_pushButton_page0_clicked() { SelectPage(0); }
	void on_pushButton_page1_clicked() { SelectPage(1); }
	void on_pushButton_page2_clicked() { SelectPage(2); }
	void on_pushButton_page3_clicked() { SelectPage(3); }
	void on_pushButton_page4_clicked() { SelectPage(4); }
	void on_pushButton_page5_clicked() { SelectPage(5); }

    void on_pushButton_getParam_clicked();
    void on_pushButton_sendParam_clicked();


private:
    void SendCmd(QString& key, QString& param);

public:
    void fastHmiLoop();  //界面显示节拍
    void fastLogicLoop();  //逻辑节拍

public:
    short afterRecvEvent(const QJsonArray& data, short channel_id = 1);
    short beforeSendEvent(const QJsonArray& data, QJsonArray& extra_data, short channel_id = 1);


private:
    Ui::screw_testClass ui;
    QJsonArray new_cmd_js_;
};
