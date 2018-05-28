#include "AcquisitionPort.h"
#include <QDebug>
#include "../DataHeaderDefine.h"
AcquisitionPort::AcquisitionPort(QObject *parent) :
    QObject(parent)
  , m_online(false)
  , m_id(0)
  , m_groupid(0)
  , m_flag(-1)
  , m_OrderOpencount(0)
  , m_OrderClosecount(0)
  , m_channel_1value(0)
  , m_channel_2value(0)
  , m_channel_3value(0)
  , m_channel_4value(0)
  , m_channel_5value(0)
  , m_channel_6value(0)
  , m_channel_7value(0)
  , m_channel_8value(0)
  , m_channel_9value(0)
  , m_channel_10value(0)
  , m_channel_11value(0)
  , m_channel_12value(0)
  , m_channel_13value(0)
  , m_channel_14value(0)
  , m_channel_15value(0)
  , m_channel_16value(0)
{
    m_redata.resize(47);
    for(int i=0;i<m_redata.size();i++){
        m_redata[i] = 0x00;
    }

    m_BadTimer = new QTimer();
    connect(m_BadTimer,SIGNAL(timeout()),this,SLOT(setacPortnotonline()));
    connect(this,SIGNAL(signalstartTimer(bool)),this,SLOT(startMyTimer(bool)));

    m_OrderOpenTimer = new QTimer();
    connect(m_OrderOpenTimer,SIGNAL(timeout()),this,SLOT(slotmytimer()));

    m_OrderCloseTimer = new QTimer();
    connect(m_OrderCloseTimer,SIGNAL(timeout()),this,SLOT(slotmytimer()));
}

AcquisitionPort::~AcquisitionPort()
{
    qDebug()<<"AcquisitionPort::~AcquisitionPort()";
}

void AcquisitionPort::startMyTimer(bool online){
    if(online){
        m_BadTimer->start(5*1000);
    }else{
        if(m_BadTimer->isActive()){
            m_BadTimer->stop();
        }
        for(int i=0;i<m_redata.size();i++){
            m_redata[i] = 0x00;
        }
        setreData(m_redata);
    }
}

void AcquisitionPort::setOnline(bool online)
{
    m_online = online;
    emit signalstartTimer(online);
}

bool AcquisitionPort::getOnline() const
{
    return m_online;
}

void AcquisitionPort::setId(quint32 id)
{
    m_id = id;
}

quint32 AcquisitionPort::getId() const
{
    return m_id;
}

void AcquisitionPort::setgroupID(quint32 groupID)
{
    m_groupid = groupID;
}

quint32 AcquisitionPort::getgroupID() const
{
    return m_groupid;
}

void AcquisitionPort::setHandShackFlag(int flag)
{
    m_flag = flag;
}


int AcquisitionPort::getHandShackFlag() const
{
    return m_flag;
}

void AcquisitionPort::setreData(QByteArray redata)
{
    m_redata = redata;
    updateValue(redata);
}

QByteArray AcquisitionPort::getreData() const
{
    return m_redata;
}

