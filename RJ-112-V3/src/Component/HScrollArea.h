#ifndef HSCROLLAREA_H
#define HSCROLLAREA_H

#include <QScrollArea>
#include <QScrollBar>
#include <QPoint>

class HScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit HScrollArea(QWidget *parent = 0);
    ~HScrollArea();

    void setFixedHeightEx(int height);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    bool mMoveStart;
    bool mContinousMove;
    QPoint mMousePoint;
    QScrollBar* scrollBar;

};

#endif // HSCROLLAREA_H
