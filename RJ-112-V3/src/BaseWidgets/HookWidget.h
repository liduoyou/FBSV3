#ifndef HOOKWIDGET_H
#define HOOKWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QHBoxLayout>
#include <QProgressBar>
#include "../BaseClass/Hook.h"
class RoundWidget;
class SubLimitStatus;
class HookWidget : public QWidget,public Hook
{
    Q_OBJECT
public:
    explicit HookWidget(HookType _type, QWidget *parent = 0);
    ~HookWidget();

    void setHookName();
protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *e);
signals:
    
public slots:
    void updateValueChange();
    void updateStatusChange();
private:

    void           setupUI();
    QHBoxLayout*   initAbstractValueLayout();
    QWidget*       initDetailValueWidget();

    QSize          m_size;

    QPushButton*   m_BtnHookName;
    QWidget*       m_detailValueWidget;
    //开关量
    QLabel*        m_UpName;
    QLabel*        m_UpStatus;
    QLabel*        m_DownName;
    QLabel*        m_DownStatus;
    QLabel*        m_BrakingName;
    QLabel*        m_BrakingStatus;
    QLabel*        m_BrakingNumber;//制动次数
    QLabel*        m_BrakingNumberUnit;//制动次数单位:次

    //开关量 限位状态
    SubLimitStatus*        m_HookUpLimit;//起升上限位 停止限位
    SubLimitStatus*        m_HookDownLimit;//起升下限位 停止限位
    SubLimitStatus*        m_HookUpCutSpeedLimit;//起升上减速限位
    SubLimitStatus*        m_HookDownCutSpeedLimit;//起升下减速限位
    SubLimitStatus*        m_HookUpOverLimit;//起升上极限限位  超限位
    SubLimitStatus*        m_HookDownOverLimit;//起升下极限限位  超限位

    QLabel*        m_GearName;
    QLabel*        m_GearStatus;

    //数据量
    QLabel*        m_WeightName;//重量
    QLabel*        m_WeightValue;//

    QLabel*        m_HeightName;//高度
    QLabel*        m_HeightValue;

    QLabel*        m_SpeedName;//速度
    QLabel*        m_SpeedValue;

    QLabel*        m_ScopeName;//幅度
    QLabel*        m_ScopeValue;

    RoundWidget*   m_RoundwidgetWeight;//重量
    RoundWidget*   m_RoundwidgetHeight;//高度
    RoundWidget*   m_RoundwidgetSpeed;//速度
    RoundWidget*   m_RoundwidgetScope;//幅度
    RoundWidget*   m_RoundwidgetMoment;//力矩

    HookType       m_type;
};

#endif // HOOKWIDGET_H
