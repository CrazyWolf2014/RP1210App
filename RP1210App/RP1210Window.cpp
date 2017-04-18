#include "RP1210Window.h"
#include "RP1210IniData.h"
#include "RP1210Core.h"

#include <QMessageBox>

RP1210Window::RP1210Window(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	IniData = RP1210IniData::GetInistance();
	IniData->ReadMainIniFile();
	rp1210Core = RP1210Core::GetInstance();

	connect(IniData, SIGNAL(LogMsg(QString)), this, SLOT(OnLogMsg(QString)));
	connect(rp1210Core, SIGNAL(LogMsg(QString)), this, SLOT(OnLogMsg(QString)));
	connect(ui.checkBoxAutoBaudRate, SIGNAL(toggled(bool)), this,SLOT(OnAutoBaudRate(bool)));
	connect(ui.pushButtonConnect, SIGNAL(clicked()), this, SLOT(OnConnect()));
	connect(ui.pushButtonDisConnect, SIGNAL(clicked()), this, SLOT(OnDisConnect()));
	connect(ui.pushButtonClearLog, SIGNAL(clicked()), this, SLOT(OnClearLog()));
	connect(ui.comboBoxVendor, SIGNAL(currentIndexChanged(QString)), IniData, SLOT(OnVenderChanged(QString)));
	connect(ui.comboBoxDevice, SIGNAL(currentIndexChanged(int)), IniData, SLOT(OnDeviceChanged(int)));
	connect(ui.comboBoxProtocol, SIGNAL(currentIndexChanged(int)), IniData, SLOT(OnProtocolChanged(int)));
	
	ui.comboBoxVendor->setModel(IniData->GetVenderModel());
	ui.comboBoxDevice->setModel(IniData->GetDeviceModel());
	ui.comboBoxProtocol->setModel(IniData->GetProtocolModel());
	ui.comboBoxBaudRate->setModel(IniData->GetBaudRateModel());

	ui.pushButtonConnect->setEnabled(true);
	ui.pushButtonDisConnect->setEnabled(false);

}

RP1210Window::~RP1210Window()
{
	if (IniData)
		delete IniData;
	if (rp1210Core)
		delete rp1210Core;

	IniData = 0;
	rp1210Core = 0;
}

void RP1210Window::OnAutoBaudRate(bool bAuto)
{
	if (ui.checkBoxAutoBaudRate->isChecked())
	{
		ui.comboBoxBaudRate->setEnabled(false);
	}
	else
	{
		ui.comboBoxBaudRate->setEnabled(true);
	}
}

void RP1210Window::OnConnect()
{
	QString dllPath = IniData->GetVenderDllPath(ui.comboBoxVendor->currentIndex());

	DWORD dwError = rp1210Core->LoadRp1210DLL(dllPath);

	if (!dwError)      // 4/16/2017 : ZH :  dwError == 0 --> Load Success
	{ 
		// 4/18/2017 : ZH : �豸ID��Э���ַ���
		int DeviceID = IniData->GetDeviceId(ui.comboBoxDevice->currentIndex());
		QString Protocol = GetProtocolString();		
		short ErrorCode = rp1210Core->ClientConnect(DeviceID, Protocol);
		if (ErrorCode != NO_ERRORS)			return;

		// 4/18/2017 : ZH : �����J1939Э��
		




		ui.pushButtonConnect->setEnabled(false);
		ui.pushButtonDisConnect->setEnabled(true);

	}
	else
	{
		QMessageBox::critical(this, tr("Can not load RP1210 DLL"), tr("Load %1 failed! Error code = %2").arg(dllPath).arg(dwError));
	}
}

void RP1210Window::OnDisConnect()
{
	short ErrorCode = rp1210Core->ClientDisconnect();
	if (ErrorCode == NO_ERRORS)
	{ 
		ui.pushButtonConnect->setEnabled(true);
		ui.pushButtonDisConnect->setEnabled(false);
	}
}

void RP1210Window::OnClearLog()
{
	ui.textBrowserLogMsg->clear();
}

void RP1210Window::OnLogMsg(QString Msg)
{
	ui.textBrowserLogMsg->append(Msg);
}

QString RP1210Window::GetProtocolString()
{
	QString ProtocolName = IniData->GetProtocolName(ui.comboBoxProtocol->currentIndex());
	if (!(ui.checkBoxAutoBaudRate->isChecked()))
	{
		QString BaudRate = IniData->GetBaudRate(ui.comboBoxBaudRate->currentIndex());
		return QString("%1:Baud=%2").arg(ProtocolName).arg(BaudRate);
	}
	else
	{
		return QString("%1:Baud=Auto").arg(ProtocolName);
	}
}
