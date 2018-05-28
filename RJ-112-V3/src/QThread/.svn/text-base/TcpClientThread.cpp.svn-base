#include "TcpClientThread.h"
#include <QDebug>
#include <QNetworkInterface>
#include <QAbstractSocket>
//#include "../Test/FuncTime.h"
#include <QAbstractSocket>
#include "./src/DataHeaderDefine.h"
TcpClientThread::TcpClientThread(QObject *parent) :
    QThread(parent)
  , tcpSocket(NULL)
  , m_sendDataTimer(NULL)
  , m_timer1(NULL)
  , _connectStatus(false)
{
    ipAddress = "192.168.1.188";

    m_array.resize(512);
    for(int i=0;i<m_array.size();i++){
        m_array[i] = 0x00;
    }

    m_AreaData.resize(40);
    for(int i=0;i<m_AreaData.size();i++){
        m_AreaData[i] = 0x00;
    }
    blockSize = 0;


    tcpSocket = new QTcpSocket();
    newConnect();
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(Login()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()),Qt::DirectConnection);
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));

    m_sendDataTimer = new QTimer();
    connect(m_sendDataTimer,SIGNAL(timeout()),this,SLOT(sendToUpdate()));
    m_sendDataTimer->start(500);

    m_timer1 = new QTimer();
    connect(m_timer1,SIGNAL(timeout()),this,SLOT(reConnectSocket()));
    m_timer1->start(5000);

}

TcpClientThread::~TcpClientThread()
{
    tcpSocket->close();
    delete tcpSocket;
}

void TcpClientThread::run()
{
//    tcpSocket = new QTcpSocket();
//    newConnect();
//    connect(tcpSocket, SIGNAL(connected()), this, SLOT(Login()));
//    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()),Qt::DirectConnection);
//    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
//            this,SLOT(displayError(QAbstractSocket::SocketError)));

//    tcpSocket->moveToThread(this);

//    QMutex m_mutex;
    while(1){
//        FuncTime ft("TcpClientThread::run()   time");
//                {
        if(tcpSocket->state() == QAbstractSocket::ConnectedState)
        {
            writeDataToTcpServer(1);
        }

        if(tcpSocket->state() == QAbstractSocket::ConnectedState)
        {
            writeDataToTcpServer(2);
        }
        if(tcpSocket->state() == QAbstractSocket::ConnectedState)
        {
            writeDataToTcpServer(3);
        }
        msleep(1);

//        }
    }
}

void TcpClientThread::newConnect()//这个函数实现了连接到服务器，下面会在“连接”按钮的单击事件槽函数中调用这个函数。
{
    blockSize = 0; //初始化其为0
    tcpSocket->abort(); //取消已有的连接
    tcpSocket->connectToHost(ipAddress,
                             SERVERPORT,QIODevice::ReadWrite);
    //连接到主机，主机地址和端口号

    qDebug("per State:%d ",tcpSocket->state());   // State: 2; 2代表ConnectingState，正确的应该为3（ConnectedState）
    const int Timeout=1*1000;
    if(!tcpSocket->waitForConnected(Timeout))
    {
        qDebug()<<"wait for Connected Timeout";
        return;
    }
    qDebug("back State:%d ",tcpSocket->state()); // State: 3（ConnectedState）正确
}

bool TcpClientThread::Login()
{
    qint64 iRet;

    QByteArray send_buf;
    send_buf.resize(16);
    send_buf[0] = 0x03;//
    send_buf[1] = 0xFF;
    send_buf[2] = 0x08;
    send_buf[3] = 0x01;
    send_buf[4] = 0x00;
    send_buf[5] = 0x00;
    send_buf[6] = RWIQAREA;//读写I/Q区
    send_buf[7] = 0x00;
    send_buf[8] = 0x02;
    send_buf[9] = 0x00;//数据区  0x00: I区  / 0x01: Q区
    send_buf[10] = 0x00;
    send_buf[11] = 0x00;//起始地址
    send_buf[12] = 0x00;// unuse
    send_buf[13] = 0x10;//read 16 Byte
    send_buf[14] = 0x05;
    send_buf[15] = 0x01;

    if (!(iRet = tcpSocket->write(send_buf))==-1){
        qDebug()<<"successful";
        return false;
    }
    else{
        qDebug()<<"xxxxxxxxxx    failed";
        return true;
    }
}

void TcpClientThread::readMessage()
{
    /*这个函数实现了数据的接收，它与服务器端的发送函数相对应。首先我们要获取文件的大小信息，然后根据文件的大小来判断是否接收到了完整的文件。*/
//    QMutex mutex;
    if(blockSize==0) //如果是刚开始接收数据
    {

        message = tcpSocket->readAll();

        blockSize = message.size();

//        mutex.lock();
        saveTcpServerData(message,blockSize);
//        mutex.unlock();

        message.clear();
        blockSize = 0;
    }

    //print
#if 0
    for(int i=0;i<message.size();i++){
        quint8 sum = (quint8)message.at(i);
        qDebug()<<"quint8["<<i<<"]"<<QString("%1").arg(sum, 0, 16).toUpper();
    }
    dealTcpServerData(message);
#endif
}

void TcpClientThread::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<"error:"<<tcpSocket->errorString(); //输出错误信息
}

