#include "ReadConfig.h"
#include <QDebug>
#include <QMessageBox>
#include <QXmlStreamAttributes>
#include "SettingsManager.h"
const QString Ac_Portstr = "AcquisitionPort";
const QString ConfigDocPath = "/sddisk/";
ReadConfig::ReadConfig():
    _msettings(NULL)
{
}

ReadConfig::~ReadConfig()
{
    delete file;
    file = 0;
    delete dom;
    dom = 0;
}

bool ReadConfig::parseXML()
{
    _msettings = SettingsManager::globalInstance();

    QString strfilename = QString(ConfigDocPath+"Config.xml");
    file = new QFile(strfilename);
    if(!file->open(QFile::ReadOnly)){
        qDebug()<<file->errorString();
        return false;
    }else{
        qDebug()<<"open xml successfully";
    }

    dom = new QDomDocument();
    if(!dom->setContent(file)){
        qDebug()<<"setContent to dom failed!";
        file->close();
        return false;
    }
    if(dom->isNull()){
        qDebug()<<"dom is null";
    }
    return true;
}

void ReadConfig::parseXMLToCreateIni()
{
    QDomNodeList nodelist = dom->elementsByTagName("Collector");    /*< 读取类型节点集合 */
    for(int i=0; i<nodelist.count(); i++){
        QDomNode node = nodelist.at(i);
        QString Ac_PortNo = parseCollector(node);
        _msettings->setAcquisitionPort(Ac_Portstr+QString::number(i+1,10),Ac_PortNo);
        QDomNodeList collectorlist = node.childNodes(); /*< 获取字节点集合 */
        for(int j=0; j<collectorlist.count(); j++){
            QDomNode channelnode = collectorlist.at(j);

            if(channelnode.toElement().tagName() == "MainNo"){
                _msettings->setSysBaseInfor("EquiNumber",channelnode.toElement().text());
            }if(channelnode.toElement().tagName() == "GroupNo"){
                _msettings->setGroupID(channelnode.toElement().text());
            }if(channelnode.toElement().tagName() == "CollectorType"){
                _msettings->setAcquisitionPort(Ac_Portstr+QString::number(i+1,10),Ac_PortNo+","+channelnode.toElement().text());
            }if(channelnode.toElement().tagName() == "ChannelItems"){
                parseChannelItems(QString::number(i+1,10),channelnode);
            }
        }
    }
}

QString ReadConfig::parseCollector(QDomNode collectorNode)
{
    QString CollectorNo = collectorNode.toElement().attribute("CollectorNo");
    return CollectorNo;
}

void ReadConfig::parseChannelItems(const QString &Ac_PortNo, QDomNode channelItemsNode)
{
    QString _key;
    QString _inOutType;
    QString _onOROffType = "";
    QDomNodeList channelitems = channelItemsNode.childNodes();
    for(int i=0; i<channelitems.count(); i++){
        QDomNode channelitem = channelitems.at(i);
        QString ChannelNo = channelitem.toElement().attribute("ChannelNo");//通道号

        QDomNodeList channelitemlist = channelitem.childNodes(); /*< 获取字节点集合 */
        for(int j=0; j<channelitemlist.count(); j++){
            QDomNode channelitemnode = channelitemlist.at(j);

            if(channelitemnode.toElement().tagName() == "InOutType"){
                _inOutType = channelitemnode.toElement().text();
            }if(channelitemnode.toElement().tagName() == "OnOROffType"){
                _onOROffType = channelitemnode.toElement().text();
            }if(channelitemnode.toElement().tagName() == "MonitorObject"){
                _key = channelitemnode.toElement().text();
            }if(channelitemnode.toElement().tagName() == "SensorType"){
                _key += channelitemnode.toElement().text();
                if(_onOROffType.isEmpty()){
                    _msettings->setChannelID(Ac_Portstr+Ac_PortNo,_key,ChannelNo+","+_inOutType);
                }else{
                    _msettings->setChannelID(Ac_Portstr+Ac_PortNo,_key,ChannelNo+","+_inOutType+","+_onOROffType);
                }
            }
        }
    }
}
