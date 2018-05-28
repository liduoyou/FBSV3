#include "QZigbeeThread.h"
#include <QDebug>
#include <QByteArray>
#include <QDateTime>
#include <QTimer>
#include <stdio.h>
#include <QStringList>
#include "../Settings/SettingsManager.h"
#include "../Component/CommonNotify.h"
#include "../AcquisitionPort/AcquisitionPortManager.h"
#include "../AcquisitionPort/AcquisitionPort.h"
#include "../MainWidget.h"
#include "../DataHeaderDefine.h"
//#define DEV "/dev/ttySAC0"
#define DEV "/dev/ttyUSB0"
QByteArray definedata;
quint8 status0 = 0;
quint8 status1 = 0;
quint8 status2 = 0;
quint8 status3 = 0;
quint8 status4 = 0;
quint8 status5 = 0;
quint8 status6 = 0;
quint8 status7 = 0;
quint8 statusLimitSwitch = 0;
bool   PLCOnlineStatus = false;
QZigbeeThread::QZigbeeThread(QObject *parent) :
    QThread(parent)
  , _handshake_flag(0)
  , m_Timerout(NULL)
  , m_timeflag(false)
  , m_array(0)
  , isSendData(NULL)
  , m_sendDataTimer(NULL)
{
    //init serial port
    m_pSerial = new Posix_QextSerialPort(DEV,QextSerialBase::Polling);//串口设备号

    if(m_pSerial != NULL){
        m_pSerial->setBaudRate(BAUD38400);
        m_pSerial->setDataBits(DATA_8);
        m_pSerial->setStopBits(STOP_1);
        m_pSerial->setParity(PAR_NONE);

        m_pSerial->setFlowControl(FLOW_OFF);
        m_pSerial->setTimeout(10);

        if(m_pSerial->open(QIODevice::ReadWrite)){
            qDebug(DEV);
        }
    }
    setObjectName("QZigbeeThread");
    m_array.resize(512);
    for(int i=0;i<m_array.size();i++){
        m_array[i] = 0x00;
    }
    _equi = (quint32)SettingsManager::globalInstance()->getSysBaseInfor(tr("EquiNumber")).toInt();
    _groupID = (quint32)SettingsManager::globalInstance()->getGroupID().toUInt();

    m_sensorTypeacPort = AcquisitionPortManager::globalInstance()->getSensorTypeList();
    m_switchValueacPort = AcquisitionPortManager::globalInstance()->getSwitchValueList();

    m_Timerout = new QTimer();
    connect(m_Timerout,SIGNAL(timeout()),this,SLOT(waittimeout()));

    m_sendDataTimer = new QTimer();
    connect(m_sendDataTimer,SIGNAL(timeout()),this,SLOT(sendToUpdate()));
//    m_sendDataTimer->start(500);

//    connect(m_pSerial,SIGNAL(signalSendData(QByteArray)),this,SLOT(receiveData(QByteArray)));
}

QZigbeeThread::~QZigbeeThread()
{
    qDebug()<<"QZigbeeThread::~QZigbeeThread()";
}

