
#ifndef RP1210MsgParser_h__
#define RP1210MsgParser_h__

#include <QAbstractTableModel>
#include "MessageDef.h"

// 4/23/2017 : ZH : ��Ϣ��������� --> Ŀǰֻ֧��J1939��Ϣ
class RP1210MsgParser : public QAbstractTableModel
{
	Q_OBJECT

public:
	RP1210MsgParser(QObject *parent);
	~RP1210MsgParser();

	// 4/23/2017 : ZH : QAbstractTableModel����
	int rowCount(const QModelIndex &parent)const override;
	int columnCount(const QModelIndex &parent) const override;
	QVariant data(const QModelIndex& index, int role)const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

public:
	QString GetMessageString(int row);
	void ClearAllMessage();
	void DeleteMessage(QModelIndexList& msgs);


public slots:
    // 4/23/2017 : ZH : ���ղ�������Ϣ
	void OnMessage(QByteArray data);

private:
	// 4/23/2017 : ZH : ������Ϣ
	QList<J1939Message> j1939MsgList;
};





#endif // RP1210MsgParser_h__