bool TcpClientThread::writeDataToTcpServer(int flag)
{
//    FuncTime ft("TcpClientThread::writeDataToTcpServer()   ");
//    {
    qint64 iRet;

    send_buf.resize(16);
    send_buf[0] = 0x03;//
    send_buf[1] = 0xFF;
    send_buf[2] = 0x08;

    if(flag == 1){//读写I区

        send_buf[3] = 0x01;
        send_buf[4] = 0x00;
        send_buf[5] = 0x00;
        send_buf[6] = RWIQAREA;//读写I区
        send_buf[7] = 0x00;
        send_buf[8] = 0x02;
        send_buf[9] = 0x00;//数据区  0x00: I区  / 0x01: Q区
        send_buf[10] = 0x00;
        send_buf[11] = 0x00;//起始地址
        send_buf[12] = 0x00;// unuse
        send_buf[13] = 0x10;//read 16 Byte
        send_buf[14] = 0x05;
        send_buf[15] = 0x01;

        if (!((iRet = tcpSocket->write(send_buf))==-1))
        {
            if(tcpSocket->waitForReadyRead(100)){
//                qDebug()<<"is Right";
            }else{
                qDebug()<<"is error";
            }
//            qDebug("III  Written State:%d ",tcpSocket->state());  // State: 3（ConnectedState）正确
            msleep(100);
//            qDebug()<<"III send_bu iRet = "<<iRet;

            return true;
        }
        else
            return false;

    }else if(flag == 2){//读写Q区

        send_buf[3] = 0x01;
        send_buf[4] = 0x00;
        send_buf[5] = 0x00;
        send_buf[6] = RWIQAREA;//读写Q区
        send_buf[7] = 0x00;
        send_buf[8] = 0x02;
        send_buf[9] = 0x01;//数据区  0x00: I区  / 0x01: Q区
        send_buf[10] = 0x00;
        send_buf[11] = 0x00;//起始地址
        send_buf[12] = 0x00;// unuse
        send_buf[13] = 0x04;//read 04 Byte
        send_buf[14] = 0x05;
        send_buf[15] = 0x01;

        if (!((iRet = tcpSocket->write(send_buf))==-1))
        {
            if(tcpSocket->waitForReadyRead(100)){
//                qDebug()<<"is Right";
            }else{
                qDebug()<<"is error";
            }
//            qDebug("QQQ   Written State:%d ",tcpSocket->state());  // State: 3（ConnectedState）正确
            msleep(100);
//            qDebug()<<"QQQ   send_bu iRet = "<<iRet;
            return true;
        }
        else
            return false;

    }else if(flag == 3){//读写M区

        send_buf[3] = 0x01;
        send_buf[4] = 0x00;
        send_buf[5] = 0x00;
        send_buf[6] = RWMAREA;//读写M区
        send_buf[7] = 0x00;
        send_buf[8] = 0x02;
        send_buf[9] = 0x00;
        send_buf[10] = 0x00;
        send_buf[11] = 0xc8;//起始地址
        send_buf[12] = 0x00;// unuse
        send_buf[13] = 0x10;//read 04 Byte
        send_buf[14] = 0x05;
        send_buf[15] = 0x01;

        if (!((iRet = tcpSocket->write(send_buf))==-1))
        {
            if(tcpSocket->waitForReadyRead(100)){
//                qDebug()<<"is Right";
            }else{
                qDebug()<<"is error";
            }
//            qDebug("MMM   Written State:%d ",tcpSocket->state());  // State: 3（ConnectedState）正确
            msleep(100);
//            qDebug()<<"MMM    send_bu iRet = "<<iRet;
            return true;
        }
        else
            return false;
    }
//    }
    return false;
}