void QZigbeeThread::run()
{
    //init
    QByteArray datagram;
    QByteArray buffer;
    QByteArray switch_buffer;
    int temp;
    int size = -1;//datagram 计数
    int buf_size = -1;//buffer 计数
    int s_buf_size = -1;//switch_buffer 计数

    while(1){
        datagram = m_pSerial->readAll();
//        qDebug()<<"datagram.size="<<datagram.size();
        msleep(1);
        size = datagram.size();
        if(size == 0 || size < 47){
            if(size < 47){
                for(int i = 0;i < size;i++){
                    if((quint8)datagram.at(i) != 0xA5){
                        switch_buffer.clear();
                        continue;
                    }
                    temp = i;
                    switch_buffer.append(0xA5);
                    if((quint8)datagram.at(i+1) == 0x5A){
                        switch_buffer.append(0x5A);
                    }
                    if(size >= temp+17){
                        if(!((quint8)datagram.at(temp+17-1)) == 0x3C || !((quint8)datagram.at(temp+17-2) == 0xC3)){
                            datagram.clear();
                            switch_buffer.clear();
                            size = 0;
                            temp = 0;
                            continue;
                        }
                        for(int k = temp+2;k<temp+17;k++){
                            if(switch_buffer.size() < 17){
                                switch_buffer.append((quint8)datagram.at(k));
                            }
                        }
                        datagram.clear();
                        size = 0;
                        temp = 0;
                        break;
                    }
                }
                if(switch_buffer.size() == 17){
                    s_buf_size = switch_buffer.size();
                    if((quint8)switch_buffer.at(s_buf_size-1) == 0x3C){	  	//查帧尾
                        if(((quint8)switch_buffer.at(s_buf_size-2) == 0xC3))
                        {
                            QMutex mutex;
                            if((quint8)switch_buffer.at(s_buf_size-3) == checkSum(switch_buffer,(s_buf_size-3)))
                            {
                                mutex.lock();
                                dealData(switch_buffer,s_buf_size);
                                mutex.unlock();
                            }
                            switch_buffer.clear();
                            s_buf_size = 0;
                        }
                    }
                }//滤帧尾  C3 3C结束
            }
            continue;
        }

        if(size >= 47){
            for(int i = 0;i < size;i++){
                if((quint8)datagram.at(i) != 0xA5){//滤帧头  A5 5A
                    buffer.clear();
                    continue;
                }
                temp = i;
                buffer.append(0xA5);
                if((quint8)datagram.at(i+1) == 0x5A){
                    buffer.append(0x5A);
                }
                if(size >= temp+47){
                    if(!((quint8)datagram.at(temp+47-1)) == 0x3C || !((quint8)datagram.at(temp+47-2) == 0xC3)){
                        datagram.clear();
                        buffer.clear();
                        size = 0;
                        temp = 0;
                        continue;
                    }
                    for(int k = temp+2;k<temp+47;k++){
                        if(buffer.size() < 47){
                            buffer.append((quint8)datagram.at(k));
                        }
                    }
//                    for(int j=0;j<47;j++){
//                        quint8 sum = (quint8)buffer.at(j);
//                        qDebug()<<"quint8[="<<j<<"]"<<QString("%1").arg(sum, 0, 16).toUpper();
//                    }
                    datagram.clear();
                    size = 0;
                    temp = 0;
                    break;
                }
            }
        }
        if(buffer.size() == 47){ //对于大于6的长度的 才去检查通信的完整性 ,帧尾是 C3 3C
            buf_size = buffer.size();
//            for(int j=0;j<47;j++){
//                quint8 sum = (quint8)buffer.at(j);
//                qDebug()<<"xxxxxxxxxquint8[="<<j<<"]"<<QString("%1").arg(sum, 0, 16).toUpper();
//            }

            if((quint8)buffer.at(buf_size-1) == 0x3C){	  	//查帧尾
                if(((quint8)buffer.at(buf_size-2) == 0xC3))
                {
                    //如果通过了和校验，才进入处理
                    QMutex mutex;
                    //                    qDebug()<<"(quint8)buffer.at(buf_size-3)"<<(quint8)buffer.at(buf_size-3);
                    if((quint8)buffer.at(buf_size-3) == checkSum(buffer,(buf_size-3)))
                    {
                        //首先进行对通信的处理
                        //                        qDebug()<<"goto dealData()";
                        mutex.lock();
                        dealData(buffer,buf_size);
                        mutex.unlock();
                    }
                    buffer.clear();
                    buf_size = 0;
                }
            }
        }//滤帧尾  C3 3C结束
    }
    m_pSerial->close();
}

void QZigbeeThread::readByteData()
{

}

