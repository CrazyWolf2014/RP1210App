#ifndef RP1210MsgLogger_h__
#define RP1210MsgLogger_h__

#include <QObject>

//5/2/2017 ZH :��Ϣ��¼
class RP1210MsgLogger : public QObject
{
	Q_OBJECT

public:
	RP1210MsgLogger(bool startLog = false,QObject *parent = 0);
	~RP1210MsgLogger();

public:
	//5/2/2017 ZH :�Ƿ�������־
	bool IsLog() const;

	//5/2/2017 ZH :��ʼ����־
	void StartLog();

	//5/2/2017 ZH :ֹͣ����־
	void StopLog();


public slots:
	//5/2/2017 ZH :
	void LogToFile(QString msg);
	void LogToFile(class J1939Message const* msg);

private:
	class QFile* logFile;
};


#endif // RP1210MsgLogger_h__