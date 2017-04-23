#pragma once

#include <QtWidgets/QDialog>
#include "ui_RP1210Window.h"

class RP1210Window : public QDialog
{
    Q_OBJECT

public:
    RP1210Window(QWidget *parent = Q_NULLPTR);
	~RP1210Window();

private:
    Ui::RP1210WindowClass ui;
	class J1939FilterWindow* J1939FilterDialog;

private:
	// 4/16/2017 : ZH : ini�ļ��л�ȡ��������
	class RP1210IniData* IniData;

	// 4/16/2017 : ZH : rp1210��̬��
	class RP1210Core* rp1210Core;

	// 4/23/2017 : ZH : ��Ϣ��ȡ�߳�
	class RP1210ReadThread* rp1210ReadThread;

	// 4/23/2017 : ZH : ��Ϣ����
	class RP1210MsgParser* msgParser;

protected slots:
	void OnAutoBaudRate(bool bAuto);
	void OnConnect();
	void OnDisConnect();
	void OnClearLog();
	void OnFilterWindow();
	void OnScrollRangeChanged(int min, int max);

public slots:
	void OnLogMsg(QString Msg);


private:
	// 4/18/2017 : ZH : ˽�У��������������ݿͻ�ѡ��ƴ��Э���ַ�����������Ӳ����������
	QString GetProtocolString();

	// 4/19/2017 : ZH : ˽�У������������������������ڲ����Ӻø����źŲ�
	void SetUpFilterWindow();
};
