#include "SubLimitStatus.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
SubLimitStatus::SubLimitStatus(QWidget *parent) :
    QWidget(parent)
  , m_size(145,25)
  , m_LimitName(NULL)
  , m_LimitStatus(NULL)
  , m_timer(NULL)
  , m_Status(false)
  , m_limitProperty(true)//默认常闭
{
    setupUI();
}
SubLimitStatus::~SubLimitStatus()
{
}
void SubLimitStatus::setLimitName(const QString &name)
{
    m_Name = name;
}

QString SubLimitStatus::getLimitName() const
{
    return m_Name;
}
//设置label的状态
void SubLimitStatus::setStatus(bool status)
{
    m_Status = status;
    accordingToStatusDispaly();
}

bool SubLimitStatus::getStatus()
{
    return m_Status;
}

void SubLimitStatus::setLimitProperty(bool switchProperty)
{
    m_limitProperty = switchProperty;
}

bool SubLimitStatus::getLimitProperty()
{
    return m_limitProperty;
}

void SubLimitStatus::accordingToStatusDispaly()
{
    if(m_limitProperty){
        if(m_Status) {
            m_LimitStatus->setStyleSheet("#limitstatus{border:0px;border-radius:0px;background-color:#0f9d58;}");
        }else{
            m_LimitStatus->setStyleSheet("#limitstatus{border:0px;border-radius:0px;background-color:#DB4437;}");
        }
    }else{
        if(!m_Status) {
            m_LimitStatus->setStyleSheet("#limitstatus{border:0px;border-radius:0px;background-color:#0f9d58;}");
        }else{
            m_LimitStatus->setStyleSheet("#limitstatus{border:0px;border-radius:0px;background-color:#DB4437;}");
        }
    }
}
 //label的布局
void SubLimitStatus::setupUI()
{
    setFixedSize(m_size);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("transparent"));
    setAutoFillBackground(true);
    setPalette(palette);

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(5);

    m_LimitName = new QLabel();
    m_LimitName->setObjectName("limitname");
    m_LimitName->setFixedSize(120,25);
    m_LimitName->setAlignment(Qt::AlignCenter);
    m_LimitName->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:transparent;}");

    m_LimitStatus = new QLabel();
    m_LimitStatus->setStyleSheet("QLabel{border:0px;border-radius:0px;background-color:#0f9d58;}");
    m_LimitStatus->setObjectName("limitstatus");
    m_LimitStatus->setFixedSize(20,20);
    m_LimitStatus->setAlignment(Qt::AlignCenter);
    hLayout->addWidget(m_LimitStatus,1,Qt::AlignCenter);
    hLayout->addWidget(m_LimitName,1,Qt::AlignCenter);

    setLayout(hLayout);
}
//获得label 成员 的接口
QLabel* SubLimitStatus::mygetmember(QString s)
{
    if(s=="limitname"){
       return  m_LimitName;
    }else if(s=="limitstatus"){
       return m_LimitStatus;
    }
}
