#include "HScrollArea.h"
#include <QMouseEvent>
#include <QScrollBar>
#include <QString>
HScrollArea::HScrollArea(QWidget *parent) :
    QScrollArea(parent)
{
    installEventFilter(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("QScrollArea{border:0px;background-color:transparent;}");
}

HScrollArea::~HScrollArea()
{

}

void HScrollArea::setFixedHeightEx(int height)
{
    setFixedHeight(height);
}

bool HScrollArea::eventFilter(QObject *obj, QEvent *event)
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
                scrollBar = horizontalScrollBar();
                QPoint p = me->globalPos();
                int offset = p.x() - mMousePoint.x();
                if( !mContinousMove && ( offset > -10 && offset < 10 ) )
                    return false;

                mContinousMove = true;

                scrollBar->setValue(scrollBar->value() - offset);
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
