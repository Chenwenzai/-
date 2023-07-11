#ifndef GTAPPFRAMEINTERFACE_H
#define GTAPPFRAMEINTERFACE_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QtPlugin>

struct AppUserComParam
{
	short channel_index;
	short user_id;			//��ӦUSERָ�������ID
	long  long_param[4];	//��ӦUSERָ�������L1��L2��L3��L4
	double double_param[4]; //��ӦUSERָ�������D1��D2��D3��D4
};


/**
 * @brief			�û������գ��������ӿ�
 * @note			�û��������ս�����ʱ����̳�GtAppFrameInterface
 * @note 			�ڲ��ָ��ʵ�ֵ�ĩβ����Ҫ��ע�����Կ�Լ��û����������
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

							// ��ע�����Կ����RobotHmi�����Լ��û���������ƣ�UserDllName��
							Q_EXPORT_PLUGIN2("RobotHmi", UserDllName);
 */
class GtAppFrameInterface : public QWidget
{

public:
	virtual ~GtAppFrameInterface() {}

	/**
	 * @brief		��ȡ���������
	 * @param[in]	<void>
	 * @return		<QString> �û����صĽ�������
	 * @note		�������ƽ�������־�ļ�¼
	 */
	virtual QString getFrameName() = 0;

	/**
	 * @brief		��ȡ����İ汾��Ϣ
	 * @param[in]	<void>
	 * @return		<QString> �û����صİ汾��Ϣ
	 * @note		�汾��Ϣ�����ڰ汾���
	 */
	virtual QString getVersion() { return ""; }


	/**
	 * @brief		�����ʼ������
	 * @param[in]	<void>
	 * @return 		<void>
	 * @note		�˺���ֻ��ϵͳ��ʼ��ʱ����һ��
	 */
	virtual void Init() { return; }

	/**
	 * @brief		�����������
	 * @param[in]	<void>
	 * @return 		<void>
	 * @note		�˺���ֻ��ϵͳ�˳�ǰ����һ��
	 */
	virtual void Exit() { return; }

	/**
	 * @brief		����ܽ��涨���ڵ��øú�������Ƶ�ʣ�Լ100ms~120ms����һ�Σ�
	 * @param[in]	<void>
	 * @return 		<void>
	 * @note		�û��豣֤���ú������ε���ʱ�䲻�ܹ�����������ѭ��
	 */
	virtual void fastHmiLoop() {}

	/**
	 * @brief		����ܽ��涨���ڵ��øú�������Ƶ�ʣ�Լ1000ms����һ�Σ�
	 * @param[in]	<void>
	 * @return 		<void>
	 * @note		�û��豣֤���ú������ε���ʱ�䲻�ܹ�����������ѭ��
	 */
	virtual void slowHmiLoop() {}

	/**
	 * @brief		������ϵͳPLC�߳����ڵ��øú�������Ƶ�ʣ�Լ10ms����һ�Σ�
	 * @param[in]	<void>
	 * @return 		<void>
	 * @note		�û��豣֤���ú������ε���ʱ�䲻�ܹ�����������ѭ��
	 */
	virtual void fastLogicLoop() {}

	/**
	 * @brief		������ϵͳNC�߳����ڵ��øú�������Ƶ�ʣ�Լ20ms����һ�Σ�
	 * @param[in]	<void>
	 * @return 		<void>
	 * @note		�û��豣֤���ú������ε���ʱ�䲻�ܹ�����������ѭ��
	 */
	virtual void slowLogicLoop() {}

	/**
	 * @brief		������ϵͳUSERʾ��ָ��ľ���ʵ��
	 * @param[in]	const AppUserComParam &param��������ϵͳִ����USERʾ��ָ��ʱ�Ĳ����б�
	 * @param[in]	const bool &first�����״�ִ����USERʾ��ָ���first = true;
	 * @return 		<0>��ִ�н�����
	 * @return 		<1>��ִ��δ������������ϵͳ���ٴ�ִ��USERָ�
	 * @return 		<2>��ִ�д��󡣻�����ϵͳ�����ֱ�����
	 * @note		�û�Ҳ��ͨ����˽ӿ�GTR_RegisterUserComע��USERָ��ľ���ʵ�����ݡ�
	 */
	virtual short userComLoopRun(const AppUserComParam& param, const bool& first) { return 0; }

	/**
	 * @brief		����������һ��״̬
	 * @param[in]	<void>
	 * @return 		<bool> ����true��ʾִ������
	 * @note		�ڲ��ӿڣ�����showFrame()����ǰ�Զ�����
	 */
	virtual bool readLastTimeStatus() { return false; }

	/**
	* @brief		���������ֳ�״̬
	* @param[in]	<void>
	* @return 		<bool> ����true��ʾִ������
	* @note		�ڲ��ӿڣ�����showFrame()�������Զ�����
	*/
	virtual bool saveLastTimeStatus() { return false; }

