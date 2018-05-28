#ifndef MENULISTWIDGET_H
#define MENULISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include "MenuInfo.h"
class MenuListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuListWidget(QWidget *parent = 0);

signals:
    void pageRequest(const QString& pagename);

public slots:
    void hide();
    void onSettingCompleted(const QList<MenuInfo> &list);

private slots:
    void onitemSelected(QListWidgetItem* item);
protected:
    void paintEvent(QPaintEvent *event);
private:
    void setupUI();
    void refreshListWidget(const QList<MenuInfo>& list);

    QListWidget *_listWidget;
    volatile int _displayCount;
};

#endif // MENULISTWIDGET_H
