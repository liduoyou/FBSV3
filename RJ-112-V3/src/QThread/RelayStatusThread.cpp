#include "RelayStatusThread.h"
#include <QDebug>
#include <QMutex>
#include "../SerialPort/posix_qextserialport.h"    //串口类
//#include "../UI/MainWidget.h"
//#include "../UI/LittleVehicleWidget.h"
//#include "../UI/HookWidget.h"
//#include "../UI/BigVehicleWidget.h"
#define DEV "/dev/ttySAC3"

RelayStatusThread::RelayStatusThread(QObject *parent) :
    QThread(parent)
  , m_sendDataTimer(NULL)
  , isSendData(false)
{
    //init serial port
    m_pSerial = new Posix_QextSerialPort(DEV,QextSerialBase::Polling);//串口设备号

    if(m_pSerial != NULL){
        m_pSerial->setBaudRate(BAUD9600);
        m_pSerial->setDataBits(DATA_8);
        m_pSerial->setStopBits(STOP_1);
        m_pSerial->setParity(PAR_NONE);

        m_pSerial->setFlowControl(FLOW_OFF);
        m_pSerial->setTimeout(10);

        if(m_pSerial->open(QIODevice::ReadWrite)){
            qDebug(DEV);
        }
    }

    m_array.resize(512);
    for(int i=0;i<m_array.size();i++){
        m_array[i] = 0x00;
    }

    m_sendDataTimer = new QTimer();
    connect(m_sendDataTimer,SIGNAL(timeout()),this,SLOT(sendToUpdate()));
    m_sendDataTimer->start(500);
}

RelayStatusThread::~RelayStatusThread()
{
}

void RelayStatusThread::run()
{
    int flag = 0 ;
    QByteArray datagram;
    QMutex mutex;
    int size = -1;
    while(1){
        datagram.append(m_pSerial->readAll());
        msleep(1);
        size = datagram.size();
        if(size == 0){
            continue;
        }

//        if(size == 4)
//        {
            if(((datagram.at(0) == 0x00) && (datagram.at(1) == 0x10) && (datagram.at(3) == 0x00)) ||
                    ((datagram.at(0) == 0x01) && (datagram.at(3) == 0x20))||
                    ((datagram.at(0) == 0x02) && (datagram.at(3) == 0x40)))
            {
                if((datagram.at(0) == 0x00) && (datagram.at(1) == 0x10) && (datagram.at(3) == 0x00))
                {
                    flag = 1 ;
                }else if((datagram.at(0) == 0x01) && (datagram.at(3) == 0x20))
                {
                    flag = 2 ;
                }else if((datagram.at(0) == 0x02) && (datagram.at(3) == 0x40))
                {
                    flag = 3 ;
                }
            }else{
                datagram.clear();
            }
//        }

        if(flag == 1){
            if(size == 41){
                quint16 check = GetCheckCode(datagram,(size-2));
                if(((check & 0xff) == (quint8)datagram.at(size-2))
                        &&(check >> 8 == (quint8)datagram.at(size-1)))
                {
                    mutex.lock();
                    //写数据
                    writeDataToSerial(flag,datagram);
                    //处理数据
                    dealData(datagram,size);
                    mutex.unlock();
                }
                datagram.clear();
                size = 0;
                flag = 0 ;
            }
        }else if(flag == 2){
            if(size == 41){
                quint16 check = GetCheckCode(datagram,(size-2));
                if(((check & 0xff) == (quint8)datagram.at(size-2))
                        &&(check >> 8 == (quint8)datagram.at(size-1)))
                {
                    mutex.lock();
                    //写数据
                    writeDataToSerial(flag,datagram);
                    //处理数据
                    dealData(datagram,size);
                    mutex.unlock();
                }
                datagram.clear();
                size = 0;
                flag = 0 ;
            }
        }else if(flag == 3){
            if(size == 41){
                quint16 check = GetCheckCode(datagram,(size-2));
                if(((check & 0xff) == (quint8)datagram.at(size-2))
                        &&(check >> 8 == (quint8)datagram.at(size-1)))
                {
                    mutex.lock();
                    //写数据
                    writeDataToSerial(flag,datagram);
                    //处理数据
                    dealData(datagram,size);
                    mutex.unlock();
                }
                datagram.clear();
                size = 0;
                flag = 0 ;
            }
        }
//            qDebug()<<"DATA SIZE="<<size;

//            qDebug()<<"check & 0xff"<<quint8(check & 0xff);
//            qDebug()<<"check >> 8"<<quint8(check >> 8);
//            qDebug()<<"(quint8)datagram.at(size-2)"<<(quint8)datagram.at(size-2);
//            qDebug()<<"(quint8)datagram.at(size-1)"<<(quint8)datagram.at(size-1);

//                qDebug()<<"CHECK";

    }
    m_pSerial->close();
}

