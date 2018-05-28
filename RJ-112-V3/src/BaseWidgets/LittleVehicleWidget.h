#ifndef LITTLEVEHICLEWIDGET_H
#define LITTLEVEHICLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "../BaseClass/LittleVehicle.h"
class SubLimitStatus;
class RoundWidget;
class LittleVehicleWidget : public QWidget,public LittleVehicle
{
    Q_OBJECT
public:
    explicit LittleVehicleWidget(LittleVehicleType _type,QWidget *parent = 0);
    ~LittleVehicleWidget();

    void setLittleVehicleName();
protected:
    void paintEvent(QPaintEvent *event);

signals:
    
public slots:
    void updateValueChange();
    void updateStatusChange();

private:
    void            setupUI();
    QHBoxLayout*    initAbstractValueLayout();
    QWidget*        initDetailValueWidget();

    QSize          m_size;

    QPushButton*   m_LittleVehicleName;
    QWidget*       m_detailValueWidget;

    //开关量
    QLabel*        m_ForwardName;
    QLabel*        m_ForwardStatus;
    QLabel*        m_BackwardName;
    QLabel*        m_BackwardStatus;
    QLabel*        m_BrakingName;
    QLabel*        m_BrakingStatus;
    QLabel*        m_BrakingNumber;//制动次数
    QLabel*        m_BrakingNumberUnit;//制动次数单位:次

    //开关量 限位状态
    SubLimitStatus*        m_LittleVehicleForwardLimit;//小车前限位 停止限位
    SubLimitStatus*        m_LittleVehicleBackwardLimit;//小车后限位 停止限位
    SubLimitStatus*        m_LittleVehicleForwardCutSpeedLimit;//小车前减速限位
    SubLimitStatus*        m_LittleVehicleBackwardCutSpeedLimit;//小车后减速限位
    SubLimitStatus*        m_LittleVehicleForwardOverLimit;//小车前极限限位  超限位
    SubLimitStatus*        m_LittleVehicleBackwardOverLimit;//小车后极限限位  超限位

    QLabel*        m_GearName;
    QLabel*        m_GearStatus;

    //数据量
    QLabel*        m_DistanceName;//行程
    QLabel*        m_DistanceValue;

    QLabel*        m_SpeedName;//速度
    QLabel*        m_SpeedValue;

    RoundWidget*   m_RoundwidgetDistance;//行程
    RoundWidget*   m_RoundwidgetSpeed;//速度

    LittleVehicleType            m_type;
};

#endif // LITTLEVEHICLEWIDGET_H