void AcquisitionPort::updateValue(QByteArray data)
{
    quint16 channelIDValue[16] = {0};
    quint64 channelNo9or10Value = 0;
    int j = 0;//接收的数据是 低位在前 高位在后
    int count = data.size();
    if(count == 47){
        for(int i = 12;i<count-19;i+=2){// 12-27 /* 1---8 通道
            quint8 low = (uchar)data.at(i);
            quint8 high = (uchar)data.at(i+1);
            channelIDValue[j] += high;channelIDValue[j] <<= 8;
            channelIDValue[j] += low;
            //把数据 整合到 2个字节放在数组中
            setChannelValue(j+1,channelIDValue[j]);
            j++;
        }
        j = 8;
        for(int k=count-12;k>=28;k-=2){//35-28 j = 8 start   /* 9通道
            channelIDValue[j] += (uchar)data.at(k);channelIDValue[j] <<= 8;
            channelIDValue[j] += (uchar)data.at(k-1);
            j++;
        }
        for(int i=8;i<j;i++){//32个字节的数据
            // (数组中的 2个字节 高位放在 m_array 前面 )
            channelNo9or10Value += channelIDValue[i];
            if(i != 11){
                channelNo9or10Value <<= 16;
            }
        }
        setChannelValue(9,channelNo9or10Value);

        j = 12;
        for(int l=count-4;l>=36;l-=2){//43-36 j = 12 start /*  10 通道
            channelIDValue[j] += (uchar)data.at(l);channelIDValue[j] <<= 8;
            channelIDValue[j] += (uchar)data.at(l-1);
            j++;
        }
        channelNo9or10Value = 0;
        for(int i=12;i<j;i++){//32个字节的数据
            // (数组中的 2个字节 高位放在 m_array 前面 )
            channelNo9or10Value += channelIDValue[i];
            if(i != 15){
                channelNo9or10Value <<= 16;
            }
        }
        setChannelValue(10,channelNo9or10Value);
#ifndef ARMCOMPILE
        QString str;
        for(int i=0;i<16;i++){
            quint16 sum = (quint16)channelIDValue[i];
            if(i == 15){
                str += QString("%1").arg(sum, 0, 16).toUpper().size() == 1?
                            QString("000%1").arg(sum, 0, 16).toUpper():
                            QString("%1").arg(sum, 0, 16).toUpper();
            }else{
                str += QString("%1").arg(sum, 0, 16).toUpper().size() == 1?
                            QString("000%1").arg(sum, 0, 16).toUpper()+" ":
                            QString("%1").arg(sum, 0, 16).toUpper()+" ";
            }
        }
        qDebug()<<"str"<<str;
        str.clear();
#endif
    }else if(count == 17){
        // 处理数据的 高低位
        quint16 channelIDValue = 0;
        QByteArray s_array;
        s_array.resize(16);
        for(int i=0;i<s_array.size();i++){
            s_array[i] = 0x00;
        }
        quint8 per = (uchar)data.at(12);//KEY[0] ~ KEY[7] -> Data[0]
        quint8 back = (uchar)data.at(13);//KEY[8] - KEY[15] ->Data[1]
        channelIDValue += back;channelIDValue <<= 8;
        channelIDValue += per;

        s_array[0] = (quint8)((channelIDValue & 0x0001) >> 0);
        s_array[1] = (quint8)((channelIDValue & 0x0002) >> 1);
        s_array[2] = (quint8)((channelIDValue & 0x0004) >> 2);
        s_array[3] = (quint8)((channelIDValue & 0x0008) >> 3);
        s_array[4] = (quint8)((channelIDValue & 0x0010) >> 4);
        s_array[5] = (quint8)((channelIDValue & 0x0020) >> 5);
        s_array[6] = (quint8)((channelIDValue & 0x0040) >> 6);
        s_array[7] = (quint8)((channelIDValue & 0x0080) >> 7);
        s_array[8] = (quint8)((channelIDValue & 0x0100) >> 8);
        s_array[9] = (quint8)((channelIDValue & 0x0200) >> 9);
        s_array[10] = (quint8)((channelIDValue & 0x0400) >> 10);
        s_array[11] = (quint8)((channelIDValue & 0x0800) >> 11);
        s_array[12] = (quint8)((channelIDValue & 0x1000) >> 12);
        s_array[13] = (quint8)((channelIDValue & 0x2000) >> 13);
        s_array[14] = (quint8)((channelIDValue & 0x4000) >> 14);
        s_array[15] = (quint8)((channelIDValue & 0x8000) >> 15);

        for(int i=0;i<s_array.size();i++){
            setChannelValue(i+1,s_array[i]);
        }
#ifndef ARMCOMPILE
        QString str;
        for(int i=0;i<16;i++){
            quint8 sum = (quint8)s_array[i];
            if(i == 15){
                str += QString("%1").arg(sum, 0, 16).toUpper().size() == 1?
                            QString("0%1").arg(sum, 0, 16).toUpper():
                            QString("%1").arg(sum, 0, 16).toUpper();
            }else{
                str += QString("%1").arg(sum, 0, 16).toUpper().size() == 1?
                            QString("0%1").arg(sum, 0, 16).toUpper()+" ":
                            QString("%1").arg(sum, 0, 16).toUpper()+" ";
            }
        }
        qDebug()<<"str"<<str;
        str.clear();
#endif
    }
}