	/**
	 * @brief		��ʾ����
	 * @param[in]	<void>
	 * @return 		<bool> ����true��ʾִ������
	 * @note		��ʾ���棬��������涨ʱ�����д����
	 */
	virtual bool showFrame() { return true; }

	/**
	 * @brief		���ؽ���
	 * @param[in]	<void>
	 * @return 		<bool> ����true��ʾִ������
	 * @note		���ؽ��棬��������涨ʱ�����д����
	 */
	virtual bool hideFrame() { return true; }

	/**
	 * @brief		��ȡ�Ҳ���ʾ�����棨���������˵���ָ��
	 * @param[in]	<void>
	 * @return		<QDialog*>	�û�������ʾ�����棨���������˵����Ŀؼ�ָ��
	 * @note		���������Ϸ��������������ʾ����ť��������Ļ�Ҳ൯������ʾ�����档�������ڡ���ʾ������������˵���ѡ�С����ա�������ʾ����ָ���Ӧ�Ŀؼ�
	 * @note		�����߽�������Ϊ��ģ̬����
	 */
	virtual QWidget* getRightShowFramePtr() { return NULL; }

	/**
	 * @brief		�������˵��߸���ť�Ľ��棬���������ð�ťʱ�������͵�index�ź�
	 * @param[in] <short index> �������ĵ�index����ť��0~6��������ɽ��յ�����ֵ
	 * @return <QDialog*>	��ʾ����ָ��
	 * @return <NULL> ����ʧ��
	 * @note �����߽�������Ϊģ̬����
	 */
	virtual QDialog* setMenuFramePtr(short index) { return NULL; }

	/**
	 * @brief		�������˵��߸���ť�����ƺ�ͼƬ
	 * @param[in] <short index> �������ڼ��ص�index����ť��0~6��������ɽ��յ�����ֵ
	 * @param[in]	<QString &menu_name> �������Ĳ˵�����
	 * @param[in]	<QString &icon_path> �������Ĳ˵�ͼ��·��
	 * @note �ú��������û�������˵��Ϸ���ͼ��ͼ��ʱ�����������˵����߸���ť�������滻ͼ������ơ�
	 * @note �������ͼ���ϵͳ���ڼ��ص�index=1����ť����������Ҫ��index=1����ť�����ƺ�ͼƬ����ʱ���Ӧ�ø���index=1�����û���Ҫ���õ����ƺ�ͼƬ
	 */
	virtual void setMenuNameIcon(short index, QString& menu_name, QString& icon_path) { return; }
	/**
	 * @brief			��ȡ�û�ָ��༭������ָ��
	 * @param[in]		<short cmd_id> �û�ָ��ID
	 * @param[in]		<double *params> �û�ָ������б�
	 * @param[in]		<short &size> �û�ָ���������
	 * @return			<QDialog*>	�û����ز�������ҳ���ָ��
	 * @note			��ʾ�̳�����棬ѡ���û�ָ�������༭���󣬽����ϳ��ֹ���ָ��༭��ť���������ٴε��ָ��༭��ť������ʾ����ָ���Ӧ�Ŀؼ�
	 * @note			�����߽�������Ϊģ̬����
	 */
	virtual QDialog* getCmdEditFramePtr(short cmd_id, double* params, const short& size) { return NULL; }

	/**
	 * @brief		��ȡ����ָ�ǰ��״̬��Ϣ
	 * @param[in]	<short cmd_id> �û�ָ��ID
	 * @param[in]	<double *params> �û�ָ������б�
	 * @param[out]	<short &size> �û�ָ���������
	 * @return 		<QString> ָ���״̬��Ϣ
	 * @return		<����> ���ַ�������ʾ����ʧ��
	 * @note		�����߻�ȡ�û����ص��ַ�����Ϣ�󣬽�����Ϣ��ӡ���������·���ɫ����Ϣ����
	 */
	virtual QString getCmdFeedBackInfo(short cmd_id, double* params, const short& size) { return ""; }

	/**
	 * @brief		��ȡ�ǹ���ָ�ǰ��״̬��Ϣ
	 * @param[in]	<QString cmd_str> ������ϵͳHMI��������еķǹ���ָ���ַ�������
	 * @return 		<QString> ָ���״̬��Ϣ
	 * @return		<����> ���ַ�������ʾ����ʧ��
	 * @note		������ϵͳHMI����ƶ�ʱ�����ô˺�����
	 *				������������ǹ���ָ������QString getCmdFeedBackInfo()�ӿ�
	 */
	virtual QString getCommonCmdFeedBackInfo(QString cmd_str) { return ""; }

	/**
	 * @brief			�ص����������빤��ָ��󴥷�
	 * @param[in]		��
	 * @param[output]	cmd_id	����ָ��id
	 * @param[output]	params[8]	����ָ�����
	 * @param[output]	size		����ָ���������
	 * @note		����ָ�����ٴ����ù���ָ��ڲ��Ĺ���ָ����ᴥ���ص�
	 */
	virtual short compilerEnterCmd(short cmd_id, double* params, const short& size) { return 0; };

