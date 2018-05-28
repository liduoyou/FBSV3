#include "SettingsManager.h"
#include <QDebug>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include "../AcquisitionPort/AcquisitionPortManager.h"
SettingsManager* SettingsManager::m_pInstance = NULL;
QMutex  SettingsManager::m_mutex;

const QString SettingsManager::config_File = "/reaki/Config.ini";//注释目录/reaki/Config.ini

SettingsManager::~SettingsManager()
{
    qDebug()<<"SettingsManager::~SettingsManager()";
    m_setting.sync();
}

SettingsManager *SettingsManager::globalInstance()
{
    if(m_pInstance == NULL)

    {
        m_mutex.lock();
        if(m_pInstance == NULL)
        {
            m_pInstance = new SettingsManager;
        }
        m_mutex.unlock();
    }
    return m_pInstance;
}

bool SettingsManager::getFirstStart(const QString &key)
{
    m_setting.beginGroup(c_setting_key_firstStartFlag);
    if(!m_setting.contains(key))
    {
        m_setting.setValue(key, c_setting_value_firstStartFlag);
    }
    bool flag = m_setting.value(key).toBool();
    m_setting.endGroup();
    return flag;
}

void SettingsManager::setFirstStart(const QString& key, bool value)
{
    m_setting.beginGroup(c_setting_key_firstStartFlag);
    m_setting.setValue(key, value);
    m_setting.endGroup();
}

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent)
    ,m_setting(config_File, QSettings::IniFormat)
{
}

void SettingsManager::setIsAutoUpdate(bool isAutoUpdate){
    m_setting.setValue(c_setting_key_isAutoUpdate, isAutoUpdate);
}

void SettingsManager::setHomeThemeVersion(int version){
    m_setting.setValue(c_setting_key_homeThemeVersion, version);
}

QString SettingsManager::getSysBaseInfor(const QString &key)
{
    m_setting.beginGroup(c_setting_key_SysBaseInfor);
    if(!m_setting.contains(key))
    {
        m_setting.setValue(key, c_setting_value_initSysBaseInfor);
    }
    QString str = m_setting.value(key).toString();
    m_setting.endGroup();
    return str;
}

void SettingsManager::setSysBaseInfor(const QString &key, const QString &value)
{
    m_setting.beginGroup(c_setting_key_SysBaseInfor);
    m_setting.setValue(key, value);
    m_setting.endGroup();
}

QString SettingsManager::getSensorCal(const QString &key)
{
    m_setting.beginGroup(c_setting_key_SensorCal);
    if(!m_setting.contains(key))
    {
        m_setting.setValue(key, c_setting_value_initSensorCal);
    }
    QString str = m_setting.value(key).toString();
    m_setting.endGroup();
    return str;
}

void SettingsManager::setfileflag(int value)
{
    m_setting.beginGroup(c_setting_key_fileFlag);
    m_setting.setValue("AmountFlag",QString::number(value));
    m_setting.endGroup();
}

int SettingsManager::getfileflag()
{
    m_setting.beginGroup(c_setting_key_fileFlag);
    if(!m_setting.contains("AmountFlag"))
    {
        m_setting.setValue("AmountFlag", c_setting_value_fileFlag);
    }
    int flag = m_setting.value("AmountFlag").toInt();
    m_setting.endGroup();
    return flag;
}

void SettingsManager::setSensorCal(const QString &key, const QString &value)
{
    m_setting.beginGroup(c_setting_key_SensorCal);
    m_setting.setValue(key, value);
    m_setting.endGroup();
}

QString SettingsManager::getThreshold(const QString &key)
{
    m_setting.beginGroup(c_setting_key_Threshold);
    if(!m_setting.contains(key))
    {
        m_setting.setValue(key, c_setting_value_initThreshold);
    }
    QString str = m_setting.value(key).toString();
    m_setting.endGroup();
    return str;
}

void SettingsManager::setThreshold(const QString &key, const QString &value)
{
    m_setting.beginGroup(c_setting_key_Threshold);
    m_setting.setValue(key, value);
    m_setting.endGroup();
}

void SettingsManager::setinitialconstantValue(const QString &key, const QString &value)
{
    m_setting.beginGroup(c_setting_key_constant);
    m_setting.setValue(key, value);
    m_setting.endGroup();
}

