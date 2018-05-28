#ifndef ACQUISITIONPORTMANAGER_H
#define ACQUISITIONPORTMANAGER_H

#include <QObject>
#include <QMap>
#include "AcquisitionPort.h"
class AcquisitionPortManager : public QObject
{
    Q_OBJECT
public:
    explicit AcquisitionPortManager(QObject *parent = 0);
    ~AcquisitionPortManager();

    static AcquisitionPortManager *globalInstance();
    QMap<uint, AcquisitionPort *> getSensorTypeList();
    QMap<uint, AcquisitionPort *> getSwitchValueList();

    void createList();
signals:
    void signalWriteDataToSerial(QByteArray);
private slots:
    void myslot(QByteArray data);
private:

    QMap<uint,AcquisitionPort*>  m_SensorTypeacquisitionPort;
    QMap<uint,AcquisitionPort*>  m_SwitchValueacquisitionPort;
};

#endif // ACQUISITIONPORTMANAGER_H
