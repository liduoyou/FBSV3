#include "MenuListWidget.h"
#include <QPainterPath>
#include <QPainter>
#include <QDebug>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QApplication>
#include "muteselectiondelegate.h"
#include "MenuItemWidget.h"
const int MaxAppItemCount = 4;

MenuListWidget::MenuListWidget(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint|Qt::Popup)//
{
    setupUI();
    resize(185,225);
    move(parent->width()-width(),56);
    hide();
}

void MenuListWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//启用反走样以得到平滑的边缘
    painter.setPen(QColor("#FDFDFD"));
    painter.setBrush(QColor("#FDFDFD"));

    painter.save();

    QRect bgRect = rect();
    bgRect.setWidth(rect().width());
    bgRect.setHeight(rect().height());
    painter.drawRect(bgRect);

    painter.restore();

    QPainterPath path;
    path.addRoundRect(0, 8, 185, 8+_displayCount*52, 10);
    path.moveTo(172, 0);
    path.lineTo(172-5, 8);
    path.lineTo(172+5, 8);

//    painter.setPen(QColor("#0f9d58"));
//    painter.setBrush(QColor("#0f9d58"));
    painter.setPen(Qt::transparent);
    painter.setBrush(Qt::transparent);
    painter.drawPath(path);
    painter.fillPath(path, QColor(255,255,255,128));
}

void MenuListWidget::setupUI() {
    setStyleSheet("QWidget{border:0px; background-color:transparent;}");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
    _listWidget = new QListWidget;
    _listWidget->setItemDelegate(new MuteSelectionDelegate);
    _listWidget->setObjectName("listWidget");
    _listWidget->setStyleSheet("#listWidget{border:0px; background-color:transparent;}");
    _listWidget->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    _listWidget->setAttribute(Qt::WA_MacShowFocusRect, 0);
    _listWidget->viewport()->setFocusPolicy(Qt::NoFocus);
    connect(_listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onitemSelected(QListWidgetItem*)));
    for(int i=0;i<MaxAppItemCount;++i) {
        QListWidgetItem *item = new QListWidgetItem(_listWidget);
        item->setSizeHint(QSize(180, 55));
        MenuItemWidget *menuWidget = new MenuItemWidget;
        _listWidget->setItemWidget(item, menuWidget);
    }
    mainLayout->addWidget(_listWidget);
    setLayout(mainLayout);
}

/*
 * 根据查询结果更新GUI
 */
void MenuListWidget::onSettingCompleted(const QList<MenuInfo> &list) {
    if(list.size() == 0){
        hide();
    } else {
        refreshListWidget(list);
    }
}

void MenuListWidget::hide() {
    QWidget::hide();
}

void MenuListWidget::refreshListWidget(const QList<MenuInfo> &list) {
    _displayCount = qMin(list.size(), MaxAppItemCount);
    if(_displayCount == 0) {
        hide();
    } else {
        show();
        update();
        // 显示搜索结果
        for(int i=0;i<_displayCount;++i) {
            QListWidgetItem *item = _listWidget->item(i);
            if(item != NULL) {
                MenuItemWidget *menuWidget = qobject_cast<MenuItemWidget *>(_listWidget->itemWidget(item));
                if(menuWidget != NULL) {
                    menuWidget->refresh(list[i]);
                    menuWidget->setHidden(false);
                }
            }
        }
        // 隐藏搜索结果之外的item
        for(int i=_displayCount;i<MaxAppItemCount;++i) {
            QListWidgetItem *item = _listWidget->item(i);
            if(item != NULL) {
                MenuItemWidget *menuWidget = qobject_cast<MenuItemWidget *>(_listWidget->itemWidget(item));
                if(menuWidget != NULL) {
                    menuWidget->setHidden(true);
                }
            }
        }
    }
}

void MenuListWidget::onitemSelected(QListWidgetItem *item)
{
    MenuItemWidget *menuWidget = qobject_cast<MenuItemWidget *>(_listWidget->itemWidget(item));
    qDebug()<<"menuWidget->getCardName()"<<menuWidget->getCardName();
    if(menuWidget != NULL) {
        emit pageRequest(menuWidget->getCardName());
        this->close();
    }
}
