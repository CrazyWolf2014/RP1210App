#ifndef RP1210Core_h__
#define RP1210Core_h__

// 2017/04/16 : ZH :  RP1210Э��ʵ��

#include <QObject>
#include "RP1210.h"

class RP1210Core : public QObject
{
	Q_OBJECT

private:
	RP1210Core(QObject *parent);

public:
	static RP1210Core* GetInstance(); 
	~RP1210Core();

	DWORD LoadRp1210DLL(QString DLLPath);
	void UnLoadRp1210DLL(); 


public:
	short ClientConnect(short DeviceId, QString Protocol,long SendBufferLen = 0,long ReceiveBufferLen = 0,bool IsAppPacketizingIncomingMsgs = false);
	short ClientDisconnect();

private:	
	// 4/16/2017 : ZH : ��̬�⵼������ָ�붨��
	fxRP1210_ClientConnect           pRP1210_ClientConnect;
	fxRP1210_ClientDisconnect        pRP1210_ClientDisconnect;
	fxRP1210_ReadMessage             pRP1210_ReadMessage;
	fxRP1210_SendMessage             pRP1210_SendMessage;
	fxRP1210_SendCommand             pRP1210_SendCommand;
	fxRP1210_ReadVersion             pRP1210_ReadVersion;
	fxRP1210_ReadDetailedVersion     pRP1210_ReadDetailedVersion;
	fxRP1210_GetHardwareStatus       pRP1210_GetHardwareStatus;
	fxRP1210_GetErrorMsg             pRP1210_GetErrorMsg;
	fxRP1210_GetLastErrorMsg         pRP1210_GetLastErrorMsg;

private:
	HINSTANCE                        hRP1210DLL;     // 4/16/2017 : ZH : ��̬����
	static RP1210Core*               theRp1210Instance;


private:
	short     ClientID;    // RP1210_ClientConnect���óɹ��󷵻صĿͻ���id,���涯̬��ĵ��ö���Ҫʹ�õ��˺�����
};


#endif // RP1210Core_h__


