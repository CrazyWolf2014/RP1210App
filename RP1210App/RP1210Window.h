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

	QAction* selectAllAction;
	QAction* clearAllAction;
	QAction* copyAction;
	QAction* deleteAction;
	QAction* logtoFileAction;
	QAction* separator01Action;
	QAction* separator02Action;

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

	void OnSelectionChanged(QItemSelection selected,QItemSelection deSelected);
	void OnScrollRangeChanged(int min, int max);

	//4/27/2017 ZH :�����Ĳ˵�
	void OnSelectAll();
	void OnClearAll();
	void OnDelete();
	void OnCopy();
	void OnLogtoFile();

public slots:
	void OnLogMsg(QString Msg);


private:
	// 4/18/2017 : ZH : ˽�У��������������ݿͻ�ѡ��ƴ��Э���ַ�����������Ӳ����������
	QString GetProtocolString();

	// 4/19/2017 : ZH : ˽�У������������������������ڲ����Ӻø����źŲ�
	void SetUpFilterWindow();

	//4/27/2017 ZH : ˽�У��������������úñ����ͼ
	void SetUpTableView();
};