void RelayStatusThread::writeDataToSerial(int flag,QByteArray datagram)
{
    QByteArray sendcmd;
    if(flag!=5){
        sendcmd.resize(8);
        sendcmd[0] = (quint8)datagram.at(0);
        sendcmd[1] = (quint8)datagram.at(1);
        sendcmd[2] = (quint8)datagram.at(2);
        quint16 CrcData;
        sendcmd[3] = (quint8)datagram.at(3);
        sendcmd[4] = (quint8)datagram.at(4);
        sendcmd[5] = (quint8)datagram.at(5);
        CrcData = GetCheckCode(sendcmd,6);
        sendcmd[6] =CrcData & 0xff;
        sendcmd[7] =CrcData >> 8;
        m_pSerial->write(sendcmd);
    }
}

void RelayStatusThread::dealData(QByteArray data, int datasize)
{
    Q_UNUSED(datasize)
    quint8 startbyte=7;  //该变量用来判断接收数据从第几个字节开始判断、分析；

    switch ((quint8)data.at(0)) {
    case 0x00:
    {
        qDebug()<<"go into case 0x00";
//        PLCOnlineStatus = true;

        //第1个字
        m_array[0] = (quint8)data.at(startbyte) & 0x01;//司机室电气室急停
        m_array[1] = ((quint8)data.at(startbyte) & 0x02) >> 1;//上小车急停
        m_array[2] = ((quint8)data.at(startbyte) & 0x04) >> 2;//下小车急停
        m_array[3] = ((quint8)data.at(startbyte) & 0x08) >> 3;//钢腿急停
        m_array[4] = ((quint8)data.at(startbyte) & 0x10) >> 4;//柔腿急停
        m_array[5] = ((quint8)data.at(startbyte) & 0x20) >> 5;//主起手柄零位
        m_array[6] = ((quint8)data.at(startbyte) & 0x40) >> 6;//副起手柄零位
        m_array[7] = ((quint8)data.at(startbyte) & 0x80) >> 7;//小车手柄零位

        m_array[8] = (quint8)data.at(startbyte+1) & 0x01;//大车手柄零位
        m_array[9] = ((quint8)data.at(startbyte+1) & 0x02) >> 1;//PLC屏启动
        m_array[10] = ((quint8)data.at(startbyte+1) & 0x04) >> 2;//故障复位
        m_array[11] = ((quint8)data.at(startbyte+1) & 0x08) >> 3;//故障停止
        m_array[12] = ((quint8)data.at(startbyte+1) & 0x10) >> 4;//灯测试
        m_array[13] = ((quint8)data.at(startbyte+1) & 0x20) >> 5;//总接触器
        m_array[14] = ((quint8)data.at(startbyte+1) & 0x40) >> 6;//PLC模块电源
        m_array[15] = ((quint8)data.at(startbyte+1) & 0x80) >> 7;//机构控制电源

        //第2个字
        m_array[16] = (quint8)data.at(startbyte+2) & 0x01;//上1#起升断路器
        m_array[17] = ((quint8)data.at(startbyte+2) & 0x02) >> 1;//上1#起升接触器
        m_array[18] = ((quint8)data.at(startbyte+2) & 0x04) >> 2;//上1#起升风机接触器
        m_array[19] = ((quint8)data.at(startbyte+2) & 0x08) >> 3;//上1#起升制动接触器
        m_array[20] = ((quint8)data.at(startbyte+2) & 0x10) >> 4;//上1#起升超速检测
        m_array[21] = ((quint8)data.at(startbyte+2) & 0x20) >> 5;//上1#起升上升超限位
        m_array[22] = ((quint8)data.at(startbyte+2) & 0x40) >> 6;//上1#起升下降超限位
        m_array[23] = ((quint8)data.at(startbyte+2) & 0x80) >> 7;//上1#起升制动器控制

        m_array[24] = (quint8)data.at(startbyte+3) & 0x01;//上1#起升变频器故障
        m_array[25] = ((quint8)data.at(startbyte+3) & 0x02) >> 1;//上1#起升上升减速
        m_array[26] = ((quint8)data.at(startbyte+3) & 0x04) >> 2;//上1#起升上升停止
        m_array[27] = ((quint8)data.at(startbyte+3) & 0x08) >> 3;//上1#起升下降减速
        m_array[28] = ((quint8)data.at(startbyte+3) & 0x10) >> 4;//上1#起升下降停止
        m_array[29] = ((quint8)data.at(startbyte+3) & 0x20) >> 5;//上1#起升上升点动
        m_array[30] = ((quint8)data.at(startbyte+3) & 0x40) >> 6;//上1#起升下降点动
        m_array[31] = ((quint8)data.at(startbyte+3) & 0x80) >> 7;//上1#起升制动电阻过热

        //第3个字
        m_array[32] = (quint8)data.at(startbyte+4) & 0x01;//上2#起升断路器
        m_array[33] = ((quint8)data.at(startbyte+4) & 0x02) >> 1;//上2#起升接触器
        m_array[34] = ((quint8)data.at(startbyte+4) & 0x04) >> 2;//上2#起升风机接触器
        m_array[35] = ((quint8)data.at(startbyte+4) & 0x08) >> 3;//上2#起升制动接触器
        m_array[36] = ((quint8)data.at(startbyte+4) & 0x10) >> 4;//上2#起升超速检测
        m_array[37] = ((quint8)data.at(startbyte+4) & 0x20) >> 5;//上2#起升上升超限位
        m_array[38] = ((quint8)data.at(startbyte+4) & 0x40) >> 6;//上2#起升下降超限位
        m_array[39] = ((quint8)data.at(startbyte+4) & 0x80) >> 7;//上2#起升制动器控制

        m_array[40] = (quint8)data.at(startbyte+5) & 0x01;//上2#起升变频器故障
        m_array[41] = ((quint8)data.at(startbyte+5) & 0x02) >> 1;//上2#起升上升减速
        m_array[42] = ((quint8)data.at(startbyte+5) & 0x04) >> 2;//上2#起升上升停止
        m_array[43] = ((quint8)data.at(startbyte+5) & 0x08) >> 3;//上2#起升下降减速
        m_array[44] = ((quint8)data.at(startbyte+5) & 0x10) >> 4;//上2#起升下降停止
        m_array[45] = ((quint8)data.at(startbyte+5) & 0x20) >> 5;//上2#起升上升点动
        m_array[46] = ((quint8)data.at(startbyte+5) & 0x40) >> 6;//上2#起升下降点动
        m_array[47] = ((quint8)data.at(startbyte+5) & 0x80) >> 7;//上2#起升制动电阻过热

        //第4个字
        m_array[48] = (quint8)data.at(startbyte+6) & 0x01;//下主起升断路器
        m_array[49] = ((quint8)data.at(startbyte+6) & 0x02) >> 1;//下主起升主接触器
        m_array[50] = ((quint8)data.at(startbyte+6) & 0x04) >> 2;//下主起升风机接触器
        m_array[51] = ((quint8)data.at(startbyte+6) & 0x08) >> 3;//下主起升制动接触器
        m_array[52] = ((quint8)data.at(startbyte+6) & 0x10) >> 4;//下主起升超速检测
        m_array[53] = ((quint8)data.at(startbyte+6) & 0x20) >> 5;//下主起升上升超限位
        m_array[54] = ((quint8)data.at(startbyte+6) & 0x40) >> 6;//下主起升下降超限位
        m_array[55] = ((quint8)data.at(startbyte+6) & 0x80) >> 7;//下主起升制动器控制

        m_array[56] = (quint8)data.at(startbyte+7) & 0x01;//下主起升变频器故障
        m_array[57] = ((quint8)data.at(startbyte+7) & 0x02) >> 1;//下主起升上升减速
        m_array[58] = ((quint8)data.at(startbyte+7) & 0x04) >> 2;//下主起升上升停止
        m_array[59] = ((quint8)data.at(startbyte+7) & 0x08) >> 3;//下主起升下降减速
        m_array[60] = ((quint8)data.at(startbyte+7) & 0x10) >> 4;//下主起升下降停止
        m_array[61] = ((quint8)data.at(startbyte+7) & 0x20) >> 5;//下主起升上升点动
        m_array[62] = ((quint8)data.at(startbyte+7) & 0x40) >> 6;//下主起升下降点动
        m_array[63] = ((quint8)data.at(startbyte+7) & 0x80) >> 7;//下主起升制动电阻过热

        //第5个字
        m_array[64] = (quint8)data.at(startbyte+8) & 0x01;//下主起升断路器
        m_array[65] = ((quint8)data.at(startbyte+8) & 0x02) >> 1;//备用
        m_array[66] = ((quint8)data.at(startbyte+8) & 0x04) >> 2;//下主起升2#变频器故障
        m_array[67] = ((quint8)data.at(startbyte+8) & 0x08) >> 3;//下主起升制动电阻过热
        m_array[68] = ((quint8)data.at(startbyte+8) & 0x10) >> 4;//备用
        m_array[69] = ((quint8)data.at(startbyte+8) & 0x20) >> 5;//备用
        m_array[70] = ((quint8)data.at(startbyte+8) & 0x40) >> 6;//备用
        m_array[71] = ((quint8)data.at(startbyte+8) & 0x80) >> 7;//备用

        m_array[72] = (quint8)data.at(startbyte+9) & 0x01;//故障确认
        m_array[73] = ((quint8)data.at(startbyte+9) & 0x02) >> 1;//故障复位
        m_array[74] = ((quint8)data.at(startbyte+9) & 0x04) >> 2;//小车纠偏投入按钮
        m_array[75] = ((quint8)data.at(startbyte+9) & 0x08) >> 3;//起升纠偏投入按钮
        m_array[76] = ((quint8)data.at(startbyte+9) & 0x10) >> 4;//大车纠偏投入按钮
        m_array[77] = ((quint8)data.at(startbyte+9) & 0x20) >> 5;//大车铁楔按钮
        m_array[78] = ((quint8)data.at(startbyte+9) & 0x40) >> 6;//备用
        m_array[79] = ((quint8)data.at(startbyte+9) & 0x80) >> 7;//备用

        //第6个字
        m_array[80] = (quint8)data.at(startbyte+10) & 0x01;//         //下副起升总断路器
        m_array[81] = ((quint8)data.at(startbyte+10) & 0x02) >> 1;    //下副起升总接触器
        m_array[82] = ((quint8)data.at(startbyte+10) & 0x04) >> 2; //下副起升风机接触器
        m_array[83] = ((quint8)data.at(startbyte+10) & 0x08) >> 3; //下副起升制动接触器
        m_array[84] = ((quint8)data.at(startbyte+10) & 0x10) >> 4; //下副起升超速检测
        m_array[85] = ((quint8)data.at(startbyte+10) & 0x20) >> 5;  //下副起升上升超限位
        m_array[86] = ((quint8)data.at(startbyte+10) & 0x40) >> 6;     //下副起升下降超限位
        m_array[87] = ((quint8)data.at(startbyte+10) & 0x80) >> 7;     //下副起升制动器控制

        m_array[88] = (quint8)data.at(startbyte+11) & 0x01;//     //下副起升变频器故障
        m_array[89] = ((quint8)data.at(startbyte+11) & 0x02) >> 1;//下副起升上升减速
        m_array[90] = ((quint8)data.at(startbyte+11) & 0x04) >> 2;//下副起升上升停止
        m_array[91] = ((quint8)data.at(startbyte+11) & 0x08) >> 3;//下副起升下降减速
        m_array[92] = ((quint8)data.at(startbyte+11) & 0x10) >> 4;//下副起升下降停止
        m_array[93] = ((quint8)data.at(startbyte+11) & 0x20) >> 5;//下副起升上升点动
        m_array[94] = ((quint8)data.at(startbyte+11) & 0x40) >> 6;//下副起升下降点动
        m_array[95] = ((quint8)data.at(startbyte+11) & 0x80) >> 7;//下副起升制动电阻过热

        //第7个字
        m_array[96] = (quint8)data.at(startbyte+12) & 0x01;//       //上运行总断路器
        m_array[97] = ((quint8)data.at(startbyte+12) & 0x02) >> 1; //上运行电机前断路器
        m_array[98] = ((quint8)data.at(startbyte+12) & 0x04) >> 2;  //上运行总接触器
        m_array[99] = ((quint8)data.at(startbyte+12) & 0x08) >> 3; //上运行风机接触器
        m_array[100] = ((quint8)data.at(startbyte+12) & 0x10) >> 4;//上运行制动接触器
        m_array[101] = ((quint8)data.at(startbyte+12) & 0x20) >> 5;  //上运行锚定开关
        m_array[102] = ((quint8)data.at(startbyte+12) & 0x40) >> 6; //上运行前行超限位
        m_array[103] = ((quint8)data.at(startbyte+12) & 0x80) >> 7; //上运行后行超限位

        m_array[104] = (quint8)data.at(startbyte+13) & 0x01;//      //上运行制动器控制
        m_array[105] = ((quint8)data.at(startbyte+13) & 0x02) >> 1; //上运行变频器故障
        m_array[106] = ((quint8)data.at(startbyte+13) & 0x04) >> 2; //上运行前停止限位
        m_array[107] = ((quint8)data.at(startbyte+13) & 0x08) >> 3; //上运行前减速限位
        m_array[108] = ((quint8)data.at(startbyte+13) & 0x10) >> 4; //上运行后减速限位
        m_array[109] = ((quint8)data.at(startbyte+13) & 0x20) >> 5; //上运行后停止限位
        m_array[110] = ((quint8)data.at(startbyte+13) & 0x40) >> 6;//上运行校正限位开关
        m_array[111] = ((quint8)data.at(startbyte+13) & 0x80) >> 7;//上运行制动电阻过热

        //第8个字
        m_array[112] = (quint8)data.at(startbyte+14) & 0x01;//     //下运行总断路器
        m_array[113] = ((quint8)data.at(startbyte+14) & 0x02) >> 1;//下运行总接触器
        m_array[114] = ((quint8)data.at(startbyte+14) & 0x04) >> 2;//下运行风机接触器
        m_array[115] = ((quint8)data.at(startbyte+14) & 0x08) >> 3;//下运行制动接触器
        m_array[116] = ((quint8)data.at(startbyte+14) & 0x10) >> 4;//下运行锚定开关
        m_array[117] = ((quint8)data.at(startbyte+14) & 0x20) >> 5;//下运行前行超限位
        m_array[118] = ((quint8)data.at(startbyte+14) & 0x40) >> 6;//下运行后行超限位
        m_array[119] = ((quint8)data.at(startbyte+14) & 0x80) >> 7;//备用

        m_array[120] = (quint8)data.at(startbyte+15) & 0x01;//     //下运行制动器控制
        m_array[121] = ((quint8)data.at(startbyte+15) & 0x02) >> 1;//下运行变频器故障
        m_array[122] = ((quint8)data.at(startbyte+15) & 0x04) >> 2;//下运行前停止限位
        m_array[123] = ((quint8)data.at(startbyte+15) & 0x08) >> 3;//下运行前减速限位
        m_array[124] = ((quint8)data.at(startbyte+15) & 0x10) >> 4;//下运行后减速限位
        m_array[125] = ((quint8)data.at(startbyte+15) & 0x20) >> 5;//下运行后停止限位
        m_array[126] = ((quint8)data.at(startbyte+15) & 0x40) >> 6;//下运行校正限位开关
        m_array[127] = ((quint8)data.at(startbyte+15) & 0x80) >> 7;    //下运行制动电阻过热

        //第9个字
        m_array[128] = (quint8)data.at(startbyte+16) & 0x01;//     //大车钢腿总断路器
        m_array[129] = ((quint8)data.at(startbyte+16) & 0x02) >> 1;//大车钢腿电机前断路器
        m_array[130] = ((quint8)data.at(startbyte+16) & 0x04) >> 2;//大车钢腿制动断路器
        m_array[131] = ((quint8)data.at(startbyte+16) & 0x08) >> 3;//大车钢腿风机断路器
        m_array[132] = ((quint8)data.at(startbyte+16) & 0x10) >> 4;//大车钢腿铁楔断路器
        m_array[133] = ((quint8)data.at(startbyte+16) & 0x20) >> 5;//大车钢腿主接触器
        m_array[134] = ((quint8)data.at(startbyte+16) & 0x40) >> 6;//大车钢腿风机接触器
        m_array[135] = ((quint8)data.at(startbyte+16) & 0x80) >> 7;//大车钢腿制动接触器

        m_array[136] = (quint8)data.at(startbyte+17) & 0x01;//      //大车钢腿锚定开关
        m_array[137] = ((quint8)data.at(startbyte+17) & 0x02) >> 1;//大车钢腿铁楔限位
        m_array[138] = ((quint8)data.at(startbyte+17) & 0x04) >> 2; //大车钢腿左超限位
        m_array[139] = ((quint8)data.at(startbyte+17) & 0x08) >> 3; //大车钢腿右超限位
        m_array[140] = ((quint8)data.at(startbyte+17) & 0x10) >> 4; //大车钢腿制动器控制
        m_array[141] = ((quint8)data.at(startbyte+17) & 0x20) >> 5;  //大车钢腿变频器故障
        m_array[142] = ((quint8)data.at(startbyte+17) & 0x40) >> 6; //备用
        m_array[143] = ((quint8)data.at(startbyte+17) & 0x80) >> 7; //大车钢腿制动电阻过热

        //第10个字
        m_array[144] = (quint8)data.at(startbyte+18) & 0x01;//     //大车柔腿总断路器
        m_array[145] = ((quint8)data.at(startbyte+18) & 0x02) >> 1;//大车柔腿电机前断路器
        m_array[146] = ((quint8)data.at(startbyte+18) & 0x04) >> 2;//大车柔腿风机断路器
        m_array[147] = ((quint8)data.at(startbyte+18) & 0x08) >> 3; //大车柔腿制动断路器
        m_array[148] = ((quint8)data.at(startbyte+18) & 0x10) >> 4; //大车柔腿铁楔断路器
        m_array[149] = ((quint8)data.at(startbyte+18) & 0x20) >> 5; //大车柔腿总接触器
        m_array[150] = ((quint8)data.at(startbyte+18) & 0x40) >> 6;  //大车柔腿风机接触器
        m_array[151] = ((quint8)data.at(startbyte+18) & 0x80) >> 7;  //大车柔腿制动器接触器

        m_array[152] = (quint8)data.at(startbyte+19) & 0x01;//     //大车柔腿锚定开关
        m_array[153] = ((quint8)data.at(startbyte+19) & 0x02) >> 1;//大车柔腿铁楔限位开关
        m_array[154] = ((quint8)data.at(startbyte+19) & 0x04) >> 2;//大车柔腿制动器控制
        m_array[155] = ((quint8)data.at(startbyte+19) & 0x08) >> 3;//大车柔腿变频器故障
        m_array[156] = ((quint8)data.at(startbyte+19) & 0x10) >> 4;//备用
        m_array[157] = ((quint8)data.at(startbyte+19) & 0x20) >> 5;//大车柔腿向左偏开关
        m_array[158] = ((quint8)data.at(startbyte+19) & 0x40) >> 6;//大车柔腿向右偏开关
        m_array[159] = ((quint8)data.at(startbyte+19) & 0x80) >> 7;//大车柔腿制动电阻过热

        //第11个字
        m_array[160] = (quint8)data.at(startbyte+20) & 0x01;//上1#起升工作方式
        m_array[161] = ((quint8)data.at(startbyte+20) & 0x02) >> 1;//上2#起升工作方式
        m_array[162] = ((quint8)data.at(startbyte+20) & 0x04) >> 2;//上双起升工作方式
        m_array[163] = ((quint8)data.at(startbyte+20) & 0x08) >> 3;//上下起升工作方式
        m_array[164] = ((quint8)data.at(startbyte+20) & 0x10) >> 4;//下主起工作方式
        m_array[165] = ((quint8)data.at(startbyte+20) & 0x20) >> 5;//上运行工作方式
        m_array[166] = ((quint8)data.at(startbyte+20) & 0x40) >> 6;//下运行工作方式
        m_array[167] = ((quint8)data.at(startbyte+20) & 0x80) >> 7;//上下小车联动工作方式

        m_array[168] = (quint8)data.at(startbyte+21) & 0x01;//上下起升差动
        m_array[169] = ((quint8)data.at(startbyte+21) & 0x02) >> 1;//备用
        m_array[170] = ((quint8)data.at(startbyte+21) & 0x04) >> 2;//柔腿单动
        m_array[171] = ((quint8)data.at(startbyte+21) & 0x08) >> 3;//大车联动
        m_array[172] = ((quint8)data.at(startbyte+21) & 0x10) >> 4;//备用
        m_array[173] = ((quint8)data.at(startbyte+21) & 0x20) >> 5;//备用
        m_array[174] = ((quint8)data.at(startbyte+21) & 0x40) >> 6;//备用
        m_array[175] = ((quint8)data.at(startbyte+21) & 0x80) >> 7;//备用

        //第12个字
        m_array[176] = (quint8)data.at(startbyte+22) & 0x01;//小车向前
        m_array[177] = ((quint8)data.at(startbyte+22) & 0x02) >> 1;//小车向后
        m_array[178] = ((quint8)data.at(startbyte+22) & 0x04) >> 2;//小车二档
        m_array[179] = ((quint8)data.at(startbyte+22) & 0x08) >> 3;//小车三档
        m_array[180] = ((quint8)data.at(startbyte+22) & 0x10) >> 4;//小车四档
        m_array[181] = ((quint8)data.at(startbyte+22) & 0x20) >> 5;//大车向左
        m_array[182] = ((quint8)data.at(startbyte+22) & 0x40) >> 6;//大车向右
        m_array[183] = ((quint8)data.at(startbyte+22) & 0x80) >> 7;//大车二档

        m_array[184] = (quint8)data.at(startbyte+23) & 0x01;//大车三档
        m_array[185] = ((quint8)data.at(startbyte+23) & 0x02) >> 1;//大车四档
        m_array[186] = ((quint8)data.at(startbyte+23) & 0x04) >> 2;//刚腿校准限位开关
        m_array[187] = ((quint8)data.at(startbyte+23) & 0x08) >> 3;//防风系缆1#锚定
        m_array[188] = ((quint8)data.at(startbyte+23) & 0x10) >> 4;//防风系缆2#锚定
        m_array[189] = ((quint8)data.at(startbyte+23) & 0x20) >> 5;//防风系缆3#锚定
        m_array[190] = ((quint8)data.at(startbyte+23) & 0x40) >> 6;//防风系缆4#锚定
        m_array[191] = ((quint8)data.at(startbyte+23) & 0x80) >> 7;//备用

        //第13个字
        m_array[192] = (quint8)data.at(startbyte+24) & 0x01;//     //主起升上升
        m_array[193] = ((quint8)data.at(startbyte+24) & 0x02) >> 1;//主起升下降
        m_array[194] = ((quint8)data.at(startbyte+24) & 0x04) >> 2;//主起升二档
        m_array[195] = ((quint8)data.at(startbyte+24) & 0x08) >> 3;//主起升三档
        m_array[196] = ((quint8)data.at(startbyte+24) & 0x10) >> 4;  //主起升四档
        m_array[197] = ((quint8)data.at(startbyte+24) & 0x20) >> 5;//副起升上升
        m_array[198] = ((quint8)data.at(startbyte+24) & 0x40) >> 6;//副起升下降
        m_array[199] = ((quint8)data.at(startbyte+24) & 0x80) >> 7;//副起升二档

        m_array[200] = (quint8)data.at(startbyte+25) & 0x01;////副起升三档
        m_array[201] = ((quint8)data.at(startbyte+25) & 0x02) >> 1;//副起升四档
        m_array[202] = ((quint8)data.at(startbyte+25) & 0x04) >> 2;//备用
        m_array[203] = ((quint8)data.at(startbyte+25) & 0x08) >> 3;//备用
        m_array[204] = ((quint8)data.at(startbyte+25) & 0x10) >> 4;//备用
        m_array[205] = ((quint8)data.at(startbyte+25) & 0x20) >> 5;//起升点动
        m_array[206] = ((quint8)data.at(startbyte+25) & 0x40) >> 6;//下降点动
        m_array[207] = ((quint8)data.at(startbyte+25) & 0x80) >> 7;//起升高速选择

        //第14个字
        m_array[208] = (quint8)data.at(startbyte+26) & 0x01;//     //司机室操作
        m_array[209] = ((quint8)data.at(startbyte+26) & 0x02) >> 1;//机旁操作
        m_array[210] = ((quint8)data.at(startbyte+26) & 0x04) >> 2;  //大车同步超差运行
        m_array[211] = ((quint8)data.at(startbyte+26) & 0x08) >> 3;  //柔性腿制动器强制打开
        m_array[212] = ((quint8)data.at(startbyte+26) & 0x10) >> 4;  //超风速强制运行
        m_array[213] = ((quint8)data.at(startbyte+26) & 0x20) >> 5; //风速超8米
        m_array[214] = ((quint8)data.at(startbyte+26) & 0x40) >> 6; //风速超20米
        m_array[215] = ((quint8)data.at(startbyte+26) & 0x80) >> 7;//备用

        m_array[216] = (quint8)data.at(startbyte+27) & 0x01;//     //上1#起升35%载荷
        m_array[217] = ((quint8)data.at(startbyte+27) & 0x02) >> 1;//上1#起升超载
        m_array[218] = ((quint8)data.at(startbyte+27) & 0x04) >> 2;//上2#起升35%超载
        m_array[219] = ((quint8)data.at(startbyte+27) & 0x08) >> 3;//上2#起升超载
        m_array[220] = ((quint8)data.at(startbyte+27) & 0x10) >> 4;//1#2#起升偏载50T
        m_array[221] = ((quint8)data.at(startbyte+27) & 0x20) >> 5;//下小车主起升35%载荷
        m_array[222] = ((quint8)data.at(startbyte+27) & 0x40) >> 6;//下小车主起升超载
        m_array[223] = ((quint8)data.at(startbyte+27) & 0x80) >> 7;//下小车副起升超载

        //第15个字
        m_array[224] = (quint8)data.at(startbyte+28) & 0x01;//     //大车左停止限位
        m_array[225] = ((quint8)data.at(startbyte+28) & 0x02) >> 1;//大车左减速限位
        m_array[226] = ((quint8)data.at(startbyte+28) & 0x04) >> 2;//大车右减速限位
        m_array[227] = ((quint8)data.at(startbyte+28) & 0x08) >> 3;//大车右停止限位
        m_array[228] = ((quint8)data.at(startbyte+28) & 0x10) >> 4; //刚性腿1#锚定限位
        m_array[229] = ((quint8)data.at(startbyte+28) & 0x20) >> 5;//刚性腿2#锚定限位
        m_array[230] = ((quint8)data.at(startbyte+28) & 0x40) >> 6;//电缆过松
        m_array[231] = ((quint8)data.at(startbyte+28) & 0x80) >> 7; //电缆过紧

        m_array[232] = (quint8)data.at(startbyte+29) & 0x01;//     //刚性腿1#铁楔限位
        m_array[233] = ((quint8)data.at(startbyte+29) & 0x02) >> 1;//刚性腿2#铁楔限位
        m_array[234] = ((quint8)data.at(startbyte+29) & 0x04) >> 2;//刚性腿3#铁楔限位
        m_array[235] = ((quint8)data.at(startbyte+29) & 0x08) >> 3;//刚性腿4#铁楔限位
        m_array[236] = ((quint8)data.at(startbyte+29) & 0x10) >> 4;//刚性腿5#铁楔限位
        m_array[237] = ((quint8)data.at(startbyte+29) & 0x20) >> 5;//刚性腿6#铁楔限位
        m_array[238] = ((quint8)data.at(startbyte+29) & 0x40) >> 6;  //刚性腿7#铁楔限位
        m_array[239] = ((quint8)data.at(startbyte+29) & 0x80) >> 7;  //刚性腿8#铁楔限位

        //第16个字
        m_array[240] = (quint8)data.at(startbyte+30) & 0x01;//柔性腿校准开关
        m_array[241] = ((quint8)data.at(startbyte+30) & 0x02) >> 1;//备用
        m_array[242] = ((quint8)data.at(startbyte+30) & 0x04) >> 2;//防风系缆1#锚定限位
        m_array[243] = ((quint8)data.at(startbyte+30) & 0x08) >> 3;//防风系缆2#锚定限位
        m_array[244] = ((quint8)data.at(startbyte+30) & 0x10) >> 4;//防风系缆3#锚定限位
        m_array[245] = ((quint8)data.at(startbyte+30) & 0x20) >> 5;//防风系缆4#锚定限位
        m_array[246] = ((quint8)data.at(startbyte+30) & 0x40) >> 6;//柔性腿1#锚定限位
        m_array[247] = ((quint8)data.at(startbyte+30) & 0x80) >> 7;//柔性腿2#锚定限位

        m_array[248] = (quint8)data.at(startbyte+31) & 0x01;//柔性腿1#铁楔限位
        m_array[249] = ((quint8)data.at(startbyte+31) & 0x02) >> 1;//柔性腿2#铁楔限位
        m_array[250] = ((quint8)data.at(startbyte+31) & 0x04) >> 2;//柔性腿3#铁楔限位
        m_array[251] = ((quint8)data.at(startbyte+31) & 0x08) >> 3;//柔性腿4#铁楔限位
        m_array[252] = ((quint8)data.at(startbyte+31) & 0x10) >> 4;//柔性腿5#铁楔限位
        m_array[253] = ((quint8)data.at(startbyte+31) & 0x20) >> 5;//柔性腿6#铁楔限位
        m_array[254] = ((quint8)data.at(startbyte+31) & 0x40) >> 6;//柔性腿7#铁楔限位
        m_array[255] = ((quint8)data.at(startbyte+31) & 0x80) >> 7;//柔性腿8#铁楔限位

    }break;
    case 0x01:
        qDebug()<<"go into case 0x01";
        m_array[256] = (quint8)data.at(7);
        m_array[257] = (quint8)data.at(8);
        m_array[258] = (quint8)data.at(9);
        m_array[259] = (quint8)data.at(10);//上升1高度编码器值(cm)

        m_array[260] = (quint8)data.at(11);
        m_array[261] = (quint8)data.at(12);
        m_array[262] = (quint8)data.at(13);
        m_array[263] = (quint8)data.at(14);//上升2高度编码器值(cm)

        m_array[264] = (quint8)data.at(15);
        m_array[265] = (quint8)data.at(16);
        m_array[266] = (quint8)data.at(17);
        m_array[267] = (quint8)data.at(18);//下主起升高度编码器值(mm)

        m_array[268] = (quint8)data.at(19);
        m_array[269] = (quint8)data.at(20);
        m_array[270] = (quint8)data.at(21);
        m_array[271] = (quint8)data.at(22);//下副起升高度编码器值(NULL)

        m_array[272] = (quint8)data.at(23);
        m_array[273] = (quint8)data.at(24);
        m_array[274] = (quint8)data.at(25);
        m_array[275] = (quint8)data.at(26);//上小车行走编码器值(mm)

        m_array[276] = (quint8)data.at(27);
        m_array[277] = (quint8)data.at(28);
        m_array[278] = (quint8)data.at(29);
        m_array[279] = (quint8)data.at(30);//下小车行走编码器值(cm)

        m_array[280] = (quint8)data.at(31);
        m_array[281] = (quint8)data.at(32);
        m_array[282] = (quint8)data.at(33);
        m_array[283] = (quint8)data.at(34);//钢腿行走编码器值(cm)

        m_array[284] = (quint8)data.at(35);
        m_array[285] = (quint8)data.at(36);
        m_array[286] = (quint8)data.at(37);
        m_array[287] = (quint8)data.at(38);//柔腿行走编码器值(cm)
        break;
    case 0x02:
        qDebug()<<"go into case 0x02";

        break;
    case 0x03:
        qDebug()<<"go into case 0x03";

        break;
    default:
        break;
    }

}

quint16 RelayStatusThread::GetCheckCode(QByteArray pSendBuf, int nEnd)  /*modbus rtu通信crc校验 */
{
    quint16 Crc =0xFFFF;
    quint8 i,j;
    for(i=0; i<nEnd; i++)
    {
        Crc ^= pSendBuf[i];
        for(j=0; j<8; j++)
        {
            if(Crc & 1)
            {
                Crc >>= 1;
                Crc ^= 0xA001;
            } else
            {
                Crc >>= 1;
            }
        }
    }
    return Crc;
}

void RelayStatusThread::sendToUpdate()
{
#ifdef WEIHAI
    emit sendAcquisitionData(m_array);
#endif
}