void AcquisitionPort::setChannelValue(int channelID, quint64 value)
{
    switch (channelID) {
    case 1:{
        setChannel_1Value((quint16)value);
    }break;
    case 2:{
        setChannel_2Value((quint16)value);
    }break;
    case 3:{
        setChannel_3Value((quint16)value);
    }break;
    case 4:{
        setChannel_4Value((quint16)value);
    }break;
    case 5:{
        setChannel_5Value((quint16)value);
    }break;
    case 6:{
        setChannel_6Value((quint16)value);
    }break;
    case 7:{
        setChannel_7Value((quint16)value);
    }break;
    case 8:{
        setChannel_8Value((quint16)value);
    }break;
    case 9:{
        setChannel_9Value((quint64)value);
    }break;
    case 10:{
        setChannel_10Value((quint64)value);
    }break;
    case 11:{
        setChannel_11Value((quint8)value);
    }break;
    case 12:{
        setChannel_12Value((quint8)value);
    }break;
    case 13:{
        setChannel_13Value((quint8)value);
    }break;
    case 14:{
        setChannel_14Value((quint8)value);
    }break;
    case 15:{
        setChannel_15Value((quint8)value);
    }break;
    case 16:{
        setChannel_16Value((quint8)value);
    }break;
    default:
        break;
    }
}

void AcquisitionPort::changeAllRelayStatus(bool flag)//改变继电器状态
{
    if(m_OrderOpenTimer != NULL){
        if(m_OrderOpenTimer->isActive()){
            m_OrderOpenTimer->stop();
        }
    }
    if(m_OrderCloseTimer != NULL){
        if(m_OrderCloseTimer->isActive()){
            m_OrderCloseTimer->stop();
        }
    }
    //获取采集板号 设备号
    quint32 ACEquiID = 0;
    ACEquiID = getId();
    quint32 _groupID = getgroupID();
    quint32 _equi = 0;

    quint8 ACEquiIDhigh = (ACEquiID & 0x00ff0000) >> 16 ;
    quint8 ACEquiIDmid = (ACEquiID & 0x0000ff00) >> 8;
    quint8 ACEquiIDlow = (ACEquiID & 0x000000ff);

    QByteArray sendbuff;

    sendbuff[0] = 0xa5;sendbuff[1] = 0x5a;//帧头
    sendbuff[2] = 0x00;
    sendbuff[3] = 0x0c;//帧长度
    sendbuff[4] = 0x01;//版本号
    sendbuff[5] = 0x0A;//帧类型

    quint32 groupIDhigh = (_groupID & 0x00ff0000) >> 16 ;
    quint32 groupIDmid = (_groupID & 0x0000ff00) >> 8;
    quint32 groupIDlow = (_groupID & 0x000000ff);

    quint32 Equihigh = (_equi & 0x00ff0000) >> 16 ;
    quint32 Equimid = (_equi & 0x0000ff00) >> 8;
    quint32 Equilow = (_equi & 0x000000ff);

    sendbuff[6] = quint32ToHex(groupIDhigh);
    sendbuff[7] = quint32ToHex(groupIDmid);
    sendbuff[8] = quint32ToHex(groupIDlow);//群组编号

    sendbuff[9] = quint32ToHex(Equihigh);
    sendbuff[10] = quint32ToHex(Equimid);
    sendbuff[11] = quint32ToHex(Equilow);//设备编号

    if(flag){
        sendbuff[12] = 0xFF;
    }else{
        sendbuff[12] = 0x00;
    }

    sendbuff[13] = ACEquiIDhigh;//采集端设备编号
    sendbuff[14] = ACEquiIDmid;
    sendbuff[15] = ACEquiIDlow;
    sendbuff[16] = checkSum(sendbuff,16);//校验和
    sendbuff[17] = 0xc3;sendbuff[18] = 0x3c;//帧尾

#if 0
    if(flag){
        qDebug()<<"cccccccccccccccccccccccc";
        QString str;
        for(int i=0;i<sendbuff.size();i++){
            quint8 sum = (quint8)sendbuff.at(i);
            if(i == (sendbuff.size() - 1)){
                str += QString("%1").arg(sum, 0, 16).toUpper().size() == 1?
                            QString("0%1").arg(sum, 0, 16).toUpper():
                            QString("%1").arg(sum, 0, 16).toUpper();
            }else{
                str += QString("%1").arg(sum, 0, 16).toUpper().size() == 1?
                            QString("0%1").arg(sum, 0, 16).toUpper()+" ":
                            QString("%1").arg(sum, 0, 16).toUpper()+" ";
            }
        }
        qDebug()<<str;
        str.clear();
    }
#endif
    emit signalwriteSerialPort(sendbuff);
}

