#ifndef TCPCLIENTTHREAD_H
#define TCPCLIENTTHREAD_H

#include <QThread>
#include <QtNetwork>
#include <QTcpSocket>
#include <QTimer>
#include <QAbstractSocket>
enum READMODE{
    RWDBMODE = 0x31,////读写DB块
    RWMAREA = 0x33,//读写M区
    RWIQAREA = 0x34,//读写I/Q区

    SERVERPORT = 1099 //port
};

class TcpClientThread : public QThread
{
    Q_OBJECT
public:
    explicit TcpClientThread(QObject *parent = 0);
    ~TcpClientThread();

    virtual void run();

    void setConnectStatus(bool flag);
    bool getConnetcStatus();
    void cleanArray();
signals:
    void sendDataSignal(int);
    void sendTcpSocketData(QByteArray);
    void sendConnectStatus(bool);

private slots:
    void newConnect(); //连接服务器
    bool Login();     //login
    void readMessage();  //接收数据
    void displayError(QAbstractSocket::SocketError);  //显示错误

    bool writeDataToTcpServer(int flag);

    void sendToUpdate();

    void reConnectSocket();

private:
    QTcpSocket *tcpSocket;
    QByteArray message;  //存放从服务器接收到的字符串
    quint16 blockSize;  //存放文件的大小信息

    quint8 counter;   //计数器

    QString ipAddress;//IP地址

    QByteArray      m_array;//数据infor量
    QTimer*         m_sendDataTimer;//按时发送数据
    QByteArray      send_buf;

    QByteArray      m_AreaData;

    QTimer*      m_timer1;//定时器1
    bool   _connectStatus;

//    int type1=qRegisterMetaType<QAbstractSocket::SocketError>("SocketError");

    void saveTcpServerData(QByteArray dealData, quint16 length);
    void updatePLCData();
};

#endif // TCPCLIENTTHREAD_H
