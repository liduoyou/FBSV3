#include "AbstractWidget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include "../DataHeaderDefine.h"
#include "../BaseWidgets/BigVehicleWidget.h"
#include "../BaseWidgets/HookWidget.h"
#include "../BaseWidgets/LittleVehicleWidget.h"
AbstractWidget::AbstractWidget(QWidget *parent) :
    QWidget(parent)
  , m_size(800,45*8)
  , m_bigVehicleWidget(NULL)
  , m_HookNo1Widget(NULL)
  , m_HookNo2Widget(NULL)
  , m_HookNo3Widget(NULL)
  , m_HookNo4Widget(NULL)
  , m_littleVehicleNo1Widget(NULL)
  , m_littleVehicleNo2Widget(NULL)
  , m_timer(NULL)
  , nameEdit(NULL)
  , nameLabel(NULL)
  , phoneEdit(NULL)
  , phoneLabel(NULL)
{
    setupUI();

    m_timer = new QTimer();
    connect(m_timer , SIGNAL(timeout()), this , SLOT(updateData()));
//    m_timer->start(300);

    updateData();
}

AbstractWidget::~AbstractWidget()
{
    qDebug()<<"AbstractWidget::~AbstractWidget()";
}

void AbstractWidget::setupUI()
{
    setFixedSize(m_size);
    setStyleSheet("QWidget{border:0px;background-color:transparent;}");

    QVBoxLayout* VLayout = new QVBoxLayout();
    VLayout->setContentsMargins(0, 0, 0, 0);
    VLayout->setSpacing(2);

    m_bigVehicleWidget = new BigVehicleWidget(BigVehicle::BVtype_NoSpeed);

    m_HookNo1Widget = new HookWidget(HookWidget::Htype_NO1);
    m_HookNo2Widget = new HookWidget(HookWidget::Htype_NO2);
    m_HookNo3Widget = new HookWidget(HookWidget::Htype_NO3);
    m_HookNo4Widget = new HookWidget(HookWidget::Htype_NO4);

    m_littleVehicleNo1Widget = new LittleVehicleWidget(LittleVehicleWidget::LVtype_UpVehicle);
    m_littleVehicleNo2Widget = new LittleVehicleWidget(LittleVehicleWidget::LVtype_DownVehicle);

    VLayout->addWidget(m_HookNo1Widget,1,Qt::AlignCenter);
    VLayout->addWidget(m_HookNo2Widget,1,Qt::AlignCenter);
    VLayout->addWidget(m_HookNo3Widget,1,Qt::AlignCenter);
    VLayout->addWidget(m_HookNo4Widget,1,Qt::AlignCenter);

    VLayout->addWidget(m_littleVehicleNo1Widget,1,Qt::AlignCenter);
    VLayout->addWidget(m_littleVehicleNo2Widget,1,Qt::AlignCenter);
    VLayout->addWidget(m_bigVehicleWidget,1,Qt::AlignCenter);

    setLayout(VLayout);
}

void AbstractWidget::updateData()
{
    m_bigVehicleWidget->updateValueChange();

    m_HookNo1Widget->updateValueChange();
    m_HookNo2Widget->updateValueChange();
    m_HookNo3Widget->updateValueChange();
    m_HookNo4Widget->updateValueChange();

    m_littleVehicleNo1Widget->updateValueChange();
    m_littleVehicleNo2Widget->updateValueChange();
}