void TcpClientThread::saveTcpServerData(QByteArray dealData, quint16 length)
{
//    FuncTime ft("TcpClientThread::saveTcpServerData()   ");
//    {
    int size = length;
    QMutex mutex;
    quint8 startbyte = 16;  //该变量用来判断接收数据从第几个字节开始判断、分析；
    if(size >= 16){
        if(((quint8)dealData.at(0) == 0xFF) && (dealData.at(1) == 0x03)){
            switch (dealData.at(4)) {
            case RWIQAREA://读写I/Q区
            {
                if(dealData.at(9) == 0x00){//读写I区
//                    if((dealData.at(2) == 0x18) && dealData.at(3) == counter){
                    if((quint8)dealData.at(2) == 0x18){//0x08+读取数据字节数  data slength
#if 1
                        mutex.lock();
                        for(int i = 0;i < 16;i++){
                            m_AreaData[i] = (quint8)dealData.at(startbyte+i);
                        }
                        mutex.unlock();
#endif
#if 0
                        m_array[0] = (quint8)dealData.at(startbyte+0) & 0x01;//相序保护
                        m_array[1] = ((quint8)dealData.at(startbyte+0) & 0x02) >> 1;//主接触器反馈
                        m_array[2] = ((quint8)dealData.at(startbyte+0) & 0x04) >> 2;//起升1空开
                        m_array[3] = ((quint8)dealData.at(startbyte+0) & 0x08) >> 3;//起升1制动
                        m_array[4] = ((quint8)dealData.at(startbyte+0) & 0x10) >> 4;//起升1故障
                        m_array[5] = ((quint8)dealData.at(startbyte+0) & 0x20) >> 5;//起升2空开
                        m_array[6] = ((quint8)dealData.at(startbyte+0) & 0x40) >> 6;//起升2制动
                        m_array[7] = ((quint8)dealData.at(startbyte+0) & 0x80) >> 7;//起升2故障

                        m_array[8] = (quint8)dealData.at(startbyte+1) & 0x01;//起升3空开
                        m_array[9] = ((quint8)dealData.at(startbyte+1) & 0x02) >> 1;//起升3制动
                        m_array[10] = ((quint8)dealData.at(startbyte+1) & 0x04) >> 2;//起升3故障
                        m_array[11] = ((quint8)dealData.at(startbyte+1) & 0x08) >> 3;//起升4空开
                        m_array[12] = ((quint8)dealData.at(startbyte+1) & 0x10) >> 4;//起升4制动
                        m_array[13] = ((quint8)dealData.at(startbyte+1) & 0x20) >> 5;//起升4故障
                        m_array[14] = ((quint8)dealData.at(startbyte+1) & 0x40) >> 6;//小车1空开
                        m_array[15] = ((quint8)dealData.at(startbyte+1) & 0x80) >> 7;//小车1热继

                        //第2个字
                        m_array[16] = (quint8)dealData.at(startbyte+2) & 0x01;//小车1故障
                        m_array[17] = ((quint8)dealData.at(startbyte+2) & 0x02) >> 1;//小车2空开
                        m_array[18] = ((quint8)dealData.at(startbyte+2) & 0x04) >> 2;//小车2热继
                        m_array[19] = ((quint8)dealData.at(startbyte+2) & 0x08) >> 3;//小车2故障
                        m_array[20] = ((quint8)dealData.at(startbyte+2) & 0x10) >> 4;//刚腿空开
                        m_array[21] = ((quint8)dealData.at(startbyte+2) & 0x20) >> 5;//刚腿热继
                        m_array[22] = ((quint8)dealData.at(startbyte+2) & 0x40) >> 6;//刚腿故障
                        m_array[23] = ((quint8)dealData.at(startbyte+2) & 0x80) >> 7;//柔腿空开

                        m_array[24] = (quint8)dealData.at(startbyte+3) & 0x01;//柔腿热继
                        m_array[25] = ((quint8)dealData.at(startbyte+3) & 0x02) >> 1;//柔腿故障
                        m_array[26] = ((quint8)dealData.at(startbyte+3) & 0x04) >> 2;//卷筒空开
                        m_array[27] = ((quint8)dealData.at(startbyte+3) & 0x08) >> 3;//起升1上停止
                        m_array[28] = ((quint8)dealData.at(startbyte+3) & 0x10) >> 4;//起升1上减速
                        m_array[29] = ((quint8)dealData.at(startbyte+3) & 0x20) >> 5;//起升1下停止
                        m_array[30] = ((quint8)dealData.at(startbyte+3) & 0x40) >> 6;//起升1下减速
                        m_array[31] = ((quint8)dealData.at(startbyte+3) & 0x80) >> 7;//起升1超速

                        //第3个字
                        m_array[32] = (quint8)dealData.at(startbyte+4) & 0x01;//起升2上停止
                        m_array[33] = ((quint8)dealData.at(startbyte+4) & 0x02) >> 1;//起升2上减速
                        m_array[34] = ((quint8)dealData.at(startbyte+4) & 0x04) >> 2;//起升2下停止
                        m_array[35] = ((quint8)dealData.at(startbyte+4) & 0x08) >> 3;//起升2下减速
                        m_array[36] = ((quint8)dealData.at(startbyte+4) & 0x10) >> 4;//起升2超速
                        m_array[37] = ((quint8)dealData.at(startbyte+4) & 0x20) >> 5;//小车1前停止
                        m_array[38] = ((quint8)dealData.at(startbyte+4) & 0x40) >> 6;//小车1前减速
                        m_array[39] = ((quint8)dealData.at(startbyte+4) & 0x80) >> 7;//起升3上停止

                        m_array[40] = (quint8)dealData.at(startbyte+5) & 0x01;//起升3上减速
                        m_array[41] = ((quint8)dealData.at(startbyte+5) & 0x02) >> 1;//起升3下停止
                        m_array[42] = ((quint8)dealData.at(startbyte+5) & 0x04) >> 2;//起升3下减速
                        m_array[43] = ((quint8)dealData.at(startbyte+5) & 0x08) >> 3;//起升3超速
                        m_array[44] = ((quint8)dealData.at(startbyte+5) & 0x10) >> 4;//起升4上停止
                        m_array[45] = ((quint8)dealData.at(startbyte+5) & 0x20) >> 5;//起升4上减速
                        m_array[46] = ((quint8)dealData.at(startbyte+5) & 0x40) >> 6;//起升4下停止
                        m_array[47] = ((quint8)dealData.at(startbyte+5) & 0x80) >> 7;//起升4下减速

                        //第4个字
                        m_array[48] = (quint8)dealData.at(startbyte+6) & 0x01;//起升4超速
                        m_array[49] = ((quint8)dealData.at(startbyte+6) & 0x02) >> 1;//小车防撞
                        m_array[50] = ((quint8)dealData.at(startbyte+6) & 0x04) >> 2;//小车2后停止
                        m_array[51] = ((quint8)dealData.at(startbyte+6) & 0x08) >> 3;//小车2后减速
                        m_array[52] = ((quint8)dealData.at(startbyte+6) & 0x10) >> 4;//大车左限位
                        m_array[53] = ((quint8)dealData.at(startbyte+6) & 0x20) >> 5;//大车左减速
                        m_array[54] = ((quint8)dealData.at(startbyte+6) & 0x40) >> 6;//大车右限位
                        m_array[55] = ((quint8)dealData.at(startbyte+6) & 0x80) >> 7;//大车右减速

                        m_array[56] = (quint8)dealData.at(startbyte+7) & 0x01;//卷筒过紧
                        m_array[57] = ((quint8)dealData.at(startbyte+7) & 0x02) >> 1;//卷筒过松
                        m_array[58] = ((quint8)dealData.at(startbyte+7) & 0x04) >> 2;//大车左校准
                        m_array[59] = ((quint8)dealData.at(startbyte+7) & 0x08) >> 3;//大车右校准
                        m_array[60] = ((quint8)dealData.at(startbyte+7) & 0x10) >> 4;//备用
                        m_array[61] = ((quint8)dealData.at(startbyte+7) & 0x20) >> 5;//备用
                        m_array[62] = ((quint8)dealData.at(startbyte+7) & 0x40) >> 6;//备用
                        m_array[63] = ((quint8)dealData.at(startbyte+7) & 0x80) >> 7;//备用

                        //第5个字
                        m_array[64] = (quint8)dealData.at(startbyte+8) & 0x01;//备用
                        m_array[65] = ((quint8)dealData.at(startbyte+8) & 0x02) >> 1;//备用
                        m_array[66] = ((quint8)dealData.at(startbyte+8) & 0x04) >> 2;//备用
                        m_array[67] = ((quint8)dealData.at(startbyte+8) & 0x08) >> 3;//备用
                        m_array[68] = ((quint8)dealData.at(startbyte+8) & 0x10) >> 4;//备用
                        m_array[69] = ((quint8)dealData.at(startbyte+8) & 0x20) >> 5;//备用
                        m_array[70] = ((quint8)dealData.at(startbyte+8) & 0x40) >> 6;//备用
                        m_array[71] = ((quint8)dealData.at(startbyte+8) & 0x80) >> 7;//备用

                        m_array[72] = (quint8)dealData.at(startbyte+9) & 0x01;//备用
                        m_array[73] = ((quint8)dealData.at(startbyte+9) & 0x02) >> 1;//备用
                        m_array[74] = ((quint8)dealData.at(startbyte+9) & 0x04) >> 2;//备用
                        m_array[75] = ((quint8)dealData.at(startbyte+9) & 0x08) >> 3;//备用
                        m_array[76] = ((quint8)dealData.at(startbyte+9) & 0x10) >> 4;//备用
                        m_array[77] = ((quint8)dealData.at(startbyte+9) & 0x20) >> 5;//备用
                        m_array[78] = ((quint8)dealData.at(startbyte+9) & 0x40) >> 6;//备用
                        m_array[79] = ((quint8)dealData.at(startbyte+9) & 0x80) >> 7;//备用

                        //第6个字
                        m_array[80] = (quint8)dealData.at(startbyte+10) & 0x01;// //起升1.2上升
                        m_array[81] = ((quint8)dealData.at(startbyte+10) & 0x02) >> 1;    //起升1.2下降
                        m_array[82] = ((quint8)dealData.at(startbyte+10) & 0x04) >> 2; //起升1.2二档
                        m_array[83] = ((quint8)dealData.at(startbyte+10) & 0x08) >> 3; //起升1.2三档
                        m_array[84] = ((quint8)dealData.at(startbyte+10) & 0x10) >> 4; //起升1.2四档
                        m_array[85] = ((quint8)dealData.at(startbyte+10) & 0x20) >> 5;  //起升1选择
                        m_array[86] = ((quint8)dealData.at(startbyte+10) & 0x40) >> 6;     //起升2选择
                        m_array[87] = ((quint8)dealData.at(startbyte+10) & 0x80) >> 7;     //试灯

                        m_array[88] = (quint8)dealData.at(startbyte+11) & 0x01;//     // 起升3.4上升
                        m_array[89] = ((quint8)dealData.at(startbyte+11) & 0x02) >> 1;//起升3.4下降
                        m_array[90] = ((quint8)dealData.at(startbyte+11) & 0x04) >> 2;//起升3.4二档
                        m_array[91] = ((quint8)dealData.at(startbyte+11) & 0x08) >> 3;//起升3.4三档
                        m_array[92] = ((quint8)dealData.at(startbyte+11) & 0x10) >> 4;//起升3.4四档
                        m_array[93] = ((quint8)dealData.at(startbyte+11) & 0x20) >> 5;//起升3选择
                        m_array[94] = ((quint8)dealData.at(startbyte+11) & 0x40) >> 6;//起升4选择
                        m_array[95] = ((quint8)dealData.at(startbyte+11) & 0x80) >> 7;//起升3.4联吊

                        //第7个字
                        m_array[96] = (quint8)dealData.at(startbyte+12) & 0x01;//       //大车左行
                        m_array[97] = ((quint8)dealData.at(startbyte+12) & 0x02) >> 1; //大车右行
                        m_array[98] = ((quint8)dealData.at(startbyte+12) & 0x04) >> 2;  //大车二档
                        m_array[99] = ((quint8)dealData.at(startbyte+12) & 0x08) >> 3; //大车三档
                        m_array[100] = ((quint8)dealData.at(startbyte+12) & 0x10) >> 4;//大车四档
                        m_array[101] = ((quint8)dealData.at(startbyte+12) & 0x20) >> 5;  //大车纠偏
                        m_array[102] = ((quint8)dealData.at(startbyte+12) & 0x40) >> 6; //大车校准
                        m_array[103] = ((quint8)dealData.at(startbyte+12) & 0x80) >> 7; //手柄零位

                        m_array[104] = (quint8)dealData.at(startbyte+13) & 0x01;//      //小车前进
                        m_array[105] = ((quint8)dealData.at(startbyte+13) & 0x02) >> 1; //小车后退
                        m_array[106] = ((quint8)dealData.at(startbyte+13) & 0x04) >> 2; //小车二档
                        m_array[107] = ((quint8)dealData.at(startbyte+13) & 0x08) >> 3; //小车三档
                        m_array[108] = ((quint8)dealData.at(startbyte+13) & 0x10) >> 4; //小车四档
                        m_array[109] = ((quint8)dealData.at(startbyte+13) & 0x20) >> 5; //小车1选择
                        m_array[110] = ((quint8)dealData.at(startbyte+13) & 0x40) >> 6;//小车2选择
                        m_array[111] = ((quint8)dealData.at(startbyte+13) & 0x80) >> 7;//故障消音

                        //第8个字
                        m_array[112] = (quint8)dealData.at(startbyte+14) & 0x01;//     //故障复位
                        m_array[113] = ((quint8)dealData.at(startbyte+14) & 0x02) >> 1;//限位旁路
                        m_array[114] = ((quint8)dealData.at(startbyte+14) & 0x04) >> 2;//高/低速
                        m_array[115] = ((quint8)dealData.at(startbyte+14) & 0x08) >> 3;//启动
                        m_array[116] = ((quint8)dealData.at(startbyte+14) & 0x10) >> 4;//停止
                        m_array[117] = ((quint8)dealData.at(startbyte+14) & 0x20) >> 5;//门限位
                        m_array[118] = ((quint8)dealData.at(startbyte+14) & 0x40) >> 6;//大风报警
                        m_array[119] = ((quint8)dealData.at(startbyte+14) & 0x80) >> 7;//备用

                        m_array[120] = (quint8)dealData.at(startbyte+15) & 0x01;//     //备用
                        m_array[121] = ((quint8)dealData.at(startbyte+15) & 0x02) >> 1;//备用
                        m_array[122] = ((quint8)dealData.at(startbyte+15) & 0x04) >> 2;//备用
                        m_array[123] = ((quint8)dealData.at(startbyte+15) & 0x08) >> 3;//备用
                        m_array[124] = ((quint8)dealData.at(startbyte+15) & 0x10) >> 4;//备用
                        m_array[125] = ((quint8)dealData.at(startbyte+15) & 0x20) >> 5;//备用
                        m_array[126] = ((quint8)dealData.at(startbyte+15) & 0x40) >> 6;//备用
                        m_array[127] = ((quint8)dealData.at(startbyte+15) & 0x80) >> 7;    //备用
#endif
                    }
                }else if(dealData.at(9) == 0x01){//读写Q区
//                    if((dealData.at(2) == 0x0c) && dealData.at(3) == counter){
                    if((quint8)dealData.at(2) == 0x0c){   //0x08+读取数据字节数  data slength
#if 1
                        mutex.lock();
                        for(int i = 16;i < 20;i++){
                            m_AreaData[i] = (quint8)dealData.at(startbyte+(i-16));
                        }
                        mutex.unlock();
#endif
#if 0
                        //第1个字
                        m_array[128] = (quint8)dealData.at(16) & 0x01;//主接触器
                        m_array[129] = ((quint8)dealData.at(16) & 0x02) >> 1;//起升1风机
                        m_array[130] = ((quint8)dealData.at(16) & 0x04) >> 2;//起升1制动
                        m_array[131] = ((quint8)dealData.at(16) & 0x08) >> 3;//起升2风机
                        m_array[132] = ((quint8)dealData.at(16) & 0x10) >> 4;//起升2制动
                        m_array[133] = ((quint8)dealData.at(16) & 0x20) >> 5;//起升3风机
                        m_array[134] = ((quint8)dealData.at(16) & 0x40) >> 6;//起升3制动
                        m_array[135] = ((quint8)dealData.at(16) & 0x80) >> 7;//起升4风机

                        m_array[136] = (quint8)dealData.at(17) & 0x01;//起升4制动
                        m_array[137] = ((quint8)dealData.at(17) & 0x02) >> 1;//小车1风机制动
                        m_array[138] = ((quint8)dealData.at(17) & 0x04) >> 2;//小车2风机制动
                        m_array[139] = ((quint8)dealData.at(17) & 0x08) >> 3;//刚腿风机制动
                        m_array[140] = ((quint8)dealData.at(17) & 0x10) >> 4;//柔腿风机制动
                        m_array[141] = ((quint8)dealData.at(17) & 0x20) >> 5;//故障复位
                        m_array[142] = ((quint8)dealData.at(17) & 0x40) >> 6;//备用
                        m_array[143] = ((quint8)dealData.at(17) & 0x80) >> 7;//备用

                        //第2个字
                        m_array[144] = (quint8)dealData.at(18) & 0x01;//电源指示
                        m_array[145] = ((quint8)dealData.at(18) & 0x02) >> 1;//故障指示
                        m_array[146] = ((quint8)dealData.at(18) & 0x04) >> 2;//故障报警
                        m_array[147] = ((quint8)dealData.at(18) & 0x08) >> 3;//起升1正常
                        m_array[148] = ((quint8)dealData.at(18) & 0x10) >> 4;//起升2正常
                        m_array[149] = ((quint8)dealData.at(18) & 0x20) >> 5;//起升3正常
                        m_array[150] = ((quint8)dealData.at(18) & 0x40) >> 6;//起升4正常
                        m_array[151] = ((quint8)dealData.at(18) & 0x80) >> 7;//小车1正常

                        m_array[152] = (quint8)dealData.at(19) & 0x01;//小车2正常
                        m_array[153] = ((quint8)dealData.at(19) & 0x02) >> 1;//小车防撞
                        m_array[154] = ((quint8)dealData.at(19) & 0x04) >> 2;//大车正常
                        m_array[155] = ((quint8)dealData.at(19) & 0x08) >> 3;//越限位
                        m_array[156] = ((quint8)dealData.at(19) & 0x10) >> 4;//大车超偏
                        m_array[157] = ((quint8)dealData.at(19) & 0x20) >> 5;//起升超载
                        m_array[158] = ((quint8)dealData.at(19) & 0x40) >> 6;//备用
                        m_array[159] = ((quint8)dealData.at(19) & 0x80) >> 7;//备用
#endif
                    }
                }
            }break;
            case RWMAREA:
            {
//                if((dealData.at(2) == 0x18) && dealData.at(3) == counter){
                if((quint8)dealData.at(2) == 0x18){//0x08+读取数据字节数  data slength
#if 1
                    mutex.lock();
                    for(int i = 20;i < 36;i++){
                        m_AreaData[i] = (quint8)dealData.at(startbyte+(i-20));
                    }
                    mutex.unlock();
#endif
#if 0
                    m_array[160] = (quint8)dealData.at(16);
                    m_array[161] = (quint8)dealData.at(17);
                    m_array[162] = (quint8)dealData.at(18);
                    m_array[163] = (quint8)dealData.at(19);//上升1高度编码器值

                    m_array[164] = (quint8)dealData.at(20);
                    m_array[165] = (quint8)dealData.at(21);
                    m_array[166] = (quint8)dealData.at(22);
                    m_array[167] = (quint8)dealData.at(23);//上升2高度编码器值

                    m_array[168] = (quint8)dealData.at(24);
                    m_array[169] = (quint8)dealData.at(25);
                    m_array[170] = (quint8)dealData.at(26);
                    m_array[171] = (quint8)dealData.at(27);//下主起升高度编码器值

                    m_array[172] = (quint8)dealData.at(28);
                    m_array[173] = (quint8)dealData.at(29);
                    m_array[174] = (quint8)dealData.at(30);
                    m_array[175] = (quint8)dealData.at(31);//下fu起升高度编码器值
#endif
                }
            }break;
            default:break;
            }
        }
    }else{
        return;
    }
//    }
}

