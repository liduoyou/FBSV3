#include "MenuItemWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QMouseEvent>
#include <QDebug>
#include "MenuInfo.h"
MenuItemWidget::MenuItemWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUI();
    setStyleSheet("QWidget{background: transparent;}");
}

void MenuItemWidget::setupUI() {
    QHBoxLayout *mainLayout = new QHBoxLayout;
    _cardIconLabel = new QLabel;
    _cardIconLabel->setFixedSize(41, 41);
    mainLayout->addWidget(_cardIconLabel,Qt::AlignCenter);
    _cardNameLabel = new QLabel;
    _cardNameLabel->setFixedHeight(41);
    mainLayout->addWidget(_cardNameLabel,Qt::AlignCenter);
    setLayout(mainLayout);
}

void MenuItemWidget::setCardIcon(const QString &iconUrl) {
    m_iconUrl = iconUrl;
    QPixmap pic(iconUrl);
    if(!pic.isNull()) {
        _cardIconLabel->setPixmap(pic.scaled(40, 40, Qt::KeepAspectRatio));
    } else {
//        qDebug() << "invalid pixmap url " << iconUrl;
    }
}

void MenuItemWidget::setCardName(const QString &cardName) {
    _cardNameLabel->setText(cardName);
}

void MenuItemWidget::refresh(const MenuInfo &menuInfo) {
    setCardIcon(menuInfo.getIconName());
    setCardName(menuInfo.getlabelText());
}

QString MenuItemWidget::getCardName() const
{
    return _cardNameLabel->text();
}

QString MenuItemWidget::getCardIcon() const
{
    return m_iconUrl;
}