void AcquisitionPort::changeOneRelayStatus(int num,bool flag)
{
    if(m_OrderOpenTimer != NULL){
        if(m_OrderOpenTimer->isActive()){
            m_OrderOpenTimer->stop();
        }
    }
    if(m_OrderCloseTimer != NULL){
        if(m_OrderCloseTimer->isActive()){
            m_OrderCloseTimer->stop();
        }
    }
    //获取采集板号 设备号
    quint32 ACEquiID = 0;
    ACEquiID = getId();
    quint32 _groupID = getgroupID();
    quint32 _equi = 0;


    quint8 ACEquiIDhigh = (ACEquiID & 0x00ff0000) >> 16 ;
    quint8 ACEquiIDmid = (ACEquiID & 0x0000ff00) >> 8;
    quint8 ACEquiIDlow = (ACEquiID & 0x000000ff);

    QByteArray sendbuff;

    sendbuff[0] = 0xa5;sendbuff[1] = 0x5a;//帧头
    sendbuff[2] = 0x00;
    sendbuff[3] = 0x0d;//帧长度
    sendbuff[4] = 0x01;//版本号
    sendbuff[5] = 0x08;//帧类型

    quint32 groupIDhigh = (_groupID & 0x00ff0000) >> 16 ;
    quint32 groupIDmid = (_groupID & 0x0000ff00) >> 8;
    quint32 groupIDlow = (_groupID & 0x000000ff);

    quint32 Equihigh = (_equi & 0x00ff0000) >> 16 ;
    quint32 Equimid = (_equi & 0x0000ff00) >> 8;
    quint32 Equilow = (_equi & 0x000000ff);

    sendbuff[6] = quint32ToHex(groupIDhigh);
    sendbuff[7] = quint32ToHex(groupIDmid);
    sendbuff[8] = quint32ToHex(groupIDlow);//群组编号

    sendbuff[9] = quint32ToHex(Equihigh);
    sendbuff[10] = quint32ToHex(Equimid);
    sendbuff[11] = quint32ToHex(Equilow);//设备编号

    sendbuff[12] = num-1;//输出通道号 继电器板是：0-7
    if(flag == 0){
        sendbuff[13] = 0x00;//信息段
    }else if(flag == 1){
        sendbuff[13] = 0x01;//信息段
    }
    sendbuff[14] = ACEquiIDhigh;//采集端设备编号
    sendbuff[15] = ACEquiIDmid;
    sendbuff[16] = ACEquiIDlow;
    sendbuff[17] = checkSum(sendbuff,17);//校验和
    sendbuff[18] = 0xc3;sendbuff[19] = 0x3c;//帧尾
#if 0
    if(flag){
        qDebug()<<"cccccccccccccccccccccccc";
        QString str;
        for(int i=0;i<sendbuff.size();i++){
            quint8 sum = (quint8)sendbuff.at(i);
            if(i == (sendbuff.size() - 1)){
                str += QString("%1").arg(sum, 0, 16).toUpper().size() == 1?
                            QString("0%1").arg(sum, 0, 16).toUpper():
                            QString("%1").arg(sum, 0, 16).toUpper();
            }else{
                str += QString("%1").arg(sum, 0, 16).toUpper().size() == 1?
                            QString("0%1").arg(sum, 0, 16).toUpper()+" ":
                            QString("%1").arg(sum, 0, 16).toUpper()+" ";
            }
        }
        qDebug()<<str;
        str.clear();
    }
#endif
    emit signalwriteSerialPort(sendbuff);
}

