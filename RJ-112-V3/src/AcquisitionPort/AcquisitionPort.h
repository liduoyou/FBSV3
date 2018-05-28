#ifndef ACQUISITIONPORT_H
#define ACQUISITIONPORT_H

#include <QObject>
#include <QTimer>
class AcquisitionPort : public QObject
{
    Q_OBJECT
public:
    explicit AcquisitionPort(QObject *parent = 0);
    ~AcquisitionPort();

    void setOnline(bool online);
    bool getOnline()const;
    void setId(quint32 id);
    quint32 getId()const;
    void setgroupID(quint32 groupID);
    quint32 getgroupID()const;
    void setHandShackFlag(int flag);/*可具体定义错误原因0x01 - 已握手;0x02 - ID错误;0X03 - 等等。。。*/
    int getHandShackFlag()const;

    void setreData(QByteArray redata);
    QByteArray getreData()const;

    void setChannel_1Value(quint16 value);
    quint16 getChannel_1Value()const;
    void setChannel_2Value(quint16 value);
    quint16 getChannel_2Value()const;
    void setChannel_3Value(quint16 value);
    quint16 getChannel_3Value()const;
    void setChannel_4Value(quint16 value);
    quint16 getChannel_4Value()const;

    void setChannel_5Value(quint16 value);
    quint16 getChannel_5Value()const;
    void setChannel_6Value(quint16 value);
    quint16 getChannel_6Value()const;
    void setChannel_7Value(quint16 value);
    quint16 getChannel_7Value()const;
    void setChannel_8Value(quint16 value);
    quint16 getChannel_8Value()const;

    void setChannel_9Value(quint64 value);
    quint64 getChannel_9Value()const;
    void setChannel_10Value(quint64 value);
    quint64 getChannel_10Value()const;

    void setChannel_11Value(quint8 value);
    quint8 getChannel_11Value()const;
    void setChannel_12Value(quint8 value);
    quint8 getChannel_12Value()const;
    void setChannel_13Value(quint8 value);
    quint8 getChannel_13Value()const;
    void setChannel_14Value(quint8 value);
    quint8 getChannel_14Value()const;
    void setChannel_15Value(quint8 value);
    quint8 getChannel_15Value()const;
    void setChannel_16Value(quint8 value);
    quint8 getChannel_16Value()const;

    void setACID(int i);
    int getACID();
public slots:
    void changeAllRelayStatus(bool flag);
    void changeOneRelayStatus(int num,bool flag);
    void changeOrderOpenRelayStatus(bool flag);
    void changeOrderCloseRelayStatus(bool flag);
    void changeCircularRelayStatus();
private slots:
    void setacPortnotonline();
    void slotmytimer();
    void startMyTimer(bool online);
signals:
    void signalstartTimer(bool);
    void signalwriteSerialPort(QByteArray data);
private:

    void updateValue(QByteArray data);
    void setChannelValue(int channelID,quint64 value);

    quint8 checkSum(QByteArray data, quint16 length);
    quint16 hexToDec(char *data);
    quint16 quint32ToHex(quint32 data);

    bool                      m_online;
    quint32                   m_id;
    quint32                   m_groupid;
    int                       m_flag;
    int                       m_i;// ini 文件中的编号
    QByteArray                m_redata;
    QTimer*                   m_BadTimer;//置采集bad不在线定时器

    QTimer*                   m_OrderOpenTimer;
    QList<QByteArray>         m_OrderOpenSenderdata;
    int                       m_OrderOpencount;

    QTimer*                   m_OrderCloseTimer;
    QList<QByteArray>         m_OrderCloseSenderdata;
    int                       m_OrderClosecount;

    quint16                   m_channel_1value;
    quint16                   m_channel_2value;
    quint16                   m_channel_3value;
    quint16                   m_channel_4value;

    quint16                   m_channel_5value;
    quint16                   m_channel_6value;
    quint16                   m_channel_7value;
    quint16                   m_channel_8value;

    quint64                   m_channel_9value;
    quint64                   m_channel_10value;

    quint8                    m_channel_11value;
    quint8                    m_channel_12value;
    quint8                    m_channel_13value;
    quint8                    m_channel_14value;
    quint8                    m_channel_15value;
    quint8                    m_channel_16value;

};

#endif // ACQUISITIONPORT_H
