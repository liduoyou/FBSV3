#include "AcquisitionPortManager.h"
#include <QDebug>
#include <QStringList>
#include "../Settings/SettingsManager.h"
Q_GLOBAL_STATIC(AcquisitionPortManager, theInstance)
AcquisitionPortManager::AcquisitionPortManager(QObject *parent) :
    QObject(parent)
{
    createList();
}

AcquisitionPortManager::~AcquisitionPortManager()
{
}

AcquisitionPortManager *AcquisitionPortManager::globalInstance()
{
    return theInstance();
}

QMap<uint, AcquisitionPort *> AcquisitionPortManager::getSensorTypeList()
{
    return m_SensorTypeacquisitionPort;
}


QMap<uint, AcquisitionPort *> AcquisitionPortManager::getSwitchValueList()
{
    return m_SwitchValueacquisitionPort;
}

void AcquisitionPortManager::myslot(QByteArray data)
{
    emit signalWriteDataToSerial(data);
}

void AcquisitionPortManager::createList()
{
    int size = SettingsManager::globalInstance()->getAc_PortSize();
    qDebug()<<"SettingsManager::globalInstance()->getAc_PortSize()"<<SettingsManager::globalInstance()->getAc_PortSize();
    QString map;
    for(int i = 0;i < size;i++){
        AcquisitionPort* acquisitionPort;
        acquisitionPort = new AcquisitionPort();
        connect(acquisitionPort,SIGNAL(signalwriteSerialPort(QByteArray)),this,SLOT(myslot(QByteArray)));
        map = SettingsManager::globalInstance()->getAcquisitionPort("AcquisitionPort"+QString::number(i+1,10));
        if(!map.isEmpty()){
            acquisitionPort->setACID(i+1);//记录下在文件中的 顺序编号
            if(map.split(",").at(1).toInt() == 0){
                m_SensorTypeacquisitionPort.insertMulti(map.split(",").at(0).toUInt(),acquisitionPort);
            }else if(map.split(",").at(1).toInt() == 1){
                m_SwitchValueacquisitionPort.insertMulti(map.split(",").at(0).toUInt(),acquisitionPort);
            }
        }
    }
}