void TcpClientThread::setConnectStatus(bool flag)
{
    _connectStatus = flag;
}

bool TcpClientThread::getConnetcStatus()
{
    return _connectStatus;
}

void TcpClientThread::sendToUpdate()
{
    updatePLCData();

    emit sendTcpSocketData(m_array);
}

void TcpClientThread::reConnectSocket()
{
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        setConnectStatus(true);
//        PLCOnlineStatus = true;
        emit sendConnectStatus(true);
    }else{
        setConnectStatus(false);
        cleanArray();
//        PLCOnlineStatus = false;
        emit sendConnectStatus(false);
        newConnect();
    }
}

void TcpClientThread::cleanArray()
{
    if(!m_array.isNull() && m_array.size() > 0){
        for(int i=0;i<m_array.size();i++){
            m_array[i] = 0x00;
        }
    }
}

void TcpClientThread::updatePLCData()
{
//    FuncTime ft("TcpClientThread::updatePLCData()   ");
//    {
    // I area
    //第1个字
    m_array[0] = (quint8)m_AreaData.at(0) & 0x01;//相序保护
    m_array[1] = ((quint8)m_AreaData.at(0) & 0x02) >> 1;//主接触器反馈
    m_array[2] = ((quint8)m_AreaData.at(0) & 0x04) >> 2;//起升1空开
    m_array[3] = ((quint8)m_AreaData.at(0) & 0x08) >> 3;//起升1制动
    m_array[4] = ((quint8)m_AreaData.at(0) & 0x10) >> 4;//起升1故障
    m_array[5] = ((quint8)m_AreaData.at(0) & 0x20) >> 5;//起升2空开
    m_array[6] = ((quint8)m_AreaData.at(0) & 0x40) >> 6;//起升2制动
    m_array[7] = ((quint8)m_AreaData.at(0) & 0x80) >> 7;//起升2故障

    m_array[8] = (quint8)m_AreaData.at(1) & 0x01;//起升3空开
    m_array[9] = ((quint8)m_AreaData.at(1) & 0x02) >> 1;//起升3制动
    m_array[10] = ((quint8)m_AreaData.at(1) & 0x04) >> 2;//起升3故障
    m_array[11] = ((quint8)m_AreaData.at(1) & 0x08) >> 3;//起升4空开
    m_array[12] = ((quint8)m_AreaData.at(1) & 0x10) >> 4;//起升4制动
    m_array[13] = ((quint8)m_AreaData.at(1) & 0x20) >> 5;//起升4故障
    m_array[14] = ((quint8)m_AreaData.at(1) & 0x40) >> 6;//小车1空开
    m_array[15] = ((quint8)m_AreaData.at(1) & 0x80) >> 7;//小车1热继

    //第2个字
    m_array[16] = (quint8)m_AreaData.at(2) & 0x01;//小车1故障
    m_array[17] = ((quint8)m_AreaData.at(2) & 0x02) >> 1;//小车2空开
    m_array[18] = ((quint8)m_AreaData.at(2) & 0x04) >> 2;//小车2热继
    m_array[19] = ((quint8)m_AreaData.at(2) & 0x08) >> 3;//小车2故障
    m_array[20] = ((quint8)m_AreaData.at(2) & 0x10) >> 4;//刚腿空开
    m_array[21] = ((quint8)m_AreaData.at(2) & 0x20) >> 5;//刚腿热继
    m_array[22] = ((quint8)m_AreaData.at(2) & 0x40) >> 6;//刚腿故障
    m_array[23] = ((quint8)m_AreaData.at(2) & 0x80) >> 7;//柔腿空开

    m_array[24] = (quint8)m_AreaData.at(3) & 0x01;//柔腿热继
    m_array[25] = ((quint8)m_AreaData.at(3) & 0x02) >> 1;//柔腿故障
    m_array[26] = ((quint8)m_AreaData.at(3) & 0x04) >> 2;//卷筒空开
    m_array[27] = ((quint8)m_AreaData.at(3) & 0x08) >> 3;//起升1上停止
    m_array[28] = ((quint8)m_AreaData.at(3) & 0x10) >> 4;//起升1上减速
    m_array[29] = ((quint8)m_AreaData.at(3) & 0x20) >> 5;//起升1下停止
    m_array[30] = ((quint8)m_AreaData.at(3) & 0x40) >> 6;//起升1下减速
    m_array[31] = ((quint8)m_AreaData.at(3) & 0x80) >> 7;//起升1超速

    //第3个字
    m_array[32] = (quint8)m_AreaData.at(4) & 0x01;//起升2上停止
    m_array[33] = ((quint8)m_AreaData.at(4) & 0x02) >> 1;//起升2上减速
    m_array[34] = ((quint8)m_AreaData.at(4) & 0x04) >> 2;//起升2下停止
    m_array[35] = ((quint8)m_AreaData.at(4) & 0x08) >> 3;//起升2下减速
    m_array[36] = ((quint8)m_AreaData.at(4) & 0x10) >> 4;//起升2超速
    m_array[37] = ((quint8)m_AreaData.at(4) & 0x20) >> 5;//小车1前停止
    m_array[38] = ((quint8)m_AreaData.at(4) & 0x40) >> 6;//小车1前减速
    m_array[39] = ((quint8)m_AreaData.at(4) & 0x80) >> 7;//起升3上停止

    m_array[40] = (quint8)m_AreaData.at(5) & 0x01;//起升3上减速
    m_array[41] = ((quint8)m_AreaData.at(5) & 0x02) >> 1;//起升3下停止
    m_array[42] = ((quint8)m_AreaData.at(5) & 0x04) >> 2;//起升3下减速
    m_array[43] = ((quint8)m_AreaData.at(5) & 0x08) >> 3;//起升3超速
    m_array[44] = ((quint8)m_AreaData.at(5) & 0x10) >> 4;//起升4上停止
    m_array[45] = ((quint8)m_AreaData.at(5) & 0x20) >> 5;//起升4上减速
    m_array[46] = ((quint8)m_AreaData.at(5) & 0x40) >> 6;//起升4下停止
    m_array[47] = ((quint8)m_AreaData.at(5) & 0x80) >> 7;//起升4下减速

    //第4个字
    m_array[48] = (quint8)m_AreaData.at(6) & 0x01;//起升4超速
    m_array[49] = ((quint8)m_AreaData.at(6) & 0x02) >> 1;//小车防撞
    m_array[50] = ((quint8)m_AreaData.at(6) & 0x04) >> 2;//小车2后停止
    m_array[51] = ((quint8)m_AreaData.at(6) & 0x08) >> 3;//小车2后减速
    m_array[52] = ((quint8)m_AreaData.at(6) & 0x10) >> 4;//大车左限位
    m_array[53] = ((quint8)m_AreaData.at(6) & 0x20) >> 5;//大车左减速
    m_array[54] = ((quint8)m_AreaData.at(6) & 0x40) >> 6;//大车右限位
    m_array[55] = ((quint8)m_AreaData.at(6) & 0x80) >> 7;//大车右减速

    m_array[56] = (quint8)m_AreaData.at(7) & 0x01;//卷筒过紧
    m_array[57] = ((quint8)m_AreaData.at(7) & 0x02) >> 1;//卷筒过松
    m_array[58] = ((quint8)m_AreaData.at(7) & 0x04) >> 2;//大车左校准
    m_array[59] = ((quint8)m_AreaData.at(7) & 0x08) >> 3;//大车右校准
    m_array[60] = ((quint8)m_AreaData.at(7) & 0x10) >> 4;//备用
    m_array[61] = ((quint8)m_AreaData.at(7) & 0x20) >> 5;//备用
    m_array[62] = ((quint8)m_AreaData.at(7) & 0x40) >> 6;//备用
    m_array[63] = ((quint8)m_AreaData.at(7) & 0x80) >> 7;//备用

    //第5个字
    m_array[64] = (quint8)m_AreaData.at(8) & 0x01;//备用
    m_array[65] = ((quint8)m_AreaData.at(8) & 0x02) >> 1;//备用
    m_array[66] = ((quint8)m_AreaData.at(8) & 0x04) >> 2;//备用
    m_array[67] = ((quint8)m_AreaData.at(8) & 0x08) >> 3;//备用
    m_array[68] = ((quint8)m_AreaData.at(8) & 0x10) >> 4;//备用
    m_array[69] = ((quint8)m_AreaData.at(8) & 0x20) >> 5;//备用
    m_array[70] = ((quint8)m_AreaData.at(8) & 0x40) >> 6;//备用
    m_array[71] = ((quint8)m_AreaData.at(8) & 0x80) >> 7;//备用

    m_array[72] = (quint8)m_AreaData.at(9) & 0x01;//备用
    m_array[73] = ((quint8)m_AreaData.at(9) & 0x02) >> 1;//备用
    m_array[74] = ((quint8)m_AreaData.at(9) & 0x04) >> 2;//备用
    m_array[75] = ((quint8)m_AreaData.at(9) & 0x08) >> 3;//备用
    m_array[76] = ((quint8)m_AreaData.at(9) & 0x10) >> 4;//备用
    m_array[77] = ((quint8)m_AreaData.at(9) & 0x20) >> 5;//备用
    m_array[78] = ((quint8)m_AreaData.at(9) & 0x40) >> 6;//备用
    m_array[79] = ((quint8)m_AreaData.at(9) & 0x80) >> 7;//备用

    //第6个字
    m_array[80] = (quint8)m_AreaData.at(10) & 0x01;// //起升1.2上升
    m_array[81] = ((quint8)m_AreaData.at(10) & 0x02) >> 1;    //起升1.2下降
    m_array[82] = ((quint8)m_AreaData.at(10) & 0x04) >> 2; //起升1.2二档
    m_array[83] = ((quint8)m_AreaData.at(10) & 0x08) >> 3; //起升1.2三档
    m_array[84] = ((quint8)m_AreaData.at(10) & 0x10) >> 4; //起升1.2四档
    m_array[85] = ((quint8)m_AreaData.at(10) & 0x20) >> 5;  //起升1选择
    m_array[86] = ((quint8)m_AreaData.at(10) & 0x40) >> 6;     //起升2选择
    m_array[87] = ((quint8)m_AreaData.at(10) & 0x80) >> 7;     //试灯

    m_array[88] = (quint8)m_AreaData.at(11) & 0x01;//     // 起升3.4上升
    m_array[89] = ((quint8)m_AreaData.at(11) & 0x02) >> 1;//起升3.4下降
    m_array[90] = ((quint8)m_AreaData.at(11) & 0x04) >> 2;//起升3.4二档
    m_array[91] = ((quint8)m_AreaData.at(11) & 0x08) >> 3;//起升3.4三档
    m_array[92] = ((quint8)m_AreaData.at(11) & 0x10) >> 4;//起升3.4四档
    m_array[93] = ((quint8)m_AreaData.at(11) & 0x20) >> 5;//起升3选择
    m_array[94] = ((quint8)m_AreaData.at(11) & 0x40) >> 6;//起升4选择
    m_array[95] = ((quint8)m_AreaData.at(11) & 0x80) >> 7;//起升3.4联吊

    //第7个字
    m_array[96] = (quint8)m_AreaData.at(12) & 0x01;//       //大车左行
    m_array[97] = ((quint8)m_AreaData.at(12) & 0x02) >> 1; //大车右行
    m_array[98] = ((quint8)m_AreaData.at(12) & 0x04) >> 2;  //大车二档
    m_array[99] = ((quint8)m_AreaData.at(12) & 0x08) >> 3; //大车三档
    m_array[100] = ((quint8)m_AreaData.at(12) & 0x10) >> 4;//大车四档
    m_array[101] = ((quint8)m_AreaData.at(12) & 0x20) >> 5;  //大车纠偏
    m_array[102] = ((quint8)m_AreaData.at(12) & 0x40) >> 6; //大车校准
    m_array[103] = ((quint8)m_AreaData.at(12) & 0x80) >> 7; //手柄零位

    m_array[104] = (quint8)m_AreaData.at(13) & 0x01;//      //小车前进
    m_array[105] = ((quint8)m_AreaData.at(13) & 0x02) >> 1; //小车后退
    m_array[106] = ((quint8)m_AreaData.at(13) & 0x04) >> 2; //小车二档
    m_array[107] = ((quint8)m_AreaData.at(13) & 0x08) >> 3; //小车三档
    m_array[108] = ((quint8)m_AreaData.at(13) & 0x10) >> 4; //小车四档
    m_array[109] = ((quint8)m_AreaData.at(13) & 0x20) >> 5; //小车1选择
    m_array[110] = ((quint8)m_AreaData.at(13) & 0x40) >> 6;//小车2选择
    m_array[111] = ((quint8)m_AreaData.at(13) & 0x80) >> 7;//故障消音

    //第8个字
    m_array[112] = (quint8)m_AreaData.at(14) & 0x01;//     //故障复位
    m_array[113] = ((quint8)m_AreaData.at(14) & 0x02) >> 1;//限位旁路
    m_array[114] = ((quint8)m_AreaData.at(14) & 0x04) >> 2;//高/低速
    m_array[115] = ((quint8)m_AreaData.at(14) & 0x08) >> 3;//启动
    m_array[116] = ((quint8)m_AreaData.at(14) & 0x10) >> 4;//停止
    m_array[117] = ((quint8)m_AreaData.at(14) & 0x20) >> 5;//门限位
    m_array[118] = ((quint8)m_AreaData.at(14) & 0x40) >> 6;//大风报警
    m_array[119] = ((quint8)m_AreaData.at(14) & 0x80) >> 7;//备用

    m_array[120] = (quint8)m_AreaData.at(15) & 0x01;//     //备用
    m_array[121] = ((quint8)m_AreaData.at(15) & 0x02) >> 1;//备用
    m_array[122] = ((quint8)m_AreaData.at(15) & 0x04) >> 2;//备用
    m_array[123] = ((quint8)m_AreaData.at(15) & 0x08) >> 3;//备用
    m_array[124] = ((quint8)m_AreaData.at(15) & 0x10) >> 4;//备用
    m_array[125] = ((quint8)m_AreaData.at(15) & 0x20) >> 5;//备用
    m_array[126] = ((quint8)m_AreaData.at(15) & 0x40) >> 6;//备用
    m_array[127] = ((quint8)m_AreaData.at(15) & 0x80) >> 7;    //备用

    //第1个字
    m_array[128] = (quint8)m_AreaData.at(16) & 0x01;//主接触器
    m_array[129] = ((quint8)m_AreaData.at(16) & 0x02) >> 1;//起升1风机
    m_array[130] = ((quint8)m_AreaData.at(16) & 0x04) >> 2;//起升1制动
    m_array[131] = ((quint8)m_AreaData.at(16) & 0x08) >> 3;//起升2风机
    m_array[132] = ((quint8)m_AreaData.at(16) & 0x10) >> 4;//起升2制动
    m_array[133] = ((quint8)m_AreaData.at(16) & 0x20) >> 5;//起升3风机
    m_array[134] = ((quint8)m_AreaData.at(16) & 0x40) >> 6;//起升3制动
    m_array[135] = ((quint8)m_AreaData.at(16) & 0x80) >> 7;//起升4风机

    m_array[136] = (quint8)m_AreaData.at(17) & 0x01;//起升4制动
    m_array[137] = ((quint8)m_AreaData.at(17) & 0x02) >> 1;//小车1风机制动
    m_array[138] = ((quint8)m_AreaData.at(17) & 0x04) >> 2;//小车2风机制动
    m_array[139] = ((quint8)m_AreaData.at(17) & 0x08) >> 3;//刚腿风机制动
    m_array[140] = ((quint8)m_AreaData.at(17) & 0x10) >> 4;//柔腿风机制动
    m_array[141] = ((quint8)m_AreaData.at(17) & 0x20) >> 5;//故障复位
    m_array[142] = ((quint8)m_AreaData.at(17) & 0x40) >> 6;//备用
    m_array[143] = ((quint8)m_AreaData.at(17) & 0x80) >> 7;//备用

    //第2个字
    m_array[144] = (quint8)m_AreaData.at(18) & 0x01;//电源指示
    m_array[145] = ((quint8)m_AreaData.at(18) & 0x02) >> 1;//故障指示
    m_array[146] = ((quint8)m_AreaData.at(18) & 0x04) >> 2;//故障报警
    m_array[147] = ((quint8)m_AreaData.at(18) & 0x08) >> 3;//起升1正常
    m_array[148] = ((quint8)m_AreaData.at(18) & 0x10) >> 4;//起升2正常
    m_array[149] = ((quint8)m_AreaData.at(18) & 0x20) >> 5;//起升3正常
    m_array[150] = ((quint8)m_AreaData.at(18) & 0x40) >> 6;//起升4正常
    m_array[151] = ((quint8)m_AreaData.at(18) & 0x80) >> 7;//小车1正常

    m_array[152] = (quint8)m_AreaData.at(19) & 0x01;//小车2正常
    m_array[153] = ((quint8)m_AreaData.at(19) & 0x02) >> 1;//小车防撞
    m_array[154] = ((quint8)m_AreaData.at(19) & 0x04) >> 2;//大车正常
    m_array[155] = ((quint8)m_AreaData.at(19) & 0x08) >> 3;//越限位
    m_array[156] = ((quint8)m_AreaData.at(19) & 0x10) >> 4;//大车超偏
    m_array[157] = ((quint8)m_AreaData.at(19) & 0x20) >> 5;//起升超载
    m_array[158] = ((quint8)m_AreaData.at(19) & 0x40) >> 6;//备用
    m_array[159] = ((quint8)m_AreaData.at(19) & 0x80) >> 7;//备用


    m_array[160] = (quint8)m_AreaData.at(20);
    m_array[161] = (quint8)m_AreaData.at(21);
    m_array[162] = (quint8)m_AreaData.at(22);
    m_array[163] = (quint8)m_AreaData.at(23);//上升1高度编码器值

    m_array[164] = (quint8)m_AreaData.at(24);
    m_array[165] = (quint8)m_AreaData.at(25);
    m_array[166] = (quint8)m_AreaData.at(26);
    m_array[167] = (quint8)m_AreaData.at(27);//上升2高度编码器值

    m_array[168] = (quint8)m_AreaData.at(28);
    m_array[169] = (quint8)m_AreaData.at(29);
    m_array[170] = (quint8)m_AreaData.at(30);
    m_array[171] = (quint8)m_AreaData.at(31);//下主起升高度编码器值

    m_array[172] = (quint8)m_AreaData.at(32);
    m_array[173] = (quint8)m_AreaData.at(33);
    m_array[174] = (quint8)m_AreaData.at(34);
    m_array[175] = (quint8)m_AreaData.at(35);//下fu起升高度编码器值
//    }

}
