#ifndef MENUITEMWIDGET_H
#define MENUITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "MenuInfo.h"
class MenuItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuItemWidget(QWidget *parent = 0);
    void setCardIcon(const QString& iconUrl);
    QString getCardIcon() const;
    void setCardName(const QString& cardName);
    QString getCardName() const;
    void refresh(const MenuInfo& menuInfo);

protected:

signals:

private slots:

private:
    void setupUI();

    QLabel   *_cardIconLabel;
    QLabel   *_cardNameLabel;
    QString  m_iconUrl;
    MenuInfo   _cardInfo;
};

#endif // MENUITEMWIDGET_H
