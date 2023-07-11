#ifndef GTAPPFRAMEINTERFACE_H
#define GTAPPFRAMEINTERFACE_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QtPlugin>

struct AppUserComParam
{
	short channel_index;
	short user_id;			//对应USER指令参数：ID
	long  long_param[4];	//对应USER指令参数：L1、L2、L3、L4
	double double_param[4]; //对应USER指令参数：D1、D2、D3、D4
};


/**
 * @brief			用户（工艺）界面插件接口
 * @note			用户创建工艺界面插件时，需继承GtAppFrameInterface
 * @note 			在插件指令实现的末尾，需要标注插件密钥以及用户插件的名称
 * @example  	class UserHmi: public GtAppFrameInterface
							{
								Q_OBJECT
									Q_INTERFACES(GtAppFrameInterface)

								......

							public:
								QString getFrameName();
								QString getVersion();
								void FastTimerLoop();

								......
							}

							.....

							QString UserHmi::getVersion()
							{
								return "v1.0";
							}

							void UserHmi::FastTimerLoop()
							{
								// do something
							}

							......

							// 标注插件密钥（“RobotHmi”）以及用户插件的名称（UserDllName）
							Q_EXPORT_PLUGIN2("RobotHmi", UserDllName);
 */
class GtAppFrameInterface : public QWidget
{

public:
	virtual ~GtAppFrameInterface() {}

	/**
	 * @brief		获取界面的名称
	 * @param[in]	<void>
	 * @return		<QString> 用户返回的界面名称
	 * @note		界面名称将用于日志的记录
	 */
	virtual QString getFrameName() = 0;

	/**
	 * @brief		获取界面的版本信息
	 * @param[in]	<void>
	 * @return		<QString> 用户返回的版本信息
	 * @note		版本信息将用于版本检查
	 */
	virtual QString getVersion() { return ""; }


	/**
	 * @brief		插件初始化函数
	 * @param[in]	<void>
	 * @return 		<void>
	 * @note		此函数只在系统初始化时调用一次
	 */
	virtual void Init() { return; }

	/**
	 * @brief		插件结束函数
	 * @param[in]	<void>
	 * @return 		<void>
	 * @note		此函数只在系统退出前调用一次
	 */
	virtual void Exit() { return; }

	/**
	 * @brief		主框架界面定周期调用该函数（高频率，约100ms~120ms调用一次）
	 * @param[in]	<void>
	 * @return 		<void>
	 * @note		用户需保证，该函数单次调用时间不能过长，且无死循环
	 */
	virtual void fastHmiLoop() {}

	/**
	 * @brief		主框架界面定周期调用该函数（低频率，约1000ms调用一次）
	 * @param[in]	<void>
	 * @return 		<void>
	 * @note		用户需保证，该函数单次调用时间不能过长，且无死循环
	 */
	virtual void slowHmiLoop() {}

	/**
	 * @brief		机器人系统PLC线程周期调用该函数（高频率，约10ms调用一次）
	 * @param[in]	<void>
	 * @return 		<void>
	 * @note		用户需保证，该函数单次调用时间不能过长，且无死循环
	 */
	virtual void fastLogicLoop() {}

	/**
	 * @brief		机器人系统NC线程周期调用该函数（高频率，约20ms调用一次）
	 * @param[in]	<void>
	 * @return 		<void>
	 * @note		用户需保证，该函数单次调用时间不能过长，且无死循环
	 */
	virtual void slowLogicLoop() {}

	/**
	 * @brief		机器人系统USER示教指令的具体实现
	 * @param[in]	const AppUserComParam &param：机器人系统执行至USER示教指令时的参数列表
	 * @param[in]	const bool &first：若首次执行至USER示教指令，则first = true;
	 * @return 		<0>：执行结束。
	 * @return 		<1>：执行未结束。机器人系统将再次执行USER指令。
	 * @return 		<2>：执行错误。机器人系统将出现报警。
	 * @note		用户也可通过后端接口GTR_RegisterUserCom注册USER指令的具体实现内容。
	 */
	virtual short userComLoopRun(const AppUserComParam& param, const bool& first) { return 0; }

	/**
	 * @brief		读入界面的上一次状态
	 * @param[in]	<void>
	 * @return 		<bool> 返回true表示执行正常
	 * @note		内部接口，调用showFrame()函数前自动调用
	 */
	virtual bool readLastTimeStatus() { return false; }

	/**
	* @brief		保存界面的现场状态
	* @param[in]	<void>
	* @return 		<bool> 返回true表示执行正常
	* @note		内部接口，调用showFrame()函数后自动调用
	*/
	virtual bool saveLastTimeStatus() { return false; }

