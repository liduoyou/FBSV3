#ifndef CARDINFO_H
#define CARDINFO_H

#include <QString>
#include <QPixmap>
#include <QMetaType>
#include <QStringList>
#include <QObject>
#include <QApplication>
/*卡片信息类*/
class CardInfo:public QObject
{
    Q_OBJECT
public:
    CardInfo();
    ~CardInfo();
	const QString& TaskAffinity() const;
	void setTaskAffinity(const QString& val);
	const QString& permission() const;
	void setPermission(const QString& val);
	const QString& processName() const;
	void setProcessName(const QString& val);

    const QString absolutePath() const;
    void setAbsolutePath(const QString& val = QApplication::applicationDirPath()+"/images");

	const QString className() const;
    void setClassName(const QString& val = "title.png");
	const QString& sourceDir() const;
	void setSourceDir(const QString& val);
	const QString& publicSourceDir() const;
	void setPublicSourceDir(const QString& val);
	const QString& dataDir() const;
	void setDataDir(const QString& val);
	int targetSdkVersion() const;
	void setTargetSdkVersion(int val);
	int theme() const;
	void setTheme(int val);
	int flags() const;
	void setFlags(int val);
	int uid();
	void setUid(int val);
	void setIcon(QSharedPointer<QPixmap>& icon);

	QString& appName();
	QString shortKey() const;
	void setShortKey(const QString& val);
    void setAppName(const QString& val = "appname");
	QSharedPointer<QPixmap> getIcon();
	int getTotalSize();
	int getDataSize() const;
	void setDataSize(int val);
	int getCodeSize() const;
	void setCodeSize(int val);
	int getCacheSize() const;
	void setCacheSize(int val);
	int getVerCode() const;
	void setVerCode(int val);
	QString getVerName() const;
	void setVerName(const QString& val);
	QString getPackageName() const;

	void setPackageName(QString val);
    bool isAvaliableToUpdate() const;

    int lastestVerCode() const;
    void setLastestVerCode(int lastestVerCode);

    QString lastestVerName() const;
    void setLastestVerName(const QString &lastestVerName);

    QString lastestVerDesc() const;
    void setLastestVerDesc(const QString &lastestVerDesc);

    QString downloadUrl() const;
    void setDownloadUrl(const QString &downloadUrl);

signals:

private slots:


private:
    QString m_taskAffinity;
    QString m_permission;
    QString m_processName;
    QString m_absolutePath;
    QString m_className;
    QString m_appName;
    QString m_verName;
    QString m_packageName;
    QString m_lastestVerName;
    QString m_lastestVerDesc;
    QString m_downloadUrl;
    QString m_shortKey;
	
	int _theme;
	int _flags;
	int _dataSize;
	int _codeSize;
	int _cacheSize;
	int _verCode;
    int _lastestVerCode;
	
	QString _sourceDir;
	QString _publicSourceDir;
	QString _dataDir;
    QString _apkPath;
	int _uid;
	int _targetSdkVersion;

	QSharedPointer<QPixmap> _icon;
};
Q_DECLARE_METATYPE(QSharedPointer<CardInfo>)
#endif //CARDINFO_H


