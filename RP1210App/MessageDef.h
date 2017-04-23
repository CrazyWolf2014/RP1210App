
#ifndef MessageDef_h__
#define MessageDef_h__

// 4/23/2017 : ZH : RP1210Э�����漰���ĸ�����Ϣ�Ķ���

#include <QString>
#include <QByteArray>

// 4/23/2017 : ZH : ��Ϣ����
class MessageBase
{
public:
	MessageBase(QByteArray rawMsg,bool useEcho = false);
	~MessageBase(); 


	QString ByteArrayToQString(QByteArray arr) const;

	// 4/23/2017 : ZH : ��RawMsg�е�ÿ���ֽڶ���ʽ��Ϊ16������ʽ��ɵ��ַ���
	QString GetRawMsgString();
	QString GetRawMsgString()const;

	// 4/23/2017 : ZH : �������ʵ�ֵĽӿڣ���������в�ͬ��ת���ַ���������
	virtual QString GetMsgDataString()const = 0;
	
	// 4/23/2017 : ZH : ��ȡʱ���
	unsigned int GetTimeStamp() const;

	// 4/23/2017 : ZH : ��ȡEcho�ֽ�
	char GetEchoByte() const;	

protected:
	unsigned int TimeStamp;      // ʱ���  : 4�ֽڣ���˴洢
	unsigned char Echo;          // echo��ǣ�ֻ�е�IsEchoΪTrue��ʱ�����Ч
	QByteArray Data;             // ��Ϣ�غ�

	bool UseEcho;                // �Ƿ�ʹ��echo��� 	
	QByteArray RawMsg;           // ��ԭʼ����Ϣ
	QString    RawMsgStr;        // �ַ�����ʽ
};

class J1939Message : public MessageBase
{
public:
	J1939Message(QByteArray rawMsg, bool useEcho = false);
	~J1939Message();

public:
	int GetPGN() const;
	unsigned char GetPriority() const;
	unsigned char GetSA() const;
	unsigned char GetTA() const;
	QByteArray GetJ1939Data() const;
	QString GetMsgDataString()const override; 

protected:
	int PGN;                      // PGN�������ֽڣ�С�˴洢
	unsigned char Priority;       // Priority:һ���ֽ�
	unsigned char SA;             // SA��һ���ֽ�   
	unsigned char TA;             // TA��һ���ֽ�
	QByteArray    J1939Data;      // J1939��Ϣ����
};







#endif // MessageDef_h__