#ifndef QZIGBEETHREAD_H
#define QZIGBEETHREAD_H

#include <QThread>
#include <QTimer>
#include <QMap>
#include "../SerialPort/posix_qextserialport.h"    //串口类
#include "../AcquisitionPort/AcquisitionPort.h"
class QZigbeeThread : public QThread
{
    Q_OBJECT
public:
    explicit QZigbeeThread(QObject *parent = 0);
    ~QZigbeeThread();

    virtual void run();
    void writeDataToSerial(QByteArray data, int count);
signals:
    void signal_Data(int,int);
    void sendSensorCalValue(const QString&);
    void saveAcquisitionData(QByteArray);
    void sendAcquisitionData(QByteArray);
    void updateAcquisitionStatus();
private slots:
    void waittimeout();
    void sendToUpdate();
    void setacPortnotonline();
    void receiveData(QByteArray revData);
private:
    void readByteData();
    void dealData(QByteArray data, int count);
    quint8 checkSum(QByteArray data, quint16 length);//校验和
    quint16 hexToDec(char *data);//16进制->10进制
    quint16 quint32ToHex(quint32 data);//16进制->10进制
    quint32 setbitdata(quint8 High1, quint8 High2, quint8 Low1, quint8 Low2);

    int _handshake_flag;   //握手标志
    quint32 _equi;
    quint32 _groupID;

    Posix_QextSerialPort * m_pSerial;
    QTimer*               m_Timerout;//超时计时
    bool                  m_timeflag;
    QByteArray            m_array;//采集数据量
    bool                  isSendData;
    QTimer*               m_sendDataTimer;//按时发送采集数据
    QList<QTimer*>        m_BadTimer;//置采集ban不在线定时器

    QMap<uint, AcquisitionPort *>        m_sensorTypeacPort;
    QMap<uint, AcquisitionPort *>        m_switchValueacPort;
};

#endif // QZIGBEETHREAD_H
