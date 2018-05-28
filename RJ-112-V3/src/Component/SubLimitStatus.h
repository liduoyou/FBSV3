#ifndef LIMITSTATUS_H
#define LIMITSTATUS_H

#include <QWidget>
#include<QLabel>
#include <QString>
#include <QSize>
#include <QTimer>
class SubLimitStatus : public QWidget
{
    Q_OBJECT
public:
    explicit SubLimitStatus(QWidget *parent = 0);
    ~SubLimitStatus();
    void setupUI();
    QLabel* mygetmember(QString s);//根据s 得到对象label
    void setLimitName(const QString& name);//限位量名
    QString getLimitName()const;
    void setStatus(bool status);//开关量的状态
    bool getStatus();
    void setLimitProperty(bool limitProperty);//常开常闭点
    bool getLimitProperty();

signals:
    
public slots:
       void accordingToStatusDispaly();
private:
    QSize          m_size;
    QLabel*        m_LimitName;
    QLabel*        m_LimitStatus;
    QTimer*        m_timer;
    QString        m_Name;
    bool           m_Status;
    bool           m_limitProperty;
    
};

#endif // LIMITSTATUS_H
