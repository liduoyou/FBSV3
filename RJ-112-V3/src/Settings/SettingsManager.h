#ifndef PSETTINGSMANAGER_H
#define PSETTINGSMANAGER_H

/***********************************************************************************************
 *abstract:获取配置项操作，更新配置项操作
 **********************************************************************************************/
#include <QString>
#include <QObject>
#include <QSettings>
#include <QMap>
#include <QMutex>
//首次启动
const QString c_setting_key_firstStartFlag = "Start";
const bool c_setting_value_firstStartFlag = true;
//版本信息
const QString c_setting_key_version = "Updater";//更新时参考
const QString c_setting_value_version = "version 2.0.0";

const QString c_setting_key_fileFlag = "FileFlag";//保存 向文件中插入 数据条数
const QString c_setting_value_fileFlag="1";// 1

//系统管理员信息
const QString c_setting_key_LoginInfor = "LoginInfor";//系统管理员信息
const QString c_setting_value_LoginInfor = "admin";//用户名,用户密码

//系统管理员信息
const QString c_setting_key_userLoginInfor = "UserLoginInfor";//系统管理员信息
const QString c_setting_value_userLoginInfor = "User";//用户名,用户密码

//自动更新
const QString c_setting_key_isAutoUpdate = "isAutoUpdate"; //是否开启自动更新
const bool c_setting_value_isAutoUpdate = true;

//首页主题版本
const QString c_setting_key_homeThemeVersion = "homeThemeVersion"; //首页主题版本
const int c_setting_value_homeThemeVersion = 0;

//设置系统基本信息
const QString c_setting_key_SysBaseInfor = "SysBaseInfor"; //系统基本信息设置
const QString c_setting_value_initSysBaseInfor = "100"; //系统基本信息设置

//设置标定
const QString c_setting_key_SensorCal = "SensorCal"; //标定设置
const QString c_setting_value_initSensorCal = "100"; //标定设置

//设置阈值
const QString c_setting_key_Threshold = "Threshold"; //阈值设置
const QString c_setting_value_initThreshold = "20"; //阈值设置

/* 设置常量:  编码器初始值  Mc
编码器运行以后实际值 Ms
碰到限位器延时一秒钟更新初始值 Mc
编码器从动轮直径 D
编码器从动轮周长 L=π*D/1000
编码器转动一周变化AD值 Md
行程：S = (Ms-Mc)*(L/Md) = (Ms-Mc)*(π*D/1000*Md)*/
const QString c_setting_key_constant = "Constant"; //设置常量

const QString c_setting_value_SteelLegDistanceconstantMc = "6000000"; //钢腿行程Mc
const QString c_setting_value_SoftLegDistanceconstantMc = "6000000"; //柔腿行程Mc
const QString c_setting_value_UpVehicleDistanceconstantMc = "1000"; //上小车行程Mc
const QString c_setting_value_DownVehicleDistanceconstantMc = "1000"; //下小车行程Mc

const QString c_setting_value_SteelLegDistanceconstantD = "200"; //钢腿行程D
const QString c_setting_value_SoftLegDistanceconstantD = "200"; //柔腿行程D
const QString c_setting_value_UpVehicleDistanceconstantD = "200"; //上小车行程D
const QString c_setting_value_DownVehicleDistanceconstantD = "200"; //下小车行程D

const QString c_setting_value_SteelLegDistanceconstantMd = "4096"; //钢腿行程Md
const QString c_setting_value_SoftLegDistanceconstantMd = "4096"; //柔腿行程Md
const QString c_setting_value_UpVehicleDistanceconstantMd = "64"; //上小车行程Md
const QString c_setting_value_DownVehicleDistanceconstantMd = "64"; //下小车行程Md

//群组编号
const QString c_setting_key_GroupID = "Group"; //群组编号
const QString c_setting_value_initGroupID = "0"; //群组编号设置

//SOUND
const QString c_setting_key_Sound = "SOUNDLOUND"; //SOUND
const QString c_setting_value_initSound = "10"; //SOUND

//设置采集端设备编号
const QString c_setting_key_AcquisitionPort = "AcquisitionPort"; //采集端设备编号
const QString c_setting_value_initAcquisitionPort = "112601,0"; //采集端设备编号设置

//本地安装选择
const QString c_setting_key_localInstallChoosePath = "LoaclInstallDefChoosePath"; //本地安装默认选择路径设置
#ifdef Q_OS_LINUX
const QString c_setting_value_initLocalInstallChoosePath = "/../Resources/download/app"; //本地安装默认选择的相对路径
#else
const QString c_setting_value_initLocalInstallChoosePath = "/Resources/download/app";
#endif

//备份路径
const QString c_setting_key_backupSavePath = "backupDefSavePath"; //备份文件默认保存路径设置
#ifdef Q_OS_LINUX
const QString c_setting_value_initBackupSavePath = "/../Resources/backups/"; //备份文件默认保存的相对路径
#else
const QString c_setting_value_initBackupSavePath = "/Resources/backups/";
#endif

#ifndef Q_OS_LINUX
const QString c_setting_key_quitOnCloseFlag = "quitOnClose"; //关闭窗口后是否退出程序设置
const int c_setting_value_quitOnClose = 2; //1 直接退出 2 最小化
#endif

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    ~SettingsManager();
    static SettingsManager* globalInstance();

    bool getFirstStart(const QString& key);
    void setFirstStart(const QString &key,bool value);
    QString getVersion(const QString &key);
    void setVersion(const QString &key,const QString &value);
    QString getLoginInfor(const QString &key);
    void setLoginInfor(const QString &key, const QString &value);

    QString getUserLoginInfor(const QString &key);
    void setUserLoginInfor(const QString &key, const QString &value);

    bool getIsAutoUpdate();
    void setIsAutoUpdate(bool isAutoUpdate);

    int getHomeThemeVersion();
    void setHomeThemeVersion(int version);

    QString getSysBaseInfor(const QString &key);//设置系统基本信息
    void setSysBaseInfor(const QString &key,const QString &value);
    QString getSensorCal(const QString &key);//设置标定
    void setSensorCal(const QString &key,const QString &value);
    QString getThreshold(const QString &key);//设置阈值
    void setThreshold(const QString &key,const QString &value);

    QString getinitialconstantValue(const QString &key);//设置标定
    void setinitialconstantValue(const QString &key,const QString &value);

    QString getGroupID();//获取群组编号
    void setGroupID(const QString &value);

    QString getAcquisitionPort(const QString &key);//获取采集端设备编号
    int getAc_PortSize();//获取采集端设备编号
    void setAcquisitionPort(const QString &key, QString value);

    QString getChannelID(const QString &Port,const QString &key);//采集端通道ID
    void setChannelID(const QString &Port, const QString &key, const QString &value);

    QString getLocalInstallChoosePath(); //本地安装路径
    void setLocalInstallChoosePath(const QString &value);
    QString getBackupPath();//备份路径
    void setBackupPath(const QString &value);

    QString getACportAndChannelID(const QString &key);

    void setfileflag(int value);
    int getfileflag();
    QString getSoundLound();
    void setSoundLound(const QString &value);
signals:
    void signal_backupPathChanged(const QString &path);

private:
    SettingsManager(QObject *parent = 0);
    bool pathCheck(const QString &path);

    QSettings       m_setting;
    static QMutex   m_mutex;
    static SettingsManager* m_pInstance;
    const static QString config_File;
};

#endif // SETTINGSMANAGER_H
