#ifndef BIGVEHICLEWIDGET_H
#define BIGVEHICLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include "../BaseClass/BigVehicle.h"
class SubLimitStatus;
class RoundWidget;
class BigVehicleWidget : public QWidget,public BigVehicle
{
    Q_OBJECT
public:
    explicit BigVehicleWidget(BigVehicleType _type,QWidget *parent = 0);
    ~BigVehicleWidget();

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *obj, QEvent *e);
signals:
    
public slots:
    void switchWindSpeed(bool flag);
    void updateValueChange();
    void updateStatusChange();

private:
    void              setupUI();
    void setBigVehicleName();
    QHBoxLayout*      initAbstractValueLayout();
    QWidget*          initDetailValueWidget();

    QSize             m_size;

    QPushButton*   m_BtnBigVehicleName;
    QWidget*       m_detailValueWidget;

    //开关量
    QLabel*        m_LeftName;
    QLabel*        m_LeftStatus;
    QLabel*        m_RightName;
    QLabel*        m_RightStatus;
    QLabel*        m_BrakingName;
    QLabel*        m_BrakingStatus;
    QLabel*        m_BrakingNumber;//制动次数
    QLabel*        m_BrakingNumberUnit;//制动次数单位:次

    //开关量 限位状态
    SubLimitStatus*        m_BigVehicleRightLimit;//大车右限位 停止限位
    SubLimitStatus*        m_BigVehicleLeftLimit;//大车左限位 停止限位
    SubLimitStatus*        m_BigVehicleRightCutSpeedLimit;//大车右减速限位
    SubLimitStatus*        m_BigVehicleLeftCutSpeedLimit;//大车左减速限位
    SubLimitStatus*        m_BigVehicleRightOverLimit;//大车右极限限位  超限位
    SubLimitStatus*        m_BigVehicleLeftOverLimit;//大车左极限限位  超限位

    SubLimitStatus*        m_LeftRollerStatus;//左电缆卷筒状态:正常(绿色) 异常(红色)
    SubLimitStatus*        m_RightRollerStatus;//右电缆卷筒状态:正常(绿色) 异常(红色)
    SubLimitStatus*        m_railclampSteellegStatus;//钢腿夹轨器状态:正常(绿色) 异常(红色)
    SubLimitStatus*        m_railclampSoftlegStatus;//柔腿夹轨器状态:正常(绿色) 异常(红色)
    SubLimitStatus*        m_DoorLimitStatus;//起重机门限位状态:正常(绿色) 异常(红色)
    SubLimitStatus*        m_AnchorStatus;//锚定状态:正常(绿色) 异常(红色)
    SubLimitStatus*        m_RailDistanceStatus;//轨道距离状态:正常(绿色) 异常(红色)
    SubLimitStatus*        m_UrgencyStopStatus;//整车急停状态:正常(绿色) 异常(红色)

    QLabel*        m_GearName;
    QLabel*        m_GearStatus;

    //数据量
    QLabel*        m_SteellegDistanceName;//钢腿行程
    QLabel*        m_SteellegDistanceValue;//

    QLabel*        m_SoftlegDistanceName;//柔腿行程
    QLabel*        m_SoftlegDistanceValue;

    QLabel*        m_SpeedName;//速度
    QLabel*        m_SpeedValue;

    QLabel*        m_WindSpeedName;//风速
    QLabel*        m_WindSpeedValue;

    QLabel*        m_DeflectionName;//偏斜值
    QLabel*        m_DeflectionValue;

    RoundWidget*   m_RoundwidgetSteellegDistance;//钢腿行程
    RoundWidget*   m_RoundwidgetSoftlegDistance;//柔腿行程
    RoundWidget*   m_RoundwidgetSpeed;//速度
    RoundWidget*   m_RoundwidgetWindSpeed;//风速
    RoundWidget*   m_RoundwidgetDeflection;//偏斜值

    BigVehicleType            m_type;
};

#endif // BIGVEHICLEWIDGET_H
