#ifndef RP1210DeviceModel_h__
#define RP1210DeviceModel_h__

// 4/16/2017 : ZH : �豸�б�

#include <QAbstractListModel>

struct Rp1210Device
{
	int                   DeviceID;                 // �豸�� 
	QString               DeviceName;               // �豸����
	QString               DeviceParam;              // �豸����
	int                   MultiCANChannels;
	int                   MultiJ1939Channels;
	int                   MultiISO15765Channels;

	QList<int>            Protocols;    // ֧�ֵ�Э���б�  
};

class RP1210DeviceModel : public QAbstractListModel
{
	Q_OBJECT

public:
	RP1210DeviceModel(QObject *parent);
	~RP1210DeviceModel();

	QList<Rp1210Device>& GetDeviceList();
	QList<int>* GetProtocolList(int index);

	void InitDeviceList(class QSettings* VenderIni);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;

private:
	QList<Rp1210Device> DeviceList;
};


#endif // RP1210DeviceModel_h__
