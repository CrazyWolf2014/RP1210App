

#ifndef RP1210ReadThread_h__
#define RP1210ReadThread_h__

#include <QThread>

// 4/22/2017 : ZH : ��Ϣ��ȡ�߳�

class RP1210Core;

class RP1210ReadThread : public QThread
{
	Q_OBJECT

public:
	RP1210ReadThread(RP1210Core* core,QObject *parent);
	~RP1210ReadThread();

	void SetNeedExit(bool needExit);

protected:
	void run() Q_DECL_OVERRIDE;

private:
	bool NeedExit;                     // �Ƿ���Ҫ�˳�
	RP1210Core* rp1210Core;            // rp1210
									
signals:							
	void MsgReady(QByteArray data);    // ����Ϣ
	void ErrorOccurred(short ErrorCode);   // ��ȡʧ�� 
};



#endif // RP1210ReadThread_h__