void QZigbeeThread::dealData(QByteArray data, int count)
{
//    qDebug()<<"one data Total size"<<count;
    switch((quint8)data.at(5))
    {
    case 0x00:{
//        qDebug("get into case 0x00");

        if((quint8)data.at(12) == 0x00)
        {
            quint32 GroupID = 0;//群组编号
            GroupID=setbitdata(0,(uchar)data.at(6),(uchar)data.at(7),(uchar)data.at(8));
            _groupID = (quint32)SettingsManager::globalInstance()->getGroupID().toUInt();//
            if(GroupID != _groupID){
                break;
            }

            quint32 AC_Equinum = 0;//采集端设备号
            quint8 AC_EquinumHigh = (uchar)data.at(9);
            quint8 AC_EquinumMid = (uchar)data.at(10);
            quint8 AC_EquinumLow = (uchar)data.at(11);
            AC_Equinum += AC_EquinumHigh;
            AC_Equinum <<= 8;
            AC_Equinum += AC_EquinumMid;
            AC_Equinum <<= 8;
            AC_Equinum += AC_EquinumLow;
            qDebug()<<"0x00 Equipment number:"<<AC_Equinum;

            int hold_res = 0,type = 0;

            if(AcquisitionPortManager::globalInstance()->getSensorTypeList().keys().contains(AC_Equinum)){
                if(AcquisitionPortManager::globalInstance()->getSensorTypeList().value(AC_Equinum)->getHandShackFlag() == 1)
                {
                    hold_res = 1;  /* have been handshack */
                }
                type = 1;
            }else if(AcquisitionPortManager::globalInstance()->getSwitchValueList().keys().contains(AC_Equinum)){
                if(AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->getHandShackFlag() == 1)
                {
                    hold_res = 1;
                }
                type = 2;
            }else{
                hold_res = 2;//错误
            }
            if(hold_res == 0)//未握手
            {
                if(type == 1){
                    AcquisitionPortManager::globalInstance()->getSensorTypeList().value(AC_Equinum)->setId(AC_Equinum);
                    AcquisitionPortManager::globalInstance()->getSensorTypeList().value(AC_Equinum)->setHandShackFlag(1);//set 已握手
                    AcquisitionPortManager::globalInstance()->getSensorTypeList().value(AC_Equinum)->setOnline(true);
                    emit updateAcquisitionStatus();
                }else if(type == 2){
                    AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->setId(AC_Equinum);
                    AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->setHandShackFlag(1);//set 已握手
                    AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->setOnline(true);
                    emit updateAcquisitionStatus();
                }
            }

            quint32 tmp = 0;
            QDateTime datetime = QDateTime::currentDateTime();
            quint8 year = datetime.toString("yyyy").toInt() - 2010;
            quint8 month = datetime.toString("MM").toInt();
            quint8 day = datetime.toString("dd").toInt();
            quint8 hour = datetime.toString("hh").toInt();
            quint8 minutes = datetime.toString("mm").toInt();
            quint8 seconds = datetime.toString("ss").toInt();

            year <<= 2;tmp += year;tmp <<= 6;
            month <<= 4;tmp += month;tmp <<= 4;
            day <<= 3;tmp += day;tmp <<= 5;
            hour <<= 3;tmp += hour;tmp <<= 5;
            minutes <<= 2;tmp += minutes;tmp <<= 4;
            tmp += seconds;

            quint32 high1 = (tmp & 0xff000000) >> 24;
            quint32 high2 = (tmp & 0x00ff0000) >> 16 ;
            quint32 low1 = (tmp & 0x0000ff00) >> 8;
            quint32 low2 = (tmp & 0x000000ff);

            QByteArray sendbuff;

            sendbuff[0] = 0xA5;sendbuff[1] = 0x5A;//帧头
            sendbuff[2] = 0x00;sendbuff[3] = 0x0D;//帧长度
            sendbuff[4] = 0x01;//版本号
            sendbuff[5] = 0x01;//帧类型

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
            sendbuff[12] = hold_res;//下位机开机后主动发出握手信息,上位机返回结果
            sendbuff[13] = quint32ToHex(high1);
            sendbuff[14] = quint32ToHex(high2);
            sendbuff[15] = quint32ToHex(low1);
            sendbuff[16] = quint32ToHex(low2);//信息段
            sendbuff[17] = checkSum(sendbuff,17);//校验和
            sendbuff[18] = 0xc3;sendbuff[19] = 0x3c;//帧尾

            m_pSerial->write(sendbuff);//发送数据
        }else
            break;
    }break;
    case 0x02:{ //采集板  47 字节
//        qDebug("get into case 0x02");
        quint32 GroupID = 0;//群组编号
        GroupID=setbitdata(0,(uchar)data.at(6),(uchar)data.at(7),(uchar)data.at(8));
        _groupID = (quint32)SettingsManager::globalInstance()->getGroupID().toUInt();//
//        qDebug()<<"GroupID = "<<GroupID<<"_groupID = "<<_groupID;
        if(GroupID != _groupID){
            break;
        }
        quint32 AC_Equinum = 0;//采集端设备号
        AC_Equinum=setbitdata(0,(uchar)data.at(9),(uchar)data.at(10),(uchar)data.at(11));
        if(AcquisitionPortManager::globalInstance()->getSensorTypeList().keys().contains(AC_Equinum)){
            AcquisitionPortManager::globalInstance()->getSensorTypeList().value(AC_Equinum)->setId(AC_Equinum);
            AcquisitionPortManager::globalInstance()->getSensorTypeList().value(AC_Equinum)->setgroupID(_groupID);
            AcquisitionPortManager::globalInstance()->getSensorTypeList().value(AC_Equinum)->setOnline(true);
            AcquisitionPortManager::globalInstance()->getSensorTypeList().value(AC_Equinum)->setreData(data);
        }else{
            break;
        }
    }break;
    case 0x04:{
        //        qDebug("get into case 0x04");
        quint32 GroupID = 0;//群组编号
        GroupID=setbitdata(0,(uchar)data.at(6),(uchar)data.at(7),(uchar)data.at(8));
        _groupID = (quint32)SettingsManager::globalInstance()->getGroupID().toUInt();//
        //        qDebug()<<"0x00 GroupID number:"<<GroupID;
        if(GroupID != _groupID){
            break;
        }
        quint32 AC_Equinum = 0;//采集端设备号
        AC_Equinum=setbitdata(0,(uchar)data.at(9),(uchar)data.at(10),(uchar)data.at(11));
        if(AcquisitionPortManager::globalInstance()->getSensorTypeList().keys().contains(AC_Equinum)){
            AcquisitionPortManager::globalInstance()->getSensorTypeList().value(AC_Equinum)->setOnline(true);
        }else{
            break;
        }
        quint16 temp = 0;
        quint8 low = (uchar)data.at(12);
        quint8 high = (uchar)data.at(13);
        temp += high;temp <<= 8;
        temp += low;
        //        emit sendSensorCalValue(QString::number(temp,10));
        //        m_timeflag = true;

    }break;
    case 0x05:{ // 开关板的数据  在m_array中同样分配了32个字节(实际只有24 字节)
//        qDebug("get into case 0x05");
        quint32 GroupID = 0;//群组编号
        GroupID=setbitdata(0,(uchar)data.at(6),(uchar)data.at(7),(uchar)data.at(8));
        _groupID = (quint32)SettingsManager::globalInstance()->getGroupID().toUInt();//
//        qDebug()<<"GroupID = "<<GroupID<<"_groupID = "<<_groupID;
        if(GroupID != _groupID){
            break;
        }
        quint32 AC_Equinum = 0;//采集板子编号
        AC_Equinum=setbitdata(0,(uchar)data.at(9),(uchar)data.at(10),(uchar)data.at(11));
//        qDebug()<<"AC_Equinum="<<AC_Equinum;
        if(AcquisitionPortManager::globalInstance()->getSwitchValueList().keys().contains(AC_Equinum)){
            AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->setId(AC_Equinum);
            AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->setgroupID(_groupID);
            AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->setOnline(true);
            AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->setreData(data);
        }else{
            break;
        }
    }break;
    case 0x07:{
        qDebug("get into case 0x07");
        quint32 GroupID = 0;//群组编号
        GroupID=setbitdata(0,(uchar)data.at(6),(uchar)data.at(7),(uchar)data.at(8));
        qDebug()<<"0x00 GroupID number:"<<GroupID;
        if(GroupID != _groupID){
            break;
        }
        quint32 AC_Equinum = 0;//采集端设备号
        AC_Equinum=setbitdata(0,(uchar)data.at(9),(uchar)data.at(10),(uchar)data.at(11));
        if(AcquisitionPortManager::globalInstance()->getSwitchValueList().keys().contains(AC_Equinum)){
            if(!(AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->getOnline()))
            {
                AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->setOnline(true);
                //                emit updateAcquisitionStatus();
            }
        }else{
            break;
        }
    }break;
    case 0x09:{
        //        qDebug("get into case 0x09");

        quint32 GroupID = 0;//群组编号
        GroupID=setbitdata(0,(uchar)data.at(6),(uchar)data.at(7),(uchar)data.at(8));
        //        qDebug()<<"0x00 GroupID number:"<<GroupID;
        if(GroupID != _groupID){
            break;
        }
        quint32 AC_Equinum = 0;//采集端设备号
        AC_Equinum=setbitdata(0,(uchar)data.at(9),(uchar)data.at(10),(uchar)data.at(11));
        if(AcquisitionPortManager::globalInstance()->getSwitchValueList().keys().contains(AC_Equinum)){
            if(!(AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->getOnline()))
            {
                AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->setOnline(true);
                //                emit updateAcquisitionStatus();
            }
        }else{
            break;
        }

        quint8 channelIDValue = 0;//单个继电器状态 return
        channelIDValue = (uchar)data.at(12);
        if(channelIDValue == 0){
            qDebug()<<"right"<<channelIDValue;//0 - 正确
        }else if(channelIDValue == 1){
            qDebug()<<"error"<<channelIDValue;//1 - 错误
        }

    }break;
    case 0x0B:{
        qDebug("get into case 0x0B");

        quint32 GroupID = 0;//群组编号
        GroupID=setbitdata(0,(uchar)data.at(6),(uchar)data.at(7),(uchar)data.at(8));
        qDebug()<<"0x00 GroupID number:"<<GroupID;
        if(GroupID != _groupID){
            break;
        }
        quint32 AC_Equinum = 0;//采集端设备号
        AC_Equinum=setbitdata(0,(uchar)data.at(9),(uchar)data.at(10),(uchar)data.at(11));
        if(AcquisitionPortManager::globalInstance()->getSwitchValueList().keys().contains(AC_Equinum)){
            if(!(AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->getOnline()))
            {
                AcquisitionPortManager::globalInstance()->getSwitchValueList().value(AC_Equinum)->setOnline(true);
                //                emit updateAcquisitionStatus();
            }
        }else{
            break;
        }

        quint8 channelIDValue = 0;//所有继电器状态 return
        channelIDValue = (uchar)data.at(12);

        if(channelIDValue == 0){
            qDebug()<<"success"<<channelIDValue;//设置结果 成功 - 0
        }else if(channelIDValue == 1){
            qDebug()<<"failed"<<channelIDValue;//设置结果 成功 - 1
        }
    }break;
    default:
        break;
    }
}

void QZigbeeThread::writeDataToSerial(QByteArray data, int count)
{
    Q_UNUSED(count)
    switch((quint8)data.at(5)){
    case 0x03:{
        qDebug("get into case 0x03");
        m_pSerial->write(data);//发送数据
        if(m_Timerout->isActive()){
            m_Timerout->stop();
        }
        m_Timerout->start(3000);
    }break;
    case 0x06:{
        qDebug("get into case 0x06");
        m_pSerial->write(data);//发送数据
        if(m_Timerout->isActive()){
            m_Timerout->stop();
        }
        m_Timerout->start(3000);
    }break;
    case 0x08:{
//        qDebug("get into case 0x08");
        m_pSerial->write(data);//发送数据
    }break;
    case 0x0A:{
//        qDebug("get into case 0x0A");
        m_pSerial->write(data);//发送数据
//        for(int i;i<data.size();i++){
//            quint8 sum = (quint8)data.at(i);
//            qDebug()<<"zzzzzzzzquint8[="<<i<<"]"<<QString("%1").arg(sum, 0, 16).toUpper();
//        }
    }break;
    default:
        break;
    }
}

quint8 QZigbeeThread::checkSum(QByteArray data, quint16 length)
{
    quint8 sum=0;//quint8 is means low 8byte
    quint16 i;
    for(i = 0;i < length; i++){
        sum += (uchar)data.at(i);
    }
//    qDebug()<<"sum"<<sum;
    QString strx;
    strx = QString("%1").arg(sum, 0, 16);
    quint8 low = (quint8)hexToDec(strx.toUpper().toLocal8Bit().data());
//    qDebug()<<"strx="<<QString("%1").arg(low, 0, 16).toUpper();
    return sum;
}

