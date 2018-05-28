#ifndef COMMONNOTIFY_H
#define COMMONNOTIFY_H

#include <QObject>

class CommonNotifyWidget;
class CommonNotify : public QObject
{
    Q_OBJECT
public:
    static CommonNotify *instance();

    explicit CommonNotify(QObject *parent = 0);

    ~CommonNotify();

    static void messageBox(QString text);

    static void messageBox(QString title, QString text);

    static bool exists();

signals:

public slots:

private slots:
    void recycleNotice();

    void adjustNoticePosition();

private:
    static QList<CommonNotifyWidget*> _noticeList;

    static CommonNotify *_instance;
};

#endif // COMMONNOTIFY_H