void AcquisitionPort::changeOrderOpenRelayStatus(bool flag)
{
    if(m_OrderCloseTimer != NULL){
        if(m_OrderCloseTimer->isActive()){
            m_OrderCloseTimer->stop();
        }
    }
    //获取采集板号 设备号
    quint32 ACEquiID = 0;
    ACEquiID = getId();
    quint32 _groupID = getgroupID();
    quint32 _equi = 0;


    quint8 ACEquiIDhigh = (ACEquiID & 0x00ff0000) >> 16 ;
    quint8 ACEquiIDmid = (ACEquiID & 0x0000ff00) >> 8;
    quint8 ACEquiIDlow = (ACEquiID & 0x000000ff);

    QByteArray sendbuff;

    sendbuff[0] = 0xa5;sendbuff[1] = 0x5a;//帧头
    sendbuff[2] = 0x00;
    sendbuff[3] = 0x0d;//帧长度
    sendbuff[4] = 0x01;//版本号
    sendbuff[5] = 0x08;//帧类型

    quint32 groupIDhigh = (_groupID & 0x00ff0000) >> 16 ;
    quint32 groupIDmid = (_groupID & 0x0000ff00) >> 8;
    quint32 groupIDlow = (_groupID & 0x000000ff);

    quint32 Equihigh = (_equi & 0x00ff0000) >> 16 ;
    quint32 Equimid = (_equi & 0x0000ff00) >> 8;
    quint32 Equilow = (_equi & 0x000000ff);

    sendbuff[6] = quint32ToHex(groupIDhigh);
    sendbuff[7] = quint32ToHex(groupIDmid);
    sendbuff[8] = quint32ToHex(groupIDlow);//群组编号

    sendbuff[9] = quint32ToHex(Equihigh);
    sendbuff[10] = quint32ToHex(Equimid);
    sendbuff[11] = quint32ToHex(Equilow);//设备编号

    for(int i=0;i<8;i++){

        sendbuff[12] = i;//输出通道号 继电器板是：0-7
        if(flag){
            sendbuff[13] = 0x01;//信息段
        }else{
            sendbuff[13] = 0x00;//信息段
        }
        sendbuff[14] = ACEquiIDhigh;//采集端设备编号
        sendbuff[15] = ACEquiIDmid;
        sendbuff[16] = ACEquiIDlow;
        sendbuff[17] = checkSum(sendbuff,17);//校验和
        sendbuff[18] = 0xc3;sendbuff[19] = 0x3c;//帧尾

        m_OrderOpenSenderdata.append(sendbuff);

    }
    if(flag){
        m_OrderOpenTimer->start(50);
    }
}

