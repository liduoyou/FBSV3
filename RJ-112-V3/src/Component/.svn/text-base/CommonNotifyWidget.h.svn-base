#ifndef COMMONNOTIFYWIDGET_H
#define COMMONNOTIFYWIDGET_H

#include <QWidget>
#include <QSize>
#include <QLabel>

class QVBoxLayout;
class CommonNotifyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CommonNotifyWidget(QWidget *parent = 0);

    void initUI();

    ~CommonNotifyWidget();

    QSize sizeHint() const;

    QString getTitle() const;

    void setTitle(const QString &value);

    QString getNotice() const;

    void setNotice(const QString &value);

signals:
    void timeOut();

protected:
    void timerEvent(QTimerEvent *event);

    void enterEvent(QEvent *);

    void leaveEvent(QEvent *);

private:

    int _selfTimerId;

    QLabel _titleLable;

    QLabel _noticeLable;

    QVBoxLayout *_mainLayout;

};

#endif // COMMONNOTIFYWIDGET_H
