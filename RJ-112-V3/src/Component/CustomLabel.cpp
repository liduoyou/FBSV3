#include "CustomLabel.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
CustomLabel::CustomLabel(QWidget *parent) :
    QLabel(parent)
  , m_size(120,20)
{
    setupUI();
}


CustomLabel::~CustomLabel()
{

}

void CustomLabel::setupUI()
{
    setFixedSize(m_size);
    setFocusPolicy(Qt::NoFocus);
    setAlignment(Qt::AlignCenter);
    setWordWrap(true);
}

void CustomLabel::setLabelName(QString name)
{
    m_labelName = name;
    update();
}

QString CustomLabel::getLabelName() const
{
    return m_labelName;
}

void CustomLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//启用反走样以得到平滑的边缘


    QFont font_size;
    font_size.setPixelSize(12);
    painter.setFont(font_size);

    painter.save();

    painter.setPen(QColor("#0f9d58"));
    painter.setBrush(QColor("transparent"));
    QPolygonF polygon;
    polygon << QPointF(3,height()/2)
            <<QPointF(18,0)
           <<QPointF(65,0)
          <<QPointF(65,height())
         <<QPointF(18,height());
    painter.drawPolygon(polygon, Qt::WindingFill);

    painter.drawText(QRectF(15,2,120,30),m_labelName);

    painter.setPen(QColor("#0f9d58"));
    painter.setBrush(QColor("#0f9d58"));
    painter.translate(height()/8, height()/8);
    QRectF rectangle2(8.0, 6.0, height()/5, height()/5);
    int startAngle1 = 0 * height()/5;
    int spanAngle1 = 3600 * height()/5;
    painter.drawArc(rectangle2, startAngle1, spanAngle1);

    painter.restore();

    //set Style...
    QStyleOption opt;
    opt.init(this);
    painter.setClipping(true);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}
