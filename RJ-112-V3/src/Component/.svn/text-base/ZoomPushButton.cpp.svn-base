#include "ZoomPushButton.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include "CustomLabel.h"
ZoomPushButton::ZoomPushButton(QWidget *parent) :
    QPushButton(parent)
  , m_size(160,40)
  , m_enter(false)
{
    setupUI();
}


ZoomPushButton::~ZoomPushButton()
{
}


void ZoomPushButton::setupUI()
{
    setFixedSize(m_size);
    setFocusPolicy(Qt::NoFocus);
    setCheckable(true);
    setChecked(false);

    m_label = new CustomLabel(this);
    m_label->setVisible(false);
    m_label->move(20,0);
}


void ZoomPushButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//启用反走样以得到平滑的边缘

    painter.save();

    if(m_enter){
        m_label->setVisible(true);
        painter.setPen(QColor("#0f9d58"));
        painter.setBrush(QColor("#0f9d58"));
        painter.translate(height()/8, height()/8);
        QRectF rectangle1(0.0, 0.0, height()/5, height()/5);
        painter.drawEllipse(rectangle1);

        painter.setPen(QColor("#0f9d58"));
        painter.setBrush(QColor("#0f9d58"));
        painter.translate(height()/8, height()/8);
        QRectF rectangle2(-9.0, -9.0, height()/2.5, height()/2.5);
        int startAngle1 = 0 * height()/3;
        int spanAngle1 = 425 * height()/3;
        painter.drawArc(rectangle2, startAngle1, spanAngle1);

    }else{
        m_label->setVisible(false);
        painter.setPen(QColor("#848484"));
        painter.setBrush(QColor("#848484"));
        painter.translate(height()/8, height()/8);
        QRectF rectangle1(0.0, 0.0, height()/4, height()/4);
        painter.drawEllipse(rectangle1);
    }

    painter.restore();

    //set Style...
    QStyleOption opt;
    opt.init(this);
    painter.setClipping(true);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}


void ZoomPushButton::leaveEvent(QEvent *event)
{
//    if(isChecked()){
//        m_enter = true;
//    }else{
        m_enter = false;
//    }
}


void ZoomPushButton::enterEvent(QEvent *event)
{
    m_enter = true;
}

void ZoomPushButton::setLabelName(QString name)
{
    m_labelName = name;
    m_label->setLabelName(m_labelName);
}

QString ZoomPushButton::getLabelName() const
{
    return m_labelName;
}