QString SettingsManager::getinitialconstantValue(const QString &key)
{
    m_setting.beginGroup(c_setting_key_constant);
    if(!m_setting.contains(key))
    {
        if(key.contains("constantMc")){
            if(key.contains("Steelleg")){
                m_setting.setValue(key, c_setting_value_SteelLegDistanceconstantMc);
            }else if(key.contains("Softleg")){
                m_setting.setValue(key, c_setting_value_SoftLegDistanceconstantMc);
            }else if(key.contains("UpVehicle")){
                m_setting.setValue(key, c_setting_value_UpVehicleDistanceconstantMc);
            }else if(key.contains("DownVehicle")){
                m_setting.setValue(key, c_setting_value_DownVehicleDistanceconstantMc);
            }
        }else if(key.contains("constantD")){
            if(key.contains("Steelleg")){
                m_setting.setValue(key, c_setting_value_SteelLegDistanceconstantD);
            }else if(key.contains("Softleg")){
                m_setting.setValue(key, c_setting_value_SoftLegDistanceconstantD);
            }else if(key.contains("UpVehicle")){
                m_setting.setValue(key, c_setting_value_UpVehicleDistanceconstantD);
            }else if(key.contains("DownVehicle")){
                m_setting.setValue(key, c_setting_value_DownVehicleDistanceconstantD);
            }
        }else if(key.contains("constantMd")){
            if(key.contains("Steelleg")){
                m_setting.setValue(key, c_setting_value_SteelLegDistanceconstantMd);
            }else if(key.contains("Softleg")){
                m_setting.setValue(key, c_setting_value_SoftLegDistanceconstantMd);
            }else if(key.contains("UpVehicle")){
                m_setting.setValue(key, c_setting_value_UpVehicleDistanceconstantMd);
            }else if(key.contains("DownVehicle")){
                m_setting.setValue(key, c_setting_value_DownVehicleDistanceconstantMd);
            }
        }
    }
    QString str = m_setting.value(key).toString();
    m_setting.endGroup();
    return str;
}

QString SettingsManager::getGroupID()
{
    m_setting.beginGroup(c_setting_key_GroupID);
    if(!m_setting.contains("GroupID"))
    {
        m_setting.setValue("GroupID", c_setting_value_initGroupID);
    }
    QString str = m_setting.value("GroupID").toString();
    m_setting.endGroup();
    return str;
}

void SettingsManager::setGroupID(const QString &value)
{
    m_setting.beginGroup(c_setting_key_GroupID);
    m_setting.setValue("GroupID", value);
    m_setting.endGroup();
}

QString SettingsManager::getSoundLound()
{
    m_setting.beginGroup(c_setting_key_Sound);
    if(!m_setting.contains("Sound"))
    {
        m_setting.setValue("Sound", c_setting_value_initSound);
    }
    QString str = m_setting.value("Sound").toString();
    m_setting.endGroup();
    return str;
}

void SettingsManager::setSoundLound(const QString &value)
{
    m_setting.beginGroup(c_setting_key_Sound);
    QMutex mutex;
    mutex.lock();
    m_setting.setValue("Sound", value);
    mutex.unlock();
    m_setting.endGroup();
}

QString SettingsManager::getAcquisitionPort(const QString &key)
{
    m_setting.beginGroup(c_setting_key_AcquisitionPort);
    QString str = "";
//    if(!m_setting.contains(key)){
//        m_setting.setValue(key, c_setting_value_initAcquisitionPort);
//    }
    str = m_setting.value(key).toString();
    m_setting.endGroup();
    return str;
}

int SettingsManager::getAc_PortSize()
{
    m_setting.beginGroup(c_setting_key_AcquisitionPort);
    int m_size = m_setting.childKeys().size();
    m_setting.endGroup();
    return m_size;
}

void SettingsManager::setAcquisitionPort(const QString &key, QString value)
{
    m_setting.beginGroup(c_setting_key_AcquisitionPort);
    m_setting.setValue(key, value);
    m_setting.endGroup();
}

QString SettingsManager::getChannelID(const QString &Port, const QString &key)
{
    m_setting.beginGroup(Port);
    QString channelID;
    channelID = m_setting.value(key).toString();
    m_setting.endGroup();
    return channelID;
}

void SettingsManager::setChannelID(const QString &Port,const QString &key, const QString& value)
{
    m_setting.beginGroup(Port);
    m_setting.setValue(key, value);
    m_setting.endGroup();
}

QString SettingsManager::getACportAndChannelID(const QString &key)
{
    QString str = "AcquisitionPort%1";
//    qDebug()<<"key"<<key;
    QString map;int channel;
    int ACPortcount = getAc_PortSize();
//    qDebug()<<"ACPortcount"<<ACPortcount;
    for(int i = 1;i <= ACPortcount;i++){
        QString ch_constant = getChannelID(str.arg(QString::number(i,10)),key);
//        qDebug()<<"ch_constant"<<ch_constant;
        if(!ch_constant.isEmpty()){
            channel = ch_constant.toUInt();
            map = QString::number(i,10)+","+ch_constant;/*QString::number(channel,10);*/
//            qDebug()<<"map"<<map;
            return map;
        }
    }
    return "";
}