void AcquisitionPort::changeOrderCloseRelayStatus(bool flag)
{
    if(m_OrderOpenTimer != NULL){
        if(m_OrderOpenTimer->isActive()){
            m_OrderOpenTimer->stop();
        }
    }
    //获取采集板号 设备号
    quint32 ACEquiID = 0;
    ACEquiID = getId();
    quint32 _groupID = getgroupID();
    quint32 _equi = 0;


    quint8 ACEquiIDhigh = (ACEquiID & 0x00ff0000) >> 16 ;
    quint8 ACEquiIDmid = (ACEquiID & 0x0000ff00) >> 8;
    quint8 ACEquiIDlow = (ACEquiID & 0x000000ff);

    QByteArray sendbuff;

    sendbuff[0] = 0xa5;sendbuff[1] = 0x5a;//帧头
    sendbuff[2] = 0x00;
    sendbuff[3] = 0x0d;//帧长度
    sendbuff[4] = 0x01;//版本号
    sendbuff[5] = 0x08;//帧类型

    quint32 groupIDhigh = (_groupID & 0x00ff0000) >> 16 ;
    quint32 groupIDmid = (_groupID & 0x0000ff00) >> 8;
    quint32 groupIDlow = (_groupID & 0x000000ff);

    quint32 Equihigh = (_equi & 0x00ff0000) >> 16 ;
    quint32 Equimid = (_equi & 0x0000ff00) >> 8;
    quint32 Equilow = (_equi & 0x000000ff);

    sendbuff[6] = quint32ToHex(groupIDhigh);
    sendbuff[7] = quint32ToHex(groupIDmid);
    sendbuff[8] = quint32ToHex(groupIDlow);//群组编号

    sendbuff[9] = quint32ToHex(Equihigh);
    sendbuff[10] = quint32ToHex(Equimid);
    sendbuff[11] = quint32ToHex(Equilow);//设备编号

    for(int i=0;i<8;i++){

        sendbuff[12] = i;//输出通道号 继电器板是：0-7
        if(flag){
            sendbuff[13] = 0x00;//信息段
        }else{
            sendbuff[13] = 0x00;//信息段
        }
        sendbuff[14] = ACEquiIDhigh;//采集端设备编号
        sendbuff[15] = ACEquiIDmid;
        sendbuff[16] = ACEquiIDlow;
        sendbuff[17] = checkSum(sendbuff,17);//校验和
        sendbuff[18] = 0xc3;sendbuff[19] = 0x3c;//帧尾

        m_OrderCloseSenderdata.append(sendbuff);
    }
    if(flag){
        m_OrderCloseTimer->start(50);
    }
}

void AcquisitionPort::changeCircularRelayStatus()
{

}

void AcquisitionPort::setChannel_1Value(quint16 value)
{
    m_channel_1value = value;
}

quint16 AcquisitionPort::getChannel_1Value() const
{
    return m_channel_1value;
}

void AcquisitionPort::setChannel_2Value(quint16 value)
{
    m_channel_2value = value;
}

quint16 AcquisitionPort::getChannel_2Value() const
{
    return m_channel_2value;
}

void AcquisitionPort::setChannel_3Value(quint16 value)
{
    m_channel_3value = value;
}

quint16 AcquisitionPort::getChannel_3Value() const
{
    return m_channel_3value;
}

void AcquisitionPort::setChannel_4Value(quint16 value)
{
    m_channel_4value = value;
}

quint16 AcquisitionPort::getChannel_4Value() const
{
    return m_channel_4value;
}

void AcquisitionPort::setChannel_5Value(quint16 value)
{
    m_channel_5value = value;
}

quint16 AcquisitionPort::getChannel_5Value() const
{
    return m_channel_5value;
}

void AcquisitionPort::setChannel_6Value(quint16 value)
{
    m_channel_6value = value;
}

quint16 AcquisitionPort::getChannel_6Value() const
{
    return m_channel_6value;
}

void AcquisitionPort::setChannel_7Value(quint16 value)
{
    m_channel_7value = value;
}

quint16 AcquisitionPort::getChannel_7Value() const
{
    return m_channel_7value;
}

void AcquisitionPort::setChannel_8Value(quint16 value)
{
    m_channel_8value = value;
}

quint16 AcquisitionPort::getChannel_8Value() const
{
    return m_channel_8value;
}

void AcquisitionPort::setChannel_9Value(quint64 value)
{
    m_channel_9value = value;
}