	/**
	 * @brief		显示界面
	 * @param[in]	<void>
	 * @return 		<bool> 返回true表示执行正常
	 * @note		显示界面，并激活界面定时器与读写操作
	 */
	virtual bool showFrame() { return true; }

	/**
	 * @brief		隐藏界面
	 * @param[in]	<void>
	 * @return 		<bool> 返回true表示执行正常
	 * @note		隐藏界面，并挂起界面定时器与读写操作
	 */
	virtual bool hideFrame() { return true; }

	/**
	 * @brief		获取右侧显示栏界面（工艺下拉菜单）指针
	 * @param[in]	<void>
	 * @return		<QDialog*>	用户返回显示栏界面（工艺下拉菜单）的控件指针
	 * @note		在主界面上方导航栏点击“显示”按钮，则在屏幕右侧弹出”显示“界面。操作工在”显示“界面的下拉菜单中选中”工艺“，则显示返回指针对应的控件
	 * @note		调用者将界面设为非模态界面
	 */
	virtual QWidget* getRightShowFramePtr() { return NULL; }

	/**
	 * @brief		设置主菜单七个按钮的界面，及界面点击该按钮时向插件发送的index信号
	 * @param[in] <short index> 界面点击的第index个按钮（0~6），插件可接收到该数值
	 * @return <QDialog*>	显示界面指针
	 * @return <NULL> 调用失败
	 * @note 调用者将界面设为模态界面
	 */
	virtual QDialog* setMenuFramePtr(short index) { return NULL; }

	/**
	 * @brief		设置主菜单七个按钮的名称和图片
	 * @param[in] <short index> 界面正在加载第index个按钮（0~6），插件可接收到该数值
	 * @param[in]	<QString &menu_name> 插件定义的菜单名称
	 * @param[in]	<QString &icon_path> 插件定义的菜单图标路径
	 * @note 该函数会在用户点击主菜单上方的图标图案时触发，对主菜单的七个按钮遍历，替换图标和名称。
	 * @note 例：点击图标后，系统正在加载第index=1个按钮，并向插件索要第index=1个按钮的名称和图片，此时插件应该根据index=1返回用户想要设置的名称和图片
	 */
	virtual void setMenuNameIcon(short index, QString& menu_name, QString& icon_path) { return; }
	/**
	 * @brief			获取用户指令“编辑”界面指针
	 * @param[in]		<short cmd_id> 用户指令ID
	 * @param[in]		<double *params> 用户指令参数列表
	 * @param[in]		<short &size> 用户指令参数个数
	 * @return			<QDialog*>	用户返回参数配置页面的指针
	 * @note			在示教程序界面，选中用户指令，点击“编辑”后，界面上出现工艺指令编辑按钮。操作工再次点击指令编辑按钮，则显示返回指针对应的控件
	 * @note			调用者将界面设为模态界面
	 */
	virtual QDialog* getCmdEditFramePtr(short cmd_id, double* params, const short& size) { return NULL; }

	/**
	 * @brief		获取工艺指令当前的状态信息
	 * @param[in]	<short cmd_id> 用户指令ID
	 * @param[in]	<double *params> 用户指令参数列表
	 * @param[out]	<short &size> 用户指令参数个数
	 * @return 		<QString> 指令的状态信息
	 * @return		<“”> 空字符串，表示调用失败
	 * @note		调用者获取用户返回的字符串信息后，将该信息打印在主界面下方绿色的信息栏上
	 */
	virtual QString getCmdFeedBackInfo(short cmd_id, double* params, const short& size) { return ""; }

	/**
	 * @brief		获取非工艺指令当前的状态信息
	 * @param[in]	<QString cmd_str> 机器人系统HMI光标所在行的非工艺指令字符串内容
	 * @return 		<QString> 指令的状态信息
	 * @return		<“”> 空字符串，表示调用失败
	 * @note		机器人系统HMI光标移动时将调用此函数。
	 *				若光标所在行是工艺指令，则调用QString getCmdFeedBackInfo()接口
	 */
	virtual QString getCommonCmdFeedBackInfo(QString cmd_str) { return ""; }

	/**
	 * @brief			回调函数：进入工艺指令后触发
	 * @param[in]		无
	 * @param[output]	cmd_id	工艺指令id
	 * @param[output]	params[8]	工艺指令参数
	 * @param[output]	size		工艺指令参数个数
	 * @note		工艺指令内再次套用工艺指令，内部的工艺指令将不会触发回调
	 */
	virtual short compilerEnterCmd(short cmd_id, double* params, const short& size) { return 0; };

