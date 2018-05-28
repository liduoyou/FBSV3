#include "NScrollBar.h"
#include <QPaintEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QStyleOption>
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>

NScrollBar::NScrollBar(QWidget *parent) :
    QScrollBar(parent)
  , _handle(NULL)
  , _valueAnimation(NULL)
  , _minimum(0)
  , _maximum(0)
  , _value(0)
  , _handle_x(0)
{
    _valueAnimation = new QPropertyAnimation(this, "value");
    _valueAnimation->setEasingCurve(QEasingCurve::OutQuad);

    initUI();
    connect(this, SIGNAL(rangeChanged(int,int)), this, SLOT(setNRange(int,int)));
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(setNValue(int)));
}


QSize NScrollBar::sizeHint() const{
    return QSize(24, 24);
}


void NScrollBar::initUI(){
    setObjectName("NScrollBar");
    setAutoFillBackground(false);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedWidth(24);
    setStyleSheet("#NScrollBar{border:0px;background-color:transparent;}");

    _handle = new NHandle(this);
    _handle->setObjectName("handle");
    _handle->setFocusPolicy(Qt::NoFocus);
    _handle->setCheckable(false);
    _handle->setStyleSheet("#handle{border:0px;background:url(:Main/ScrollBar_Btn.png) center no-repeat;}");
    _handle->setGeometry(_handle_x, 0, 22, 22);

    connect(_handle, SIGNAL(handleMoved(int)), this, SLOT(reCalcValue(int)));
}


void NScrollBar::refreshHandlePosition(){
    int maxHeight = frameSize().height() - _handle->height();
    if(_maximum == 0){
        _handle->setGeometry(_handle_x, 0, 22, 22);
        return;
    }
    double pos = (double)_value / (double)_maximum * (double)maxHeight;
    _handle->setGeometry(_handle_x, qMin(maxHeight, (int)pos), 22, 22);
    _handle->update();
    update();
}


void NScrollBar::setValueWithAnimate(int newValue){
    if(_valueAnimation->state() == QPropertyAnimation::Running){
        _valueAnimation->stop();
    }

    if(newValue <= height()){
        int stateValue = _value;
        emit scrollToMin();
        if(stateValue < _value){
            newValue = newValue + (_value - stateValue);
        }
    }

    _valueAnimation->setStartValue(value());
    _valueAnimation->setEndValue(newValue);

    double distance = qAbs(newValue - value());
    double time = (double)maximum() / (double)height() / 2.0 * 600.0 * (distance / (double)height());
    time = qMin(600.0, time);
    _valueAnimation->setDuration(time);
    _valueAnimation->start();
}


void NScrollBar::reCalcValue(int pos){
    int maxHeight = frameSize().height() - _handle->height();
    if(_maximum == 0){
        _handle->setGeometry(_handle_x, 0, 22, 22);
        return;
    }
    double value = (double)pos /(double)maxHeight * (double)_maximum;

    setValueWithAnimate(qMin((int)value, _maximum));
}


void NScrollBar::setNRange(int min, int max){
    _minimum = min;
    _maximum = max;
    refreshHandlePosition();
}


void NScrollBar::setNValue(int value){
    _value = value;
    refreshHandlePosition();
}


void NScrollBar::paintEvent(QPaintEvent *event){
    _handle_x = (rect().width() - 22) / 2;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//启用反走样以得到平滑的边缘
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);

    painter.save();
    painter.translate((rect().width() - 3)/2, 0);
    QRect bgRect = rect();
    bgRect.setWidth(3);
    bgRect.setHeight(bgRect.height() - 5);
    painter.drawPixmap(bgRect,QPixmap(":Main/Scrollbar_Line.png"));
    painter.restore();

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    QWidget::paintEvent(event);
}


void NScrollBar::mousePressEvent(QMouseEvent *event){
    event->accept();
    reCalcValue(event->pos().y());
}


void NScrollBar::wheelEvent(QWheelEvent *event){
//    QPoint numPixels = event->pixelDelta();
//    QPoint numDegrees = event->angleDelta() / 120;

//    int y = 0;
//    if(numDegrees.isNull()){
//        y = numPixels.ry();
//    }else{
//        y = numDegrees.ry();
//    }
//    y = value() - pageStep()/3 * 2 * y;
//    if(y > 0){
//        y = qMin(_maximum, y);
//    }else{
//        y = 0;
//    }

//    setValueWithAnimate(y);
}

void NScrollBar::resizeEvent(QResizeEvent *event){
    refreshHandlePosition();
    QScrollBar::resizeEvent(event);
}


NHandle::NHandle(QWidget *parent) :
    QPushButton(parent)
  , _isDrag(false)
{

}


void NHandle::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        _isDrag = true;
        _lastHeight = event->globalY() - frameGeometry().topLeft().y();
        event->accept();
    }
    _isDrag = true;
}


void NHandle::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        _isDrag = false;
        event->accept();
    }
}


void NHandle::mouseMoveEvent(QMouseEvent *event){
    if (_isDrag){
        int targetHeight = event->globalY() - _lastHeight;
        int maxHeight = parentWidget()->frameSize().height() - frameGeometry().height();

        if(targetHeight > maxHeight){
            targetHeight = maxHeight;
        }
        if(targetHeight < 0){
            targetHeight = 0;
        }

        event->accept();

        emit handleMoved(targetHeight);
    }
}
