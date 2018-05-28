#include "BigVehicleWidget.h"
#include <QEvent>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsDropShadowEffect>
#include "../Component/SubLimitStatus.h"
#include "../Component/RoundWidget.h"
#include "../DataHeaderDefine.h"
BigVehicleWidget::BigVehicleWidget(BigVehicleType _type, QWidget *parent) :
    QWidget(parent)
  #ifdef MAXRESOLUTION
 , m_size(1012,675)
  #else
  , m_size(792,390)
  #endif
  , m_BtnBigVehicleName(NULL)
  , m_LeftName(NULL)
  , m_LeftStatus(NULL)
  , m_RightName(NULL)
  , m_RightStatus(NULL)
  , m_BrakingName(NULL)
  , m_BrakingStatus(NULL)
  , m_BrakingNumber(NULL)
  , m_BrakingNumberUnit(NULL)
  , m_BigVehicleRightLimit(NULL)
  , m_BigVehicleLeftLimit(NULL)
  , m_BigVehicleRightCutSpeedLimit(NULL)
  , m_BigVehicleLeftCutSpeedLimit(NULL)
  , m_BigVehicleRightOverLimit(NULL)
  , m_BigVehicleLeftOverLimit(NULL)
  , m_LeftRollerStatus(NULL)
  , m_RightRollerStatus(NULL)
  , m_railclampSteellegStatus(NULL)
  , m_railclampSoftlegStatus(NULL)
  , m_DoorLimitStatus(NULL)
  , m_AnchorStatus(NULL)
  , m_RailDistanceStatus(NULL)
  , m_UrgencyStopStatus(NULL)
  , m_GearName(NULL)
  , m_GearStatus(NULL)
  , m_RoundwidgetSteellegDistance(NULL)
  , m_RoundwidgetSoftlegDistance(NULL)
  , m_RoundwidgetSpeed(NULL)
  , m_RoundwidgetWindSpeed(NULL)
  , m_RoundwidgetDeflection(NULL)
  , m_type(_type)
{
    setupUI();
    setBigVehicleName();
    updateValueChange();
}

BigVehicleWidget::~BigVehicleWidget()
{
}

void BigVehicleWidget::setBigVehicleName()
{
    switch ((BigVehicleType)m_type) {
    case BVtype_ALL:
        m_BtnBigVehicleName->setText(tr("大车状态"));
        break;
    case BVtype_NoSpeed:
        m_BtnBigVehicleName->setText(tr("大车状态"));
        break;
    case BVtype_OneDistance:
        m_BtnBigVehicleName->setText(tr("大车状态"));
        break;
    case BVtype_OnlyWind:
        m_RoundwidgetSteellegDistance->setVisible(false);
        m_RoundwidgetSoftlegDistance->setVisible(false);
        m_RoundwidgetDeflection->setVisible(false);
        m_BtnBigVehicleName->setText(tr("大车状态"));
        break;
    case BVtype_NO5:
        m_BtnBigVehicleName->setText(tr("整机状态"));
        break;
    case BVtype_NO6:
        m_BtnBigVehicleName->setText(tr("整机状态"));
        break;
    case BVtype_NO7:
        m_BtnBigVehicleName->setText(tr("整机状态"));
        break;
    case BVtype_NO8:
        m_BtnBigVehicleName->setText(tr("整机状态"));
        break;
    default:
        break;
    }
}

void BigVehicleWidget::updateValueChange()
{
//    m_SteellegDistanceValue->setText(QString::number(getSteellegDistance(),10,2));
//    m_SoftlegDistanceValue->setText(QString::number(getSoftlegDistance(),10,2));
//    m_SpeedValue->setText(QString::number(getSpeed(),10,2));
//    m_DeflectionValue->setText(QString::number(getDeflection(),10,2));
    if(m_RoundwidgetSteellegDistance != NULL){
        m_RoundwidgetSteellegDistance->setValue(QString::number(getSteelLegDistance(),10,2));
        m_RoundwidgetSteellegDistance->setSpecificAngle(getSteelLegDistance(),getMinSteelLegDistance(),getnearMinSteelLegDistance(),
                                                        getnearMaxSteelLegDistance(),getMaxSteelLegDistance());
    }
    if(m_RoundwidgetSoftlegDistance != NULL){
        m_RoundwidgetSoftlegDistance->setValue(QString::number(getSoftLegDistance(),10,2));
        m_RoundwidgetSoftlegDistance->setSpecificAngle(getSoftLegDistance(),getMinSoftLegDistance(),getnearMinSoftLegDistance(),
                                              getnearMaxSoftLegDistance(),getMaxSoftLegDistance());
    }
    if(m_RoundwidgetSpeed != NULL){
        m_RoundwidgetSpeed->setValue(QString::number(getSpeed(),10,2));
        m_RoundwidgetSpeed->setNormalAngle(getSpeed(),getnearMaxSpeed(),getMaxSpeed());
    }
    if(m_RoundwidgetWindSpeed != NULL){
        m_RoundwidgetWindSpeed->setValue(QString::number(getWindSpeed(),10,2));
        m_RoundwidgetWindSpeed->setNormalAngle(getWindSpeed(),getnearMaxWindSpeed(),getMaxWindSpeed());
    }
    if(m_RoundwidgetDeflection != NULL){
        m_RoundwidgetDeflection->setValue(QString::number(getDeflection(),10,2));
        m_RoundwidgetDeflection->setNormalAngle(getDeflection(),getnearMaxDeflection(),getMaxDeflection());
    }
    updateStatusChange();
}

void BigVehicleWidget::updateStatusChange()
{
    if(getLeft()){
        m_LeftStatus->setStyleSheet("QLabel{border:0px;background-color:#0f9d58;}");
    }else{
        m_LeftStatus->setStyleSheet("QLabel{border:0px;background-color:#ABABAB;}");
    }
    if(getRight()){
        m_RightStatus->setStyleSheet("QLabel{border:0px;background-color:#0f9d58;}");
    }else{
        m_RightStatus->setStyleSheet("QLabel{border:0px;background-color:#ABABAB;}");
    }
    if(!getBraking()){
        m_BrakingStatus->setStyleSheet("QLabel{border:0px;background-color:#0f9d58;}");
    }else{
        m_BrakingStatus->setStyleSheet("QLabel{border:0px;background-color:#DB4437;}");
    }
    m_GearStatus->setText(QString::number(getGear()));

    if(m_BrakingNumber != NULL)
        m_BrakingNumber->setText(QString::number(getBrakingNumber()));

    if(m_BigVehicleRightLimit != NULL){
        m_BigVehicleRightLimit->setStatus(getLimitStatus() & 0x01);
    }
    if(m_BigVehicleLeftLimit != NULL){
        m_BigVehicleLeftLimit->setStatus(getLimitStatus() & 0x02);
    }
    if(m_BigVehicleRightCutSpeedLimit != NULL){
        m_BigVehicleRightCutSpeedLimit->setStatus(getLimitStatus() & 0x04);
    }
    if(m_BigVehicleLeftCutSpeedLimit != NULL){
        m_BigVehicleLeftCutSpeedLimit->setStatus(getLimitStatus() & 0x08);
    }
    if(m_BigVehicleRightOverLimit != NULL){
        m_BigVehicleRightOverLimit->setStatus(getLimitStatus() & 0x10);
    }
    if(m_BigVehicleLeftOverLimit != NULL){
        m_BigVehicleLeftOverLimit->setStatus(getLimitStatus() & 0x20);
    }

    if(m_LeftRollerStatus != NULL){
        m_LeftRollerStatus->setStatus(getOtherStatus() & 0x01);
    }
    if(m_RightRollerStatus != NULL){
        m_RightRollerStatus->setStatus(getOtherStatus() & 0x02);
    }
    if(m_railclampSteellegStatus != NULL){
        m_railclampSteellegStatus->setStatus(getOtherStatus() & 0x04);
    }
    if(m_railclampSoftlegStatus != NULL){
        m_railclampSoftlegStatus->setStatus(getOtherStatus() & 0x08);
    }
    if(m_DoorLimitStatus != NULL){
        m_DoorLimitStatus->setStatus(getOtherStatus() & 0x10);
    }
    if(m_AnchorStatus != NULL){
        m_AnchorStatus->setStatus(getOtherStatus() & 0x20);
    }
    if(m_RailDistanceStatus != NULL){
        m_RailDistanceStatus->setStatus(getOtherStatus() & 0x40);
    }
    if(m_UrgencyStopStatus != NULL){
        m_UrgencyStopStatus->setStatus(getOtherStatus() & 0x80);
    }
}

bool BigVehicleWidget::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == m_BtnBigVehicleName){
        if(e->type() == QEvent::Enter){
            return true;
        }else if(e->type() == QEvent::Leave){
            return false;
        }
    }
    return QObject::eventFilter(obj, e);
}

void BigVehicleWidget::setupUI()
{
    setFixedSize(m_size);
    setObjectName("BigVehicleWidget");
    setStyleSheet("#BigVehicleWidget{background-color:transparent;}");

//    m_BtnBigVehicleName = new QPushButton(this);
//    m_BtnBigVehicleName->setFixedSize(100,30);
//    m_BtnBigVehicleName->setFlat(true);
//    m_BtnBigVehicleName->setFocusPolicy(Qt::NoFocus);
//    m_BtnBigVehicleName->setObjectName("m_BtnBigVehicleName");//border-radius:15px;
//    m_BtnBigVehicleName->setStyleSheet("#m_BtnBigVehicleName{border:0px;color:#FDFDFD;font-size:16px;background-color:#0f9d58;}");

    QHBoxLayout* HLayout = new QHBoxLayout();
    HLayout->setSizeConstraint(QLayout::SetMaximumSize);
    HLayout->setContentsMargins(0, 0, 0, 0);
    HLayout->setSpacing(5);

//    HLayout->addWidget(m_BtnBigVehicleName,1,Qt::AlignCenter);
//    HLayout->addLayout(initAbstractValueLayout());
    HLayout->addWidget(initDetailValueWidget(),1,Qt::AlignCenter);

    setLayout(HLayout);
}

QHBoxLayout *BigVehicleWidget::initAbstractValueLayout()
{
    QHBoxLayout* m_SwitchValueLayout = new QHBoxLayout();
    m_SwitchValueLayout->setSizeConstraint(QLayout::SetMaximumSize);
    m_SwitchValueLayout->setContentsMargins(5, 0, 0, 0);
    m_SwitchValueLayout->setSpacing(15);

    QWidget* switchValue0 = new QWidget();
    switchValue0->setObjectName("switchValue0");
    switchValue0->setStyleSheet("#switchValue0{border:0px;}");
    switchValue0->setFixedSize(75,50);
    switchValue0->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout0 = new QVBoxLayout();
    vLayout0->setContentsMargins(0, 0, 0, 0);
    vLayout0->setSpacing(0);

    m_LeftName = new QLabel();
    m_LeftName->setAlignment(Qt::AlignCenter);
    m_LeftName->setText(tr("左行"));
    m_LeftName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout0->addWidget(m_LeftName,1,Qt::AlignCenter);

    m_LeftStatus = new QLabel();
    m_LeftStatus->setFixedSize(20,20);
    m_LeftStatus->setAlignment(Qt::AlignCenter);
    m_LeftStatus->setStyleSheet("QLabel{border:0px;background-color:#ABABAB;}");
    vLayout0->addWidget(m_LeftStatus,1,Qt::AlignCenter);

    switchValue0->setLayout(vLayout0);

    QWidget* switchValue1 = new QWidget();
    switchValue1->setObjectName("switchValue1");
    switchValue1->setStyleSheet("#switchValue1{border:0px;}");
    switchValue1->setFixedSize(75,50);
    switchValue1->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout1 = new QVBoxLayout();
    vLayout1->setContentsMargins(0, 0, 0, 0);
    vLayout1->setSpacing(0);

    m_RightName = new QLabel();
    m_RightName->setAlignment(Qt::AlignCenter);
    m_RightName->setText(tr("右行"));
    m_RightName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout1->addWidget(m_RightName,1,Qt::AlignCenter);

    m_RightStatus = new QLabel();
    m_RightStatus->setFixedSize(20,20);
    m_RightStatus->setAlignment(Qt::AlignCenter);
    m_RightStatus->setStyleSheet("QLabel{border:0px;background-color:#ABABAB;}");
    vLayout1->addWidget(m_RightStatus,1,Qt::AlignCenter);

    switchValue1->setLayout(vLayout1);

    QWidget* switchValue2 = new QWidget();
    switchValue2->setObjectName("switchValue2");
    switchValue2->setStyleSheet("#switchValue2{border:0px;}");
    switchValue2->setFixedSize(75,50);
    switchValue2->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout2 = new QVBoxLayout();
    vLayout2->setContentsMargins(0, 0, 0, 0);
    vLayout2->setSpacing(0);

    m_BrakingName = new QLabel();
    m_BrakingName->setAlignment(Qt::AlignCenter);
    m_BrakingName->setText(tr("制动"));
    m_BrakingName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout2->addWidget(m_BrakingName,1,Qt::AlignCenter);

    m_BrakingStatus = new QLabel();
    m_BrakingStatus->setFixedSize(20,20);
    m_BrakingStatus->setAlignment(Qt::AlignCenter);
    m_BrakingStatus->setStyleSheet("QLabel{border:0px;background-color:#ABABAB;}");
    vLayout2->addWidget(m_BrakingStatus,1,Qt::AlignCenter);

    switchValue2->setLayout(vLayout2);

    QWidget* switchValue3 = new QWidget();
    switchValue3->setObjectName("switchValue3");
    switchValue3->setStyleSheet("#switchValue3{border:0px;}");
    switchValue3->setFixedSize(75,50);
    switchValue3->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout3 = new QVBoxLayout();
    vLayout3->setContentsMargins(0, 0, 0, 0);
    vLayout3->setSpacing(0);

    m_GearName = new QLabel();
    m_GearName->setAlignment(Qt::AlignCenter);
    m_GearName->setText(tr("档位"));
    m_GearName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout3->addWidget(m_GearName,1,Qt::AlignCenter);

    m_GearStatus = new QLabel();
    m_GearStatus->setFixedSize(20,20);
    m_GearStatus->setAlignment(Qt::AlignCenter);
    m_GearStatus->setText(tr("0"));
    m_GearStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#ABABAB;}");
    vLayout3->addWidget(m_GearStatus,1,Qt::AlignCenter);

    switchValue3->setLayout(vLayout3);

    QWidget* switchValue4 = new QWidget();
    switchValue4->setObjectName("switchValue4");
    switchValue4->setStyleSheet("#switchValue4{border:0px;}");
    switchValue4->setFixedSize(75,50);
    switchValue4->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout4 = new QVBoxLayout();
    vLayout4->setContentsMargins(0, 0, 0, 0);
    vLayout4->setSpacing(0);

    m_SteellegDistanceName = new QLabel();
    m_SteellegDistanceName->setAlignment(Qt::AlignCenter);
    m_SteellegDistanceName->setText(tr("钢腿行程"));
    m_SteellegDistanceName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout4->addWidget(m_SteellegDistanceName,1,Qt::AlignCenter);

    m_SteellegDistanceValue = new QLabel();
    m_SteellegDistanceValue->setFixedSize(75,20);
    m_SteellegDistanceValue->setAlignment(Qt::AlignCenter);
    m_SteellegDistanceValue->setText(tr("000.000"));
    m_SteellegDistanceValue->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#ABABAB;}");
    vLayout4->addWidget(m_SteellegDistanceValue,1,Qt::AlignCenter);

    switchValue4->setLayout(vLayout4);

    QWidget* switchValue5 = new QWidget();
    switchValue5->setObjectName("switchValue5");
    switchValue5->setStyleSheet("#switchValue5{border:0px;}");
    switchValue5->setFixedSize(75,50);
    switchValue5->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout5 = new QVBoxLayout();
    vLayout5->setContentsMargins(0, 0, 0, 0);
    vLayout5->setSpacing(0);

    m_SoftlegDistanceName = new QLabel();
    m_SoftlegDistanceName->setAlignment(Qt::AlignCenter);
    m_SoftlegDistanceName->setText(tr("柔腿行程"));
    m_SoftlegDistanceName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout5->addWidget(m_SoftlegDistanceName,1,Qt::AlignCenter);

    m_SoftlegDistanceValue = new QLabel();
    m_SoftlegDistanceValue->setFixedSize(75,20);
    m_SoftlegDistanceValue->setAlignment(Qt::AlignCenter);
    m_SoftlegDistanceValue->setText(tr("000.000"));
    m_SoftlegDistanceValue->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#ABABAB;}");
    vLayout5->addWidget(m_SoftlegDistanceValue,1,Qt::AlignCenter);

    switchValue5->setLayout(vLayout5);

    QWidget* switchValue6 = new QWidget();
    switchValue6->setObjectName("switchValue6");
    switchValue6->setStyleSheet("#switchValue6{border:0px;}");
    switchValue6->setFixedSize(75,50);
    switchValue6->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout6 = new QVBoxLayout();
    vLayout6->setContentsMargins(0, 0, 0, 0);
    vLayout6->setSpacing(0);

    m_SpeedName = new QLabel();
    m_SpeedName->setAlignment(Qt::AlignCenter);
    m_SpeedName->setText(tr("风速"));
    m_SpeedName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout6->addWidget(m_SpeedName,1,Qt::AlignCenter);

    m_SpeedValue = new QLabel();
    m_SpeedValue->setFixedSize(75,20);
    m_SpeedValue->setAlignment(Qt::AlignCenter);
    m_SpeedValue->setText(tr("000.000"));
    m_SpeedValue->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#ABABAB;}");
    vLayout6->addWidget(m_SpeedValue,1,Qt::AlignCenter);

    switchValue6->setLayout(vLayout6);

    QWidget* switchValue7 = new QWidget();
    switchValue7->setObjectName("switchValue7");
    switchValue7->setStyleSheet("#switchValue7{border:0px;}");
    switchValue7->setFixedSize(75,50);
    switchValue7->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout7 = new QVBoxLayout();
    vLayout7->setContentsMargins(0, 0, 0, 0);
    vLayout7->setSpacing(0);

    m_DeflectionName = new QLabel();
    m_DeflectionName->setAlignment(Qt::AlignCenter);
    m_DeflectionName->setText(tr("偏斜"));
    m_DeflectionName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout7->addWidget(m_DeflectionName,1,Qt::AlignCenter);

    m_DeflectionValue = new QLabel();
    m_DeflectionValue->setFixedSize(75,20);
    m_DeflectionValue->setAlignment(Qt::AlignCenter);
    m_DeflectionValue->setText(tr("000.000"));
    m_DeflectionValue->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#ABABAB;}");
    vLayout7->addWidget(m_DeflectionValue,1,Qt::AlignCenter);

    switchValue7->setLayout(vLayout7);

    m_SwitchValueLayout->addWidget(switchValue0);
    m_SwitchValueLayout->addWidget(switchValue1);
    m_SwitchValueLayout->addWidget(switchValue2);
    m_SwitchValueLayout->addWidget(switchValue3);
    m_SwitchValueLayout->addWidget(switchValue4);
    m_SwitchValueLayout->addWidget(switchValue5);
    m_SwitchValueLayout->addWidget(switchValue6);
    m_SwitchValueLayout->addWidget(switchValue7);

    return m_SwitchValueLayout;
}

QWidget *BigVehicleWidget::initDetailValueWidget()
{
    m_detailValueWidget = new QWidget();
#ifdef MAXRESOLUTION
    m_detailValueWidget->setFixedSize(1012,675);
#else
    m_detailValueWidget->setFixedSize(792,390);
#endif
    m_detailValueWidget->setStyleSheet("QWidget{background-color:transparent;}");

    m_BtnBigVehicleName = new QPushButton(m_detailValueWidget);
    m_BtnBigVehicleName->setFixedSize(100,30);
    m_BtnBigVehicleName->setFlat(true);
    m_BtnBigVehicleName->setFocusPolicy(Qt::NoFocus);
    m_BtnBigVehicleName->setObjectName("m_BtnBigVehicleName");
    m_BtnBigVehicleName->setStyleSheet("#m_BtnBigVehicleName{border:0px;color:#FDFDFD;font-size:16px;background-color:#0f9d58;}");
    m_BtnBigVehicleName->move(35,15);

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(m_BtnBigVehicleName);
    shadow_effect->setOffset(4,4);
    shadow_effect->setColor(QColor("#787878"));
    shadow_effect->setBlurRadius(8);
    m_BtnBigVehicleName->setGraphicsEffect(shadow_effect);

    QVBoxLayout* VLayout = new QVBoxLayout();
    VLayout->setSizeConstraint(QLayout::SetMaximumSize);
    VLayout->setContentsMargins(0, 0, 0, 0);
    VLayout->setSpacing(0);

    QHBoxLayout* hLayout1 = new QHBoxLayout();
    hLayout1->setContentsMargins(0, 0, 0, 0);
    hLayout1->setSpacing(0);

    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout2->setContentsMargins(0, 0, 0, 0);
    hLayout2->setSpacing(0);

    QWidget* switchValue0 = new QWidget();
    switchValue0->setObjectName("switchValue0");
    switchValue0->setStyleSheet("#switchValue0{border:0px;}");
#ifdef MAXRESOLUTION
    switchValue0->setFixedSize(75,220);
#else
    switchValue0->setFixedSize(75,120);
#endif
    switchValue0->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout0 = new QVBoxLayout();
    vLayout0->setContentsMargins(0, 0, 0, 0);
    vLayout0->setSpacing(0);

    m_LeftName = new QLabel();
    m_LeftName->setAlignment(Qt::AlignCenter);
    m_LeftName->setText(tr("左行"));
    m_LeftName->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:transparent;}");

    m_LeftStatus = new QLabel();
    m_LeftStatus->setFixedSize(40,40);
    m_LeftStatus->setAlignment(Qt::AlignCenter);
    m_LeftStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:#ABABAB;}");

    vLayout0->addWidget(m_LeftName,1,Qt::AlignCenter);
    vLayout0->addWidget(m_LeftStatus,1,Qt::AlignCenter);

    switchValue0->setLayout(vLayout0);

    QWidget* switchValue1 = new QWidget();
    switchValue1->setObjectName("switchValue1");
    switchValue1->setStyleSheet("#switchValue1{border:0px;}");
#ifdef MAXRESOLUTION
    switchValue1->setFixedSize(75,220);
#else
    switchValue1->setFixedSize(75,120);
#endif
    switchValue1->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout1 = new QVBoxLayout();
    vLayout1->setContentsMargins(0, 0, 0, 0);
    vLayout1->setSpacing(0);

    m_RightName = new QLabel();
    m_RightName->setAlignment(Qt::AlignCenter);
    m_RightName->setText(tr("右行"));
    m_RightName->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:transparent;}");

    m_RightStatus = new QLabel();
    m_RightStatus->setFixedSize(40,40);
    m_RightStatus->setAlignment(Qt::AlignCenter);
    m_RightStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:#ABABAB;}");

    vLayout1->addWidget(m_RightName,1,Qt::AlignCenter);
    vLayout1->addWidget(m_RightStatus,1,Qt::AlignCenter);

    switchValue1->setLayout(vLayout1);

    QWidget* switchValue2 = new QWidget();
    switchValue2->setObjectName("switchValue2");
    switchValue2->setStyleSheet("#switchValue2{border:0px;}");
#ifdef MAXRESOLUTION
    switchValue2->setFixedSize(75,220);
#else
    switchValue2->setFixedSize(75,120);
#endif
    switchValue2->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout2 = new QVBoxLayout();
    vLayout2->setContentsMargins(0, 0, 0, 0);
    vLayout2->setSpacing(0);

    m_GearName = new QLabel();
    m_GearName->setAlignment(Qt::AlignCenter);
    m_GearName->setText(tr("档位"));
    m_GearName->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:transparent;}");

    m_GearStatus = new QLabel();
    m_GearStatus->setFixedSize(40,40);
    m_GearStatus->setAlignment(Qt::AlignCenter);
    m_GearStatus->setText(tr("0"));
    m_GearStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:25px;background-color:#ABABAB;}");
    vLayout2->addWidget(m_GearName,1,Qt::AlignCenter);
    vLayout2->addWidget(m_GearStatus,1,Qt::AlignCenter);

    switchValue2->setLayout(vLayout2);

    QWidget* switchValue3 = new QWidget();
    switchValue3->setObjectName("switchValue3");
    switchValue3->setStyleSheet("#switchValue3{border:0px;}");
#ifdef MAXRESOLUTION
    switchValue3->setFixedSize(75,220);
#else
    switchValue3->setFixedSize(75,120);
#endif
    switchValue3->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout3 = new QVBoxLayout();
    vLayout3->setContentsMargins(0, 0, 0, 0);
    vLayout3->setSpacing(0);

    m_BrakingName = new QLabel();
    m_BrakingName->setAlignment(Qt::AlignCenter);
    m_BrakingName->setText(tr("制动"));
    m_BrakingName->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:transparent;}");

    m_BrakingStatus = new QLabel();
    m_BrakingStatus->setFixedSize(40,40);
    m_BrakingStatus->setAlignment(Qt::AlignCenter);
    m_BrakingStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:#DB4437;}");
    vLayout3->addWidget(m_BrakingName,1,Qt::AlignCenter);
    vLayout3->addWidget(m_BrakingStatus,1,Qt::AlignCenter);

    switchValue3->setLayout(vLayout3);

    QWidget* switchValue4 = new QWidget();
    switchValue4->setObjectName("switchValue4");
    switchValue4->setStyleSheet("#switchValue4{border:0px;}");
#ifdef MAXRESOLUTION
    switchValue4->setFixedSize(90,150);
#else
    switchValue4->setFixedSize(90,100);
#endif
    switchValue4->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QHBoxLayout* hLayout4 = new QHBoxLayout();
    hLayout4->setContentsMargins(0, 0, 0, 0);
    hLayout4->setSpacing(5);

    m_BrakingNumber = new QLabel();
    m_BrakingNumber->setAlignment(Qt::AlignCenter);
    m_BrakingNumber->setFixedSize(75,25);
    m_BrakingNumber->setText(tr("0"));
    m_BrakingNumber->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:#ABABAB;}");

    m_BrakingNumberUnit = new QLabel();
    m_BrakingNumberUnit->setAlignment(Qt::AlignCenter);
    m_BrakingNumberUnit->setText(tr("次"));
    m_BrakingNumberUnit->setStyleSheet("QLabel{border:0px;color:black;font-size:14px;background-color:transparent;}");
    hLayout4->addWidget(m_BrakingNumber,1,Qt::AlignBottom|Qt::AlignRight);
    hLayout4->addWidget(m_BrakingNumberUnit,1,Qt::AlignBottom|Qt::AlignRight);

    switchValue4->setLayout(hLayout4);

    QWidget* switchValue5 = new QWidget();
    switchValue5->setObjectName("switchValue5");
    switchValue5->setStyleSheet("#switchValue5{border:0px;}");
#ifdef MAXRESOLUTION
    switchValue5->setFixedSize(550,220);
#else
    switchValue5->setFixedSize(550,120);
#endif
    switchValue5->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QHBoxLayout* hLayout5 = new QHBoxLayout();
    hLayout5->setContentsMargins(0, 0, 0, 0);
    hLayout5->setSpacing(0);

    QVBoxLayout* vvLayout1 = new QVBoxLayout();
    vvLayout1->setContentsMargins(0, 0, 0, 0);
    vvLayout1->setSpacing(0);

    QVBoxLayout* vvLayout2 = new QVBoxLayout();
    vvLayout2->setContentsMargins(0, 0, 0, 0);
    vvLayout2->setSpacing(0);

    QVBoxLayout* vvLayout3 = new QVBoxLayout();
    vvLayout3->setContentsMargins(0, 0, 0, 0);
    vvLayout3->setSpacing(0);

    m_BigVehicleRightLimit=new SubLimitStatus();//大车右限位
    m_BigVehicleRightLimit->setObjectName("BigVehicleRightLimit");
    m_BigVehicleRightLimit->mygetmember("limitname")->setText(tr("大车右限位"));
    m_BigVehicleRightLimit->setLimitProperty(true);

    m_BigVehicleLeftLimit=new SubLimitStatus();//大车左限位
    m_BigVehicleLeftLimit->setObjectName("BigVehicleLeftLimit");
    m_BigVehicleLeftLimit->mygetmember("limitname")->setText(tr("大车左限位"));
    m_BigVehicleLeftLimit->setLimitProperty(true);

    m_BigVehicleRightCutSpeedLimit=new SubLimitStatus();//大车右减速限位
    m_BigVehicleRightCutSpeedLimit->setObjectName("BigVehicleRightCutSpeedLimit");
    m_BigVehicleRightCutSpeedLimit->mygetmember("limitname")->setText(tr("大车右减速限位"));
    m_BigVehicleRightCutSpeedLimit->setLimitProperty(true);

    m_BigVehicleLeftCutSpeedLimit=new SubLimitStatus();//大车左减速限位
    m_BigVehicleLeftCutSpeedLimit->setObjectName("BigVehicleLeftCutSpeedLimit");
    m_BigVehicleLeftCutSpeedLimit->mygetmember("limitname")->setText(tr("大车左减速限位"));
    m_BigVehicleLeftCutSpeedLimit->setLimitProperty(true);

    m_BigVehicleRightOverLimit=new SubLimitStatus();//大车右极限限位
    m_BigVehicleRightOverLimit->setObjectName("BigVehicleRightOverLimit");
    m_BigVehicleRightOverLimit->mygetmember("limitname")->setText(tr("大车右极限限位"));
    m_BigVehicleRightOverLimit->setLimitProperty(true);

    m_BigVehicleLeftOverLimit=new SubLimitStatus();//大车左极限限位
    m_BigVehicleLeftOverLimit->setObjectName("BigVehicleLeftOverLimit");
    m_BigVehicleLeftOverLimit->mygetmember("limitname")->setText(tr("大车左极限限位"));
    m_BigVehicleLeftOverLimit->setLimitProperty(true);


    m_LeftRollerStatus=new SubLimitStatus();//左电缆卷筒状态:正常(绿色) 异常(红色)
    m_LeftRollerStatus->setObjectName("BigVehicleLeftRollerStatus");
    m_LeftRollerStatus->mygetmember("limitname")->setText(tr("左电缆卷筒状态"));
    m_LeftRollerStatus->setLimitProperty(true);
    m_RightRollerStatus=new SubLimitStatus();//右电缆卷筒状态:正常(绿色) 异常(红色)
    m_RightRollerStatus->setObjectName("BigVehicleRightRollerStatus");
    m_RightRollerStatus->mygetmember("limitname")->setText(tr("右电缆卷筒状态"));
    m_RightRollerStatus->setLimitProperty(true);

    m_railclampSteellegStatus=new SubLimitStatus();//钢腿夹轨器状态:正常(绿色) 异常(红色)
    m_railclampSteellegStatus->setObjectName("BigVehiclerailclampSteellegStatus");
    m_railclampSteellegStatus->mygetmember("limitname")->setText(tr("钢腿夹轨器状态"));
    m_railclampSteellegStatus->setLimitProperty(true);
    m_railclampSoftlegStatus=new SubLimitStatus();//柔腿夹轨器状态:正常(绿色) 异常(红色)
    m_railclampSoftlegStatus->setObjectName("BigVehiclerailclampSoftlegStatus");
    m_railclampSoftlegStatus->mygetmember("limitname")->setText(tr("柔腿夹轨器状态"));
    m_railclampSoftlegStatus->setLimitProperty(true);

    m_DoorLimitStatus=new SubLimitStatus();//门限位状态:正常(绿色) 异常(红色)
    m_DoorLimitStatus->setObjectName("BigVehicleDoorLimitStatus");
    m_DoorLimitStatus->mygetmember("limitname")->setText(tr("门限位状态"));
    m_DoorLimitStatus->setLimitProperty(true);
    m_AnchorStatus=new SubLimitStatus();//锚定状态:正常(绿色) 异常(红色)
    m_AnchorStatus->setObjectName("BigVehicleAnchorStatus");
    m_AnchorStatus->mygetmember("limitname")->setText(tr("锚定状态"));
    m_AnchorStatus->setLimitProperty(true);
    m_RailDistanceStatus=new SubLimitStatus();//轨距状态:正常(绿色) 异常(红色)
    m_RailDistanceStatus->setObjectName("BigVehicleRailDistanceStatus");
    m_RailDistanceStatus->mygetmember("limitname")->setText(tr("轨距状态"));
    m_RailDistanceStatus->setLimitProperty(true);
    m_UrgencyStopStatus=new SubLimitStatus();//整车急停状态:正常(绿色) 异常(红色)
    m_UrgencyStopStatus->setObjectName("BigVehicleUrgencyStopStatus");
    m_UrgencyStopStatus->mygetmember("limitname")->setText(tr("急停状态"));
    m_UrgencyStopStatus->setLimitProperty(true);

    vvLayout1->addWidget(m_BigVehicleRightLimit);
    vvLayout2->addWidget(m_BigVehicleLeftLimit);
    vvLayout1->addWidget(m_BigVehicleRightCutSpeedLimit);
    vvLayout2->addWidget(m_BigVehicleLeftCutSpeedLimit);
    vvLayout1->addWidget(m_BigVehicleRightOverLimit);
    vvLayout2->addWidget(m_BigVehicleLeftOverLimit);
    vvLayout1->addWidget(m_LeftRollerStatus);
    vvLayout2->addWidget(m_railclampSteellegStatus);
    vvLayout1->addWidget(m_RightRollerStatus);
    vvLayout2->addWidget(m_railclampSoftlegStatus);

    vvLayout3->addWidget(m_UrgencyStopStatus);
    vvLayout3->addWidget(m_AnchorStatus);
    vvLayout3->addWidget(m_RailDistanceStatus);
    vvLayout3->addWidget(m_DoorLimitStatus);

    hLayout5->addLayout(vvLayout1);
    hLayout5->addLayout(vvLayout2);
    hLayout5->addLayout(vvLayout3);

    switchValue5->setLayout(hLayout5);

//#ifndef MAXRESOLUTION
//    hLayout1->addSpacing(100);
//#endif
    m_RoundwidgetSteellegDistance = new RoundWidget(tr("钢腿行程,M"));
    m_RoundwidgetSoftlegDistance = new RoundWidget(tr("柔腿行程,M"));
//    m_RoundwidgetSpeed = new RoundWidget(tr("速度,M/S"));
    m_RoundwidgetWindSpeed = new RoundWidget(tr("风速,M/S"));
    m_RoundwidgetDeflection = new RoundWidget(tr("偏斜值,MM"));
    hLayout1->addWidget(m_RoundwidgetSteellegDistance);
    hLayout1->addWidget(m_RoundwidgetSoftlegDistance);
//    hLayout1->addWidget(m_RoundwidgetSpeed);
    hLayout1->addWidget(m_RoundwidgetWindSpeed);
    connect(m_RoundwidgetWindSpeed,SIGNAL(circleClicked(bool)),this,SLOT(switchWindSpeed(bool)));
    hLayout1->addWidget(m_RoundwidgetDeflection);
//#ifndef MAXRESOLUTION
//    hLayout1->addSpacing(85);//100
//#endif
    hLayout1->addWidget(switchValue1);
    hLayout1->addWidget(switchValue0);

//    hLayout2->addStretch(1);
    hLayout2->addWidget(switchValue5);
    hLayout2->addStretch(1);
    hLayout2->addWidget(switchValue2);
    hLayout2->addWidget(switchValue3);
    hLayout2->addWidget(switchValue4);
//    hLayout2->addStretch(1);

    VLayout->addLayout(hLayout1);
    VLayout->addLayout(hLayout2);

    m_detailValueWidget->setLayout(VLayout);

    return m_detailValueWidget;
}

void BigVehicleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QColor("#FDFDFD"));
    painter.setBrush(QColor("#FDFDFD"));

    painter.save();

    QRect bgRect;
    bgRect.setWidth(width());
    bgRect.setHeight(height());
    painter.drawRect(bgRect);

    painter.restore();
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&painter,this);

    QWidget::paintEvent(event);
}

void BigVehicleWidget::switchWindSpeed(bool flag)
{
    if(flag){
        m_RoundwidgetWindSpeed->setValue(QString::number(getWindspeedJIBIE(),10,2));
        m_RoundwidgetWindSpeed->setNormalAngle(getWindspeedJIBIE(),getnearMaxWindSpeedJIBIE(),getMaxWindSpeedJIBIE());
    }else{
        m_RoundwidgetWindSpeed->setValue(QString::number(getWindSpeed(),10,2));
        m_RoundwidgetWindSpeed->setNormalAngle(getWindSpeed(),getnearMaxWindSpeed(),getMaxWindSpeed());
    }
}