	/**
	 * @brief			回调函数：离开工艺指令后触发
	 * @param[in]		无
	 * @param[output]	cmd_id	工艺指令id
	 * @param[output]	params[8]	工艺指令参数
	 * @param[output]	size		工艺指令参数个数
	 * @note		工艺指令内再次套用工艺指令，内部的工艺指令将不会触发回调
	 */
	virtual short compilerLeaveCmd(short cmd_id, double* params, const short& size) { return 0; };

	/**
	 * @brief			回调函数：工艺指令编译前事件
	 * @param[in]
	 * @note		工艺指令编译前触发该函数
	 */
	virtual short compileRegCmdCallback(short cmd_id, double* params, const short& size) { return 0; };

	/**
	 * @brief			回调函数：工艺指令编译后事件
	 * @param[in]
	 * @note		工艺指令编译后触发该函数
	 */
	virtual short completeRegCmdCallback(short cmd_id, double* params, const short& size) { return 0; };

	/**
	 * @brief		设置用户权限
	 * @param[in]	short type:用户权限等级,
	 *				type = 0: 操作人员权限
	 *				type = 1: 管理员权限
	 *				type = 2: 厂家权限
	 * @note		每次切换至插件界面或系统用户权限改变时，此函数被调用
	 */
	virtual void setPermission(short type) { return; }

	/**
	 * @brief		【程序】界面打开的文件路径
	 * @param[in]	QString path: 【程序】界面打开的文件路径名称
	 * @note		输入的path为绝对路径
	 */
	virtual void hmiOpenFilePath(QString path) { return; }

	/**
	 * @brief			机器人系统工艺数据管道
	 * @param[in]		short src_id: 数据源ID
	 *					src_id数据位含义：
	 *					第1位:【数据属性】，1xx=GET数据；2xx=SET数据；0xx=所有工艺共享数据
	 *					第2-3位:【工艺参数】，1xx=弧焊GET数据；2xx=弧焊SET数据；0xx=弧焊共享数据
	 *
	 * @param[in]		void *input: 数据管道数据输入指针，开发人员进行数据类型转换
	 * @param[output]	void *output: 数据管道数据输出指针，开发人员进行数据类型进行转换
	 *
	 * @note			【src_id=0】为所有工艺共享的等环网数据
	 */
	virtual short dataPipe(short src_id, void* input, void* output) { return 0; };

	/**
	 * @brief			获取工艺加密密钥
	 * @param[in]		无
	 * @param[output]	无
	 * @note			默认返回空字符串，机器人系统不对插件进行加密校验，直接加载工艺插件，
	 *					机器人系统工艺需返回特定密钥字符串。
	 */
	virtual QString getEncyptKey() { return ""; };

	/**
 * @brief			启动前进检查事件
 * @param[in]		无
 * @param[output]	无
 * @note
 */
	virtual short startForwardCheck() { return 0; };

	/**
 * @brief			停止前进检查事件
 * @param[in]		无
 * @param[output]	无
 * @note
 */
	virtual short stopForwardCheck() { return 0; };

	/**
 * @brief			前进检查结束事件
 * @param[in]		无
 * @param[output]	无
 * @note
 */
	virtual short forwardCheckFinished() { return 0; };

	/**
 * @brief			断点启动前进检查事件
 * @param[in]		无
 * @param[output]	无
 * @note
 */
	virtual short breakPointForwardCheck() { return 0; };

	/**
 * @brief			启动回放事件
 * @param[in]		无
 * @param[output]	无
 * @note
 */
	virtual short startReplayRun() { return 0; };

	/**
	 * @brief			暂停回放事件
	 * @param[in]		无
	 * @param[output]	无
	 * @note
	 */
	virtual short pauseReplayRun() { return 0; };

	/**
 * @brief			停止回放事件
 * @param[in]		无
 * @param[output]	无
 * @note
 */
	virtual short stopReplayRun() { return 0; };

	/**
 * @brief			回放运行结束事件
 * @param[in]		无
 * @param[output]	无
 * @note
 */
	virtual short replayRunFinished() { return 0; };

	/**
 * @brief			断点回放启动事件
 * @param[in]		无
 * @param[output]	无
 * @note
 */
	virtual short breakPointReplayRun() { return 0; };

	/**
 * @brief			恢复回放事件
 * @param[in]		无
 * @param[output]	无
 * @note
 */
	virtual short continueReplayRun() { return 0; };

	/**
 * @brief			控制器掉电信号事件
 * @param[in]		无
 * @param[output]	无
 * @note
 */
	virtual short powerOffSignal() { return 0; };

signals:
	void appHide();

};


QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(GtAppFrameInterface, "RobotHmi");
QT_END_NAMESPACE

#endif