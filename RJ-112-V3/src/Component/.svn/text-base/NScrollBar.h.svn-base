#ifndef NSCROLLBAR_H
#define NSCROLLBAR_H

#include <QScrollBar>
#include <QPushButton>
#include <QSize>

class QPaintEvent;
class QMouseEvent;
class QWheelEvent;
class QPushButton;
class QPropertyAnimation;

class NHandle : public QPushButton{
    Q_OBJECT
public:
    explicit NHandle(QWidget *parent = 0);

signals:
    void handleMoved(int moveHeight);

    void valueChanged(int value);

    void rangeChanged(int min, int max);

protected:
    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

private:
    bool _isDrag;

    int _lastHeight;
};



class NScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit NScrollBar(QWidget *parent = 0);

    QSize sizeHint() const;

signals:
    void scrollToMin();

public slots:

    void setNRange(int min, int max);

    void setNValue(int value);

protected:
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent* event);

    void resizeEvent(QResizeEvent *event);

private slots:
    void reCalcValue(int pos);

private:
    void initUI();

    void refreshHandlePosition();

    void setValueWithAnimate(int newValue);

    NHandle *_handle;

    QPropertyAnimation* _valueAnimation;

    int _minimum;

    int _maximum;

    int _value;

    int _handle_x;

};

#endif // NSCROLLBAR_H
