#include "CardInfo.h"
#include <QDebug>
CardInfo::CardInfo():
    _dataSize(0)
  , _codeSize(0)
  , _cacheSize(0)
  , _lastestVerCode(0)
{
    setAbsolutePath();
}


CardInfo::~CardInfo()
{
    qDebug()<<"CardInfo::~CardInfo()";
}

const QString& CardInfo::TaskAffinity() const
{
    return m_taskAffinity;
}

void CardInfo::setTaskAffinity(const QString& val)
{
    m_taskAffinity = val;
}

const QString& CardInfo::processName() const
{
    return m_processName;
}

const QString& CardInfo::permission() const
{
    return m_permission;
}

void CardInfo::setPermission(const QString& val)
{
    m_permission = val;
}

void CardInfo::setProcessName(const QString& val)
{
    m_processName = val;
}

const QString CardInfo::absolutePath() const
{
    return m_absolutePath;
}

void CardInfo::setAbsolutePath(const QString &val)
{
    m_absolutePath = val;
}

const QString CardInfo::className() const
{
    return m_className;
}

void CardInfo::setClassName(const QString& val)
{
     m_className = val;
}

const QString& CardInfo::sourceDir() const
{
	return _sourceDir;
}

void CardInfo::setSourceDir(const QString& val)
{
	_sourceDir = val;
}

const QString& CardInfo::publicSourceDir() const
{
	return _publicSourceDir;
}

void CardInfo::setPublicSourceDir(const QString& val)
{
	_publicSourceDir = val;
}

const QString& CardInfo::dataDir() const
{
	return _dataDir;
}

void CardInfo::setDataDir(const QString& val)
{
	_dataDir = val;
}
 
int CardInfo::targetSdkVersion() const
{
	return _targetSdkVersion;
}

void CardInfo::setTargetSdkVersion(int val)
{
	_targetSdkVersion = val;
}

int CardInfo::theme() const
{
	return _theme;
}

void CardInfo::setTheme(int val)
{
	_theme = val;
}

int CardInfo::flags() const
{
	return _flags;
}

void CardInfo::setFlags(int val)
{
	_flags = val;
}

int CardInfo::uid()
{
	return _uid;
}

void CardInfo::setUid(int val)
{
	_uid = val;
}

void CardInfo::setIcon(QSharedPointer<QPixmap>& icon)
{
	_icon = icon;
}

QSharedPointer<QPixmap> CardInfo::getIcon()
{
	return _icon;
}

QString& CardInfo::appName()
{
    return m_appName;
}

void CardInfo::setAppName(const QString& val)
{
    m_appName = val;
}

int CardInfo::getDataSize() const
{
	return _dataSize;
}

void CardInfo::setDataSize(int val)
{
	_dataSize = val;
}

int CardInfo::getCodeSize() const
{
	return _codeSize;
}

void CardInfo::setCodeSize(int val)
{
	_codeSize = val;
}

int CardInfo::getCacheSize() const
{
	return _cacheSize;
}

void CardInfo::setCacheSize(int val)
{
	_cacheSize = val;
}

int CardInfo::getVerCode() const
{
	return _verCode;
}

void CardInfo::setVerCode(int val)
{
	_verCode = val;
}

QString CardInfo::getVerName() const
{
    return m_verName;
}

void CardInfo::setVerName(const QString& val)
{
    m_verName = val;
}

QString CardInfo::getPackageName() const
{
    return m_packageName;
}

void CardInfo::setPackageName(QString val)
{
    m_packageName = val;
}
bool CardInfo::isAvaliableToUpdate() const{
    if(_verCode < _lastestVerCode){
        return true;
    }
    return false;
}
int CardInfo::lastestVerCode() const
{
    return _lastestVerCode;
}

void CardInfo::setLastestVerCode(int lastestVerCode)
{
    _lastestVerCode = lastestVerCode;
}
QString CardInfo::lastestVerName() const
{
    return m_lastestVerName;
}

void CardInfo::setLastestVerName(const QString &lastestVerName)
{
    m_lastestVerName = lastestVerName;
}

QString CardInfo::lastestVerDesc() const
{
    return m_lastestVerDesc;
}

void CardInfo::setLastestVerDesc(const QString &lastestVerDesc)
{
    m_lastestVerDesc = lastestVerDesc;
}

QString CardInfo::downloadUrl() const
{
    return m_downloadUrl;
}

void CardInfo::setDownloadUrl(const QString &downloadUrl)
{
    m_downloadUrl = downloadUrl;
}

QString CardInfo::shortKey() const
{
    return m_shortKey;
}

void CardInfo::setShortKey(const QString& val)
{
    m_shortKey = val;
}

int CardInfo::getTotalSize()
{
    return _cacheSize + _codeSize + _dataSize;
}
