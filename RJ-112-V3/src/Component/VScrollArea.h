#ifndef VSCROLLAREA_H
#define VSCROLLAREA_H

#include <QScrollArea>
#include <QScrollBar>
#include <QPoint>

class VScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit VScrollArea(QWidget *parent = 0);
    ~VScrollArea();

    void setFixedWidthEx(int width);
    void setFixedHeightEx(int height);
signals:
    void sendVerticalScrollBarValue(int value);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    bool mMoveStart;
    bool mContinousMove;
    QPoint mMousePoint;
    QScrollBar* scrollBar;

};

#endif // VSCROLLAREA_H
