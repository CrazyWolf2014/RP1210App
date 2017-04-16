
#ifndef RP1210ProtocolModel_h__
#define RP1210ProtocolModel_h__

// 4/16/2017 : ZH : Э���б�

#include <QAbstractListModel>
#include "RP1210DeviceModel.h"

struct Rp1210Protocol
{
	int             ProtocolID;          // ��� 
	QString         ProtocolName;        // ����
	QString         ProtocolParam;       // ����
	QStringList     ProtocolSpeed;       // �ٶ� 
	QList<int>      DeviceIDs;           // ֧�ֵ��豸���б� 
};

class RP1210ProtocolModel : public QAbstractListModel
{
	Q_OBJECT

public:
	RP1210ProtocolModel(QObject *parent);
	~RP1210ProtocolModel();

	Rp1210Protocol* GetProtocol(int index);
	void IniProtocolList(class QSettings* VenderIni, QList<Rp1210Device>& DeviceList);
	void SetProtocolList(QList<int> list);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;

private:
	QMap<int, Rp1210Protocol> RawProtocolMap;
	QList<int>            IndexList;
}; 

#endif // RP1210ProtocolModel_h__