quint16 QZigbeeThread::hexToDec(char *data)
{
    char* endptr;
    quint16 lnumber;
    /* strtol converts string to long integer */
    lnumber = strtol(data, &endptr, 16);
//    qDebug()<<"lnumber="<<lnumber;
    return lnumber;
}

quint16 QZigbeeThread::quint32ToHex(quint32 data)
{
    QString strx;
    strx = QString("%1").arg(data, 0, 16);
    quint16 low = (quint16)hexToDec(strx.toUpper().toLocal8Bit().data());
//    qDebug()<<"quint16 low"<<QString("%1").arg(low, 0, 16).toUpper().toLocal8Bit();
    return low;
}

void QZigbeeThread::waittimeout()
{
    if(m_timeflag){
        //接收到数据
        m_timeflag = false;
    }else{
        //请求超时
//        CommonNotify::instance()->messageBox(tr("读取失败"),tr("请求超时"));
        m_timeflag = false;
    }
    if(m_Timerout->isActive()){
        m_Timerout->stop();
    }
}

void QZigbeeThread::sendToUpdate()
{
    emit sendAcquisitionData(m_array);
}

void QZigbeeThread::setacPortnotonline()
{
}

quint32 QZigbeeThread::setbitdata(quint8 High1, quint8 High2, quint8 Low1, quint8 Low2)
{
    quint32 data=0;
    data += High1;
    data<<=8;
    data+=High2;
    data<<=8;
    data+=Low1;
    data<<=8;
    data+=Low2;
    return data;
}

void QZigbeeThread::receiveData(QByteArray revData)
{
    qDebug()<<"ddddddddddddddddd";
    qDebug()<<"yyyyyyyyyyyy  revData.size() = "<<revData.size();
    QString str;
    for(int i=0;i<revData.size();i++){
        quint8 sum = (quint8)revData.at(i);
        if(i == (revData.size() - 1)){
            str += QString("%1").arg(sum, 0, 16).toUpper().size() == 1?
                        QString("0%1").arg(sum, 0, 16).toUpper():
                        QString("%1").arg(sum, 0, 16).toUpper();
        }else{
            str += QString("%1").arg(sum, 0, 16).toUpper().size() == 1?
                        QString("0%1").arg(sum, 0, 16).toUpper()+" ":
                        QString("%1").arg(sum, 0, 16).toUpper()+" ";
        }
    }
    qDebug()<<"xxxxxxxxxstr"<<str;
    str.clear();
}