void SettingsManager::setBackupPath(const QString &value)
{
    QString path = QDir::cleanPath(value);
    QDir dir(path);
    if(dir.exists() || pathCheck(path))
    {
        m_setting.setValue(c_setting_key_backupSavePath, path);
        emit signal_backupPathChanged(path);
    }
}

QString SettingsManager::getVersion(const QString &key)
{
    m_setting.beginGroup(c_setting_key_version);
    if(!m_setting.contains(key))
    {
        m_setting.setValue(key, c_setting_value_version);
    }
    QString str = m_setting.value(key).toString();
    m_setting.endGroup();
    return str;
}

void SettingsManager::setVersion(const QString &key, const QString &value)
{
    m_setting.beginGroup(c_setting_key_version);
    m_setting.setValue(key, value);
    m_setting.endGroup();
}

QString SettingsManager::getLoginInfor(const QString &key)
{
    m_setting.beginGroup(c_setting_key_LoginInfor);
    if(!m_setting.contains(key))
    {
        m_setting.setValue(key, c_setting_value_LoginInfor);
    }
    QString str = m_setting.value(key).toString();
    m_setting.endGroup();
    return str;
}

void SettingsManager::setLoginInfor(const QString &key, const QString &value)
{
    m_setting.beginGroup(c_setting_key_LoginInfor);
    m_setting.setValue(key, value);
    m_setting.endGroup();
}

QString SettingsManager::getUserLoginInfor(const QString &key)
{
    m_setting.beginGroup(c_setting_key_userLoginInfor);
    if(!m_setting.contains(key))
    {
        m_setting.setValue(key, c_setting_value_userLoginInfor);
    }
    QString str = m_setting.value(key).toString();
    m_setting.endGroup();
    return str;
}

void SettingsManager::setUserLoginInfor(const QString &key, const QString &value)
{
    m_setting.beginGroup(c_setting_key_userLoginInfor);
    m_setting.setValue(key, value);
    m_setting.endGroup();
}

bool SettingsManager::getIsAutoUpdate(){
    if(!m_setting.contains(c_setting_key_isAutoUpdate))
    {
        m_setting.setValue(c_setting_key_isAutoUpdate, c_setting_value_isAutoUpdate);
    }
    return m_setting.value(c_setting_key_isAutoUpdate).toBool();
}

int SettingsManager::getHomeThemeVersion(){
    if(!m_setting.contains(c_setting_key_homeThemeVersion)){
        m_setting.setValue(c_setting_key_homeThemeVersion, c_setting_value_homeThemeVersion);
    }
    return m_setting.value(c_setting_key_homeThemeVersion).toInt();
}

QString SettingsManager::getLocalInstallChoosePath()
{
    m_setting.beginGroup("LoaclInstallDefChoosePath");
    if(!m_setting.contains(c_setting_key_localInstallChoosePath))
    {
        QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + c_setting_value_initLocalInstallChoosePath);
        m_setting.setValue(c_setting_key_localInstallChoosePath, path);
    }
    QString str = m_setting.value(c_setting_key_localInstallChoosePath).toString();
    m_setting.endGroup();
    return str;
}

void SettingsManager::setLocalInstallChoosePath(const QString &value)
{
    QString path = QDir::cleanPath(value);
    QDir dir(path);
    if(dir.exists())
    {
        m_setting.setValue(c_setting_key_localInstallChoosePath, path);
    }
}

QString SettingsManager::getBackupPath()
{
    if(!m_setting.contains(c_setting_key_backupSavePath))
    {
        QString path = QDir::cleanPath(QCoreApplication::applicationDirPath() + c_setting_value_initBackupSavePath);
        m_setting.setValue(c_setting_key_backupSavePath, path);
    }
    QString path = m_setting.value(c_setting_key_backupSavePath).toString();;
    pathCheck(path);
    return path;
}

bool SettingsManager::pathCheck(const QString &path){
    if(path.isEmpty()){
        return false;
    }
    QDir dir(path);
    if(dir.exists()){
        return false;
    }

    if(QDir::isAbsolutePath(path)){
        return dir.mkpath(path);
    }else{
        QDir currDir(".");
         return currDir.mkpath(path);
    }
    return false;
}
