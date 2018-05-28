#include "VScrollArea.h"
#include <QDebug>
#include <QMouseEvent>
#include <QScrollBar>
VScrollArea::VScrollArea(QWidget *parent) :
    QScrollArea(parent)
{
    installEventFilter(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("QScrollArea{border:0px;background-color:transparent;}");
    scrollBar = verticalScrollBar();
}

VScrollArea::~VScrollArea()
{

}

void VScrollArea::setFixedWidthEx(int width)
{
    setFixedWidth(width);
}

void VScrollArea::setFixedHeightEx(int height)
{
    setFixedHeight(height);
}

bool VScrollArea::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent* me = (QMouseEvent*) event;
        if ((me->buttons() & Qt::LeftButton)) {
            if (!mMoveStart) {
                mMoveStart = true;
                mContinousMove =false;
                mMousePoint = me->globalPos();
            }
            else {
                QPoint p = me->globalPos();
                int offset = p.y() - mMousePoint.y();
                if( !mContinousMove && ( offset > -10 && offset < 10 ) )
                    return false;

                mContinousMove = true;

                int currentvalue = scrollBar->value() - offset;
                scrollBar->setValue(currentvalue);
                emit sendVerticalScrollBarValue(currentvalue);
                mMousePoint = p;
            }
            return true;
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease) {
        mMoveStart = false;
    }
    return QObject::eventFilter(obj, event);
}
