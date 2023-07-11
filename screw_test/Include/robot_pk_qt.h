#pragma once

#define TCP_CMD_VERSION "3.8.7.1"

#include "windows.h"

#include <QtCore>
#include <QObject>

// ���ص���
#include <QDebug>
#include <QString>

// �ļ�IO
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

// JSON����
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

// ��ʱ
#include <QTimer>
#include <QDateTime>

// ����
#include <QVector>
#include <QList>
#include <QHash>

// �����ÿؼ�
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


// ���������������
#include <QTextCodec>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#pragma execution_character_set("utf-8")
#endif

// ��׼����ӿ�
#include "robot_pk_app_interface.h"
#include "gtrobot_backend_define.h"

// ͨ������
#define ROBOT_PK_MAX_CH_NUM	2

// ����
#include "utility/gtr_load_api.h"

#include "utility/gtr_math.hpp"
#include "utility/gtr_precise_thread.hpp"
#include "utility/gtr_string.hpp"
#include "utility/gtr_trigger.hpp"
#include "utility/gtr_display.hpp"
#include "utility/gtr_version.hpp"
