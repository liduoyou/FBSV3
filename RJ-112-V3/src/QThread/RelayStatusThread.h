#ifndef RELAYSTATUSTHREAD_H
#define RELAYSTATUSTHREAD_H

#include <QThread>
#include <QTimer>
class Posix_QextSerialPort;
class RelayStatusThread : public QThread
{
    Q_OBJECT
public:
    explicit RelayStatusThread(QObject *parent = 0);
    ~RelayStatusThread();

    virtual void run();

    void writeDataToSerial(int flag, QByteArray datagram);
signals:
    void sendAcquisitionData(QByteArray);

private slots:
    void sendToUpdate();
private:
    void dealData(QByteArray data, int datasize);
    quint16 GetCheckCode(QByteArray pSendBuf, int nEnd);
    Posix_QextSerialPort* m_pSerial;
    QTimer*               m_sendDataTimer;//按时发送采集数据
    QByteArray            m_array;//采集数据量
    bool                  isSendData;
    quint8                _uphockstop;
    quint8                _downhockstop;
    quint8                _bigcarstop;
};

#endif // RELAYSTATUSTHREAD_H