quint64 AcquisitionPort::getChannel_9Value() const
{
    return m_channel_9value;
}

void AcquisitionPort::setChannel_10Value(quint64 value)
{
    m_channel_10value = value;
}

quint64 AcquisitionPort::getChannel_10Value() const
{
    return m_channel_10value;
}

void AcquisitionPort::setChannel_11Value(quint8 value)
{
    m_channel_11value = value;
}

quint8 AcquisitionPort::getChannel_11Value() const
{
    return m_channel_11value;
}

void AcquisitionPort::setChannel_12Value(quint8 value)
{
    m_channel_12value = value;
}

quint8 AcquisitionPort::getChannel_12Value() const
{
    return m_channel_12value;
}

void AcquisitionPort::setChannel_13Value(quint8 value)
{
    m_channel_13value = value;
}

quint8 AcquisitionPort::getChannel_13Value() const
{
    return m_channel_13value;
}

void AcquisitionPort::setChannel_14Value(quint8 value)
{
    m_channel_14value = value;
}

quint8 AcquisitionPort::getChannel_14Value() const
{
    return m_channel_14value;
}

void AcquisitionPort::setChannel_15Value(quint8 value)
{
    m_channel_15value = value;
}

quint8 AcquisitionPort::getChannel_15Value() const
{
    return m_channel_15value;
}

void AcquisitionPort::setChannel_16Value(quint8 value)
{
    m_channel_16value = value;
}

quint8 AcquisitionPort::getChannel_16Value() const
{
    return m_channel_16value;
}

void  AcquisitionPort::setACID(int i)
{
    m_i=i;
}

int AcquisitionPort::getACID()
{
    return m_i;
}

void AcquisitionPort::setacPortnotonline()
{
    qDebug()<<tr("acPort Number=")<<"222222222"<<getId();
    QTimer *timer = qobject_cast<QTimer*>(sender());
    if(timer == m_BadTimer){
        setOnline(false);
        m_redata.clear();
        return ;
    }
}

void AcquisitionPort::slotmytimer()
{
    QTimer *timer = qobject_cast<QTimer*>(sender());
    if(timer == m_OrderOpenTimer){
        if(m_OrderOpencount == 8){
            m_OrderOpencount = 0;
        }
        m_OrderOpencount ++;
        emit signalwriteSerialPort(m_OrderOpenSenderdata[m_OrderOpencount-1]);
    }else if(timer == m_OrderCloseTimer){
        if(m_OrderClosecount == 8){
            m_OrderClosecount = 0;
        }
        m_OrderClosecount ++;
        emit signalwriteSerialPort(m_OrderCloseSenderdata[m_OrderClosecount-1]);
    }
}

quint8 AcquisitionPort::checkSum(QByteArray data, quint16 length)
{
    quint8 sum=0;//quint8 is means low 8byte
    quint16 i;
    for(i = 0;i < length; i++){
        sum += (uchar)data.at(i);
    }
    QString strx;
    strx = QString("%1").arg(sum, 0, 16);
//    quint8 low = (quint8)hexToDec(strx.toUpper().toLocal8Bit().data());
    //    qDebug()<<"strx="<<QString("%1").arg(low, 0, 16).toUpper();
    return sum;
}

quint16 AcquisitionPort::hexToDec(char *data)
{
    char* endptr;
    quint16 lnumber;
    /* strtol converts string to long integer */
    lnumber = strtol(data, &endptr, 16);
    //    qDebug()<<"lnumber="<<lnumber;
    return lnumber;
}

quint16 AcquisitionPort::quint32ToHex(quint32 data)
{
    QString strx;
    strx = QString("%1").arg(data, 0, 16);
    quint16 low = (quint16)hexToDec(strx.toUpper().toLocal8Bit().data());
    //    qDebug()<<"quint16 low"<<QString("%1").arg(low, 0, 16).toUpper().toLocal8Bit();
    return low;
}
