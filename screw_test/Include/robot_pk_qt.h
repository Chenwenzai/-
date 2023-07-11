#pragma once

#define TCP_CMD_VERSION "3.8.7.1"

#include "windows.h"

#include <QtCore>
#include <QObject>

// 本地调试
#include <QDebug>
#include <QString>

// 文件IO
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

// JSON解析
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

// 计时
#include <QTimer>
#include <QDateTime>

// 容器
#include <QVector>
#include <QList>
#include <QHash>

// 交互用控件
#include <QWidget>
#include <QStyle>
#include <QLabel>
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include <QTextBrowser>
#include <QPushButton>
#include <QToolButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>

#include <QGroupBox>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpacerItem>
#include <QDockWidget>
#include <QScrollArea>
#include <QTabWidget>
#include <QTableWidget>


// 解决中文乱码问题
#include <QTextCodec>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#pragma execution_character_set("utf-8")
#endif

// 标准插件接口
#include "robot_pk_app_interface.h"
#include "gtrobot_backend_define.h"

// 通道数量
#define ROBOT_PK_MAX_CH_NUM	2

// 工具
#include "utility/gtr_load_api.h"

#include "utility/gtr_math.hpp"
#include "utility/gtr_precise_thread.hpp"
#include "utility/gtr_string.hpp"
#include "utility/gtr_trigger.hpp"
#include "utility/gtr_display.hpp"
#include "utility/gtr_version.hpp"