	/**
	 * @brief			�ص��������뿪����ָ��󴥷�
	 * @param[in]		��
	 * @param[output]	cmd_id	����ָ��id
	 * @param[output]	params[8]	����ָ�����
	 * @param[output]	size		����ָ���������
	 * @note		����ָ�����ٴ����ù���ָ��ڲ��Ĺ���ָ����ᴥ���ص�
	 */
	virtual short compilerLeaveCmd(short cmd_id, double* params, const short& size) { return 0; };

	/**
	 * @brief			�ص�����������ָ�����ǰ�¼�
	 * @param[in]
	 * @note		����ָ�����ǰ�����ú���
	 */
	virtual short compileRegCmdCallback(short cmd_id, double* params, const short& size) { return 0; };

	/**
	 * @brief			�ص�����������ָ�������¼�
	 * @param[in]
	 * @note		����ָ�����󴥷��ú���
	 */
	virtual short completeRegCmdCallback(short cmd_id, double* params, const short& size) { return 0; };

	/**
	 * @brief		�����û�Ȩ��
	 * @param[in]	short type:�û�Ȩ�޵ȼ�,
	 *				type = 0: ������ԱȨ��
	 *				type = 1: ����ԱȨ��
	 *				type = 2: ����Ȩ��
	 * @note		ÿ���л�����������ϵͳ�û�Ȩ�޸ı�ʱ���˺���������
	 */
	virtual void setPermission(short type) { return; }

	/**
	 * @brief		�����򡿽���򿪵��ļ�·��
	 * @param[in]	QString path: �����򡿽���򿪵��ļ�·������
	 * @note		�����pathΪ����·��
	 */
	virtual void hmiOpenFilePath(QString path) { return; }

	/**
	 * @brief			������ϵͳ�������ݹܵ�
	 * @param[in]		short src_id: ����ԴID
	 *					src_id����λ���壺
	 *					��1λ:���������ԡ���1xx=GET���ݣ�2xx=SET���ݣ�0xx=���й��չ�������
	 *					��2-3λ:�����ղ�������1xx=����GET���ݣ�2xx=����SET���ݣ�0xx=������������
	 *
	 * @param[in]		void *input: ���ݹܵ���������ָ�룬������Ա������������ת��
	 * @param[output]	void *output: ���ݹܵ��������ָ�룬������Ա�����������ͽ���ת��
	 *
	 * @note			��src_id=0��Ϊ���й��չ���ĵȻ�������
	 */
	virtual short dataPipe(short src_id, void* input, void* output) { return 0; };

	/**
	 * @brief			��ȡ���ռ�����Կ
	 * @param[in]		��
	 * @param[output]	��
	 * @note			Ĭ�Ϸ��ؿ��ַ�����������ϵͳ���Բ�����м���У�飬ֱ�Ӽ��ع��ղ����
	 *					������ϵͳ�����践���ض���Կ�ַ�����
	 */
	virtual QString getEncyptKey() { return ""; };

	/**
 * @brief			����ǰ������¼�
 * @param[in]		��
 * @param[output]	��
 * @note
 */
	virtual short startForwardCheck() { return 0; };

	/**
 * @brief			ֹͣǰ������¼�
 * @param[in]		��
 * @param[output]	��
 * @note
 */
	virtual short stopForwardCheck() { return 0; };

	/**
 * @brief			ǰ���������¼�
 * @param[in]		��
 * @param[output]	��
 * @note
 */
	virtual short forwardCheckFinished() { return 0; };

	/**
 * @brief			�ϵ�����ǰ������¼�
 * @param[in]		��
 * @param[output]	��
 * @note
 */
	virtual short breakPointForwardCheck() { return 0; };

	/**
 * @brief			�����ط��¼�
 * @param[in]		��
 * @param[output]	��
 * @note
 */
	virtual short startReplayRun() { return 0; };

	/**
	 * @brief			��ͣ�ط��¼�
	 * @param[in]		��
	 * @param[output]	��
	 * @note
	 */
	virtual short pauseReplayRun() { return 0; };

	/**
 * @brief			ֹͣ�ط��¼�
 * @param[in]		��
 * @param[output]	��
 * @note
 */
	virtual short stopReplayRun() { return 0; };

	/**
 * @brief			�ط����н����¼�
 * @param[in]		��
 * @param[output]	��
 * @note
 */
	virtual short replayRunFinished() { return 0; };

	/**
 * @brief			�ϵ�ط������¼�
 * @param[in]		��
 * @param[output]	��
 * @note
 */
	virtual short breakPointReplayRun() { return 0; };

	/**
 * @brief			�ָ��ط��¼�
 * @param[in]		��
 * @param[output]	��
 * @note
 */
	virtual short continueReplayRun() { return 0; };

	/**
 * @brief			�����������ź��¼�
 * @param[in]		��
 * @param[output]	��
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