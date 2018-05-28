#include "LittleVehicleWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsDropShadowEffect>
#include "../Component/SubLimitStatus.h"
#include "../Component/RoundWidget.h"
#include "../DataHeaderDefine.h"
LittleVehicleWidget::LittleVehicleWidget(LittleVehicleType _type,QWidget *parent) :
    QWidget(parent)
  #ifdef MAXRESOLUTION
 , m_size(1012,675)
  #else
  , m_size(792,390)
  #endif
  , m_LittleVehicleName(NULL)
  , m_ForwardName(NULL)
  , m_ForwardStatus(NULL)
  , m_BackwardName(NULL)
  , m_BackwardStatus(NULL)
  , m_BrakingName(NULL)
  , m_BrakingStatus(NULL)
  , m_BrakingNumber(NULL)
  , m_BrakingNumberUnit(NULL)
  , m_LittleVehicleForwardLimit(NULL)
  , m_LittleVehicleBackwardLimit(NULL)
  , m_LittleVehicleForwardCutSpeedLimit(NULL)
  , m_LittleVehicleBackwardCutSpeedLimit(NULL)
  , m_LittleVehicleForwardOverLimit(NULL)
  , m_LittleVehicleBackwardOverLimit(NULL)
  , m_GearName(NULL)
  , m_GearStatus(NULL)
  , m_DistanceName(NULL)
  , m_DistanceValue(NULL)
  , m_SpeedName(NULL)
  , m_SpeedValue(NULL)
  , m_RoundwidgetDistance(NULL)
  , m_RoundwidgetSpeed(NULL)
  , m_type(_type)
{
    setupUI();
    setLittleVehicleName();
    updateValueChange();
}

LittleVehicleWidget::~LittleVehicleWidget()
{
}

void LittleVehicleWidget::setLittleVehicleName()
{
    switch ((LittleVehicleType)m_type) {
    case LVtype_UpVehicle:
        m_LittleVehicleName->setText(tr("上小车状态"));
        break;
    case LVtype_DownVehicle:
        m_LittleVehicleName->setText(tr("下小车状态"));
        break;
    case LVtype_FrontVehicle:
        m_LittleVehicleName->setText(tr("前天车状态"));
        break;
    case LVtype_BackVehicle:
        m_LittleVehicleName->setText(tr("后天车状态"));
        break;
    case LVtype_NO1Vehicle:
        m_LittleVehicleName->setText(tr("1#小车状态"));
        break;
    case LVtype_NO2Vehicle:
        m_LittleVehicleName->setText(tr("2#小车状态"));
        break;
    default:
        break;
    }
}

void LittleVehicleWidget::updateValueChange()
{
//    m_DistanceValue->setText(QString::number(getDistance(),10,2));
//    m_SpeedValue->setText(QString::number(getSpeed(),10,2));
    if(m_RoundwidgetDistance != NULL){
        m_RoundwidgetDistance->setValue(QString::number(getDistance(),10,2));
        m_RoundwidgetDistance->setSpecificAngle(getDistance(),getMinDistance(),getnearMinDistance(),
                                              getnearMaxDistance(),getMaxDistance());
    }
    if(m_RoundwidgetSpeed != NULL){
        m_RoundwidgetSpeed->setValue(QString::number(getSpeed(),10,2));
        m_RoundwidgetSpeed->setNormalAngle(getSpeed(),getnearMaxSpeed(),getMaxSpeed());
    }
    updateStatusChange();
}

void LittleVehicleWidget::updateStatusChange()
{
    if(getForward()){
        m_ForwardStatus->setStyleSheet("QLabel{border:0px;background-color:#0f9d58;}");
    }else{
        m_ForwardStatus->setStyleSheet("QLabel{border:0px;background-color:#ABABAB;}");
    }
    if(getBackward()){
        m_BackwardStatus->setStyleSheet("QLabel{border:0px;background-color:#0f9d58;}");
    }else{
        m_BackwardStatus->setStyleSheet("QLabel{border:0px;background-color:#ABABAB;}");
    }
    if(!getBraking()){
        m_BrakingStatus->setStyleSheet("QLabel{border:0px;background-color:#0f9d58;}");
    }else{
        m_BrakingStatus->setStyleSheet("QLabel{border:0px;background-color:#DB4437;}");
    }
    m_GearStatus->setText(QString::number(getGear()));

    if(m_BrakingNumber != NULL)
        m_BrakingNumber->setText(QString::number(getBrakingNumber()));

    if(m_LittleVehicleForwardLimit != NULL){
        m_LittleVehicleForwardLimit->setStatus(getLimitStatus() & 0x01);
    }
    if(m_LittleVehicleBackwardLimit != NULL){
        m_LittleVehicleBackwardLimit->setStatus(getLimitStatus() & 0x02);
    }
    if(m_LittleVehicleForwardCutSpeedLimit != NULL){
        m_LittleVehicleForwardCutSpeedLimit->setStatus(getLimitStatus() & 0x04);
    }
    if(m_LittleVehicleBackwardCutSpeedLimit != NULL){
        m_LittleVehicleBackwardCutSpeedLimit->setStatus(getLimitStatus() & 0x08);
    }
    if(m_LittleVehicleForwardOverLimit != NULL){
        m_LittleVehicleForwardOverLimit->setStatus(getLimitStatus() & 0x10);
    }
    if(m_LittleVehicleBackwardOverLimit != NULL){
        m_LittleVehicleBackwardOverLimit->setStatus(getLimitStatus() & 0x20);
    }
}

void LittleVehicleWidget::setupUI()
{
    setFixedSize(m_size);
    setObjectName("LittleVehicleWidget");
    setStyleSheet("#LittleVehicleWidget{background-color:transparent;}");

//    m_LittleVehicleName = new QPushButton(this);
//    m_LittleVehicleName->setFixedSize(100,30);
//    m_LittleVehicleName->setFlat(true);
//    m_LittleVehicleName->setFocusPolicy(Qt::NoFocus);
//    m_LittleVehicleName->setObjectName("m_LittleVehicleName");//border-radius:15px;
//    m_LittleVehicleName->setStyleSheet("#m_LittleVehicleName{border:0px;color:#FDFDFD;font-size:16px;background-color:#0f9d58;}");

    QHBoxLayout* HLayout = new QHBoxLayout();
    HLayout->setSizeConstraint(QLayout::SetMaximumSize);
    HLayout->setContentsMargins(0, 0, 0, 0);
    HLayout->setSpacing(5);

//    HLayout->addWidget(m_LittleVehicleName,1,Qt::AlignCenter);
//    HLayout->addLayout(initAbstractValueLayout());
    HLayout->addWidget(initDetailValueWidget(),1,Qt::AlignCenter);

    setLayout(HLayout);
}

QHBoxLayout *LittleVehicleWidget::initAbstractValueLayout()
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

    m_ForwardName = new QLabel();
    m_ForwardName->setAlignment(Qt::AlignCenter);
    m_ForwardName->setText(tr("前行"));
    m_ForwardName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout0->addWidget(m_ForwardName,1,Qt::AlignCenter);

    m_ForwardStatus = new QLabel();
    m_ForwardStatus->setFixedSize(20,20);
    m_ForwardStatus->setAlignment(Qt::AlignCenter);
    m_ForwardStatus->setStyleSheet("QLabel{border:0px;background-color:#848484;}");
    vLayout0->addWidget(m_ForwardStatus,1,Qt::AlignCenter);

    switchValue0->setLayout(vLayout0);

    QWidget* switchValue1 = new QWidget();
    switchValue1->setObjectName("switchValue1");
    switchValue1->setStyleSheet("#switchValue1{border:0px;}");
    switchValue1->setFixedSize(75,50);
    switchValue1->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout1 = new QVBoxLayout();
    vLayout1->setContentsMargins(0, 0, 0, 0);
    vLayout1->setSpacing(0);

    m_BackwardName = new QLabel();
    m_BackwardName->setAlignment(Qt::AlignCenter);
    m_BackwardName->setText(tr("后行"));
    m_BackwardName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout1->addWidget(m_BackwardName,1,Qt::AlignCenter);

    m_BackwardStatus = new QLabel();
    m_BackwardStatus->setFixedSize(20,20);
    m_BackwardStatus->setAlignment(Qt::AlignCenter);
    m_BackwardStatus->setStyleSheet("QLabel{border:0px;background-color:#848484;}");
    vLayout1->addWidget(m_BackwardStatus,1,Qt::AlignCenter);

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
    m_BrakingStatus->setStyleSheet("QLabel{border:0px;background-color:#848484;}");
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
    m_GearStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#848484;}");
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

    m_DistanceName = new QLabel();
    m_DistanceName->setAlignment(Qt::AlignCenter);
    m_DistanceName->setText(tr("行程"));
    m_DistanceName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout4->addWidget(m_DistanceName,1,Qt::AlignCenter);

    m_DistanceValue = new QLabel();
    m_DistanceValue->setFixedSize(75,20);
    m_DistanceValue->setAlignment(Qt::AlignCenter);
    m_DistanceValue->setText(tr("000.000"));
    m_DistanceValue->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#848484;}");
    vLayout4->addWidget(m_DistanceValue,1,Qt::AlignCenter);

    switchValue4->setLayout(vLayout4);

    QWidget* switchValue5 = new QWidget();
    switchValue5->setObjectName("switchValue5");
    switchValue5->setStyleSheet("#switchValue5{border:0px;}");
    switchValue5->setFixedSize(75,50);
    switchValue5->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout* vLayout5 = new QVBoxLayout();
    vLayout5->setContentsMargins(0, 0, 0, 0);
    vLayout5->setSpacing(0);

    m_SpeedName = new QLabel();
    m_SpeedName->setAlignment(Qt::AlignCenter);
    m_SpeedName->setText(tr("速度"));
    m_SpeedName->setStyleSheet("QLabel{border:0px;color:black;font-size:12px;background-color:transparent;}");
    vLayout5->addWidget(m_SpeedName,1,Qt::AlignCenter);

    m_SpeedValue = new QLabel();
    m_SpeedValue->setFixedSize(75,20);
    m_SpeedValue->setAlignment(Qt::AlignCenter);
    m_SpeedValue->setText(tr("000.000"));
    m_SpeedValue->setStyleSheet("QLabel{border:0px;color:black;font-size:15px;background-color:#848484;}");//
    vLayout5->addWidget(m_SpeedValue,1,Qt::AlignCenter);

    switchValue5->setLayout(vLayout5);

    m_SwitchValueLayout->addWidget(switchValue0);
    m_SwitchValueLayout->addWidget(switchValue1);
    m_SwitchValueLayout->addWidget(switchValue2);
    m_SwitchValueLayout->addWidget(switchValue3);
    m_SwitchValueLayout->addWidget(switchValue4);
    m_SwitchValueLayout->addWidget(switchValue5);

    return m_SwitchValueLayout;
}

QWidget *LittleVehicleWidget::initDetailValueWidget()
{
    m_detailValueWidget = new QWidget();
#ifdef MAXRESOLUTION
    m_detailValueWidget->setFixedSize(1012,675);
#else
    m_detailValueWidget->setFixedSize(792,390);
#endif
    m_detailValueWidget->setStyleSheet("QWidget{background-color:transparent;}");

    m_LittleVehicleName = new QPushButton(m_detailValueWidget);
    m_LittleVehicleName->setFixedSize(100,30);
    m_LittleVehicleName->setFlat(true);
    m_LittleVehicleName->setFocusPolicy(Qt::NoFocus);
    m_LittleVehicleName->setObjectName("m_LittleVehicleName");
    m_LittleVehicleName->setStyleSheet("#m_LittleVehicleName{border:0px;color:#FDFDFD;font-size:16px;background-color:#0f9d58;}");
    m_LittleVehicleName->move(35,15);

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(m_LittleVehicleName);
    shadow_effect->setOffset(4,4);
    shadow_effect->setColor(QColor("#787878"));
    shadow_effect->setBlurRadius(8);
    m_LittleVehicleName->setGraphicsEffect(shadow_effect);

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

    m_ForwardName = new QLabel();
    m_ForwardName->setAlignment(Qt::AlignCenter);
    m_ForwardName->setText(tr("前行"));
    m_ForwardName->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:transparent;}");

    m_ForwardStatus = new QLabel();
    m_ForwardStatus->setFixedSize(40,40);
    m_ForwardStatus->setAlignment(Qt::AlignCenter);
    m_ForwardStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:#ABABAB;}");

    vLayout0->addWidget(m_ForwardName,1,Qt::AlignCenter);
    vLayout0->addWidget(m_ForwardStatus,1,Qt::AlignCenter);

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

    m_BackwardName = new QLabel();
    m_BackwardName->setAlignment(Qt::AlignCenter);
    m_BackwardName->setText(tr("后行"));
    m_BackwardName->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:transparent;}");

    m_BackwardStatus = new QLabel();
    m_BackwardStatus->setFixedSize(40,40);
    m_BackwardStatus->setAlignment(Qt::AlignCenter);
    m_BackwardStatus->setStyleSheet("QLabel{border:0px;color:black;font-size:16px;background-color:#ABABAB;}");

    vLayout1->addWidget(m_BackwardName,1,Qt::AlignCenter);
    vLayout1->addWidget(m_BackwardStatus,1,Qt::AlignCenter);

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
    switchValue5->setFixedSize(410,220);
#else
    switchValue5->setFixedSize(410,120);
#endif
    switchValue5->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QHBoxLayout* hLayout5 = new QHBoxLayout();
    hLayout5->setContentsMargins(0, 0, 0, 0);
    hLayout5->setSpacing(15);

    QVBoxLayout* vvLayout1 = new QVBoxLayout();
    vvLayout1->setContentsMargins(0, 0, 0, 0);
    vvLayout1->setSpacing(0);

    QVBoxLayout* vvLayout2 = new QVBoxLayout();
    vvLayout2->setContentsMargins(0, 0, 0, 0);
    vvLayout2->setSpacing(0);

    m_LittleVehicleForwardLimit=new SubLimitStatus();//小车前限位
    m_LittleVehicleForwardLimit->setObjectName("LittleVehicleForwardLimit");
    m_LittleVehicleForwardLimit->mygetmember("limitname")->setText(tr("小车前限位"));
    m_LittleVehicleForwardLimit->setLimitProperty(true);

    m_LittleVehicleBackwardLimit=new SubLimitStatus();//小车后限位
    m_LittleVehicleBackwardLimit->setObjectName("LittleVehicleBackwardLimit");
    m_LittleVehicleBackwardLimit->mygetmember("limitname")->setText(tr("小车后限位"));
    m_LittleVehicleBackwardLimit->setLimitProperty(true);

    m_LittleVehicleForwardCutSpeedLimit=new SubLimitStatus();//小车前减速限位
    m_LittleVehicleForwardCutSpeedLimit->setObjectName("LittleVehicleForwardCutSpeedLimit");
    m_LittleVehicleForwardCutSpeedLimit->mygetmember("limitname")->setText(tr("小车前减速限位"));
    m_LittleVehicleForwardCutSpeedLimit->setLimitProperty(true);

    m_LittleVehicleBackwardCutSpeedLimit=new SubLimitStatus();//小车后减速限位
    m_LittleVehicleBackwardCutSpeedLimit->setObjectName("LittleVehicleBackwardCutSpeedLimit");
    m_LittleVehicleBackwardCutSpeedLimit->mygetmember("limitname")->setText(tr("小车后减速限位"));
    m_LittleVehicleBackwardCutSpeedLimit->setLimitProperty(true);

    m_LittleVehicleForwardOverLimit=new SubLimitStatus();//小车前极限限位
    m_LittleVehicleForwardOverLimit->setObjectName("LittleVehicleForwardOverLimit");
    m_LittleVehicleForwardOverLimit->mygetmember("limitname")->setText(tr("小车前极限限位"));
    m_LittleVehicleForwardOverLimit->setLimitProperty(true);

    m_LittleVehicleBackwardOverLimit=new SubLimitStatus();//小车后极限限位
    m_LittleVehicleBackwardOverLimit->setObjectName("LittleVehicleBackwardOverLimit");
    m_LittleVehicleBackwardOverLimit->mygetmember("limitname")->setText(tr("小车后极限限位"));
    m_LittleVehicleBackwardOverLimit->setLimitProperty(true);

    vvLayout1->addWidget(m_LittleVehicleForwardLimit);
    vvLayout2->addWidget(m_LittleVehicleBackwardLimit);
    vvLayout1->addWidget(m_LittleVehicleForwardCutSpeedLimit);
    vvLayout2->addWidget(m_LittleVehicleBackwardCutSpeedLimit);
    vvLayout1->addWidget(m_LittleVehicleForwardOverLimit);
    vvLayout2->addWidget(m_LittleVehicleBackwardOverLimit);

    hLayout5->addLayout(vvLayout1);
    hLayout5->addLayout(vvLayout2);

    switchValue5->setLayout(hLayout5);

#ifndef MAXRESOLUTION
    hLayout1->addSpacing(100);
#endif
    m_RoundwidgetDistance = new RoundWidget(tr("行程,M"));
    m_RoundwidgetSpeed = new RoundWidget(tr("速度,M/S"));
    hLayout1->addWidget(m_RoundwidgetDistance);
    hLayout1->addWidget(m_RoundwidgetSpeed);
#ifndef MAXRESOLUTION
    hLayout1->addSpacing(85);//100
#endif
    hLayout1->addWidget(switchValue0);
    hLayout1->addWidget(switchValue1);

    hLayout2->addStretch(1);
    hLayout2->addWidget(switchValue5);
    hLayout2->addStretch(1);
    hLayout2->addWidget(switchValue2);
    hLayout2->addWidget(switchValue3);
    hLayout2->addWidget(switchValue4);
    hLayout2->addStretch(1);

    VLayout->addLayout(hLayout1);
    VLayout->addLayout(hLayout2);

    m_detailValueWidget->setLayout(VLayout);

    return m_detailValueWidget;
}

void LittleVehicleWidget::paintEvent(QPaintEvent *event)
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
