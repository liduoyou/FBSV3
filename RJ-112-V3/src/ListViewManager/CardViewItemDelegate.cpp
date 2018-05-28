﻿#include "CardViewItemDelegate.h"
#include "CardListModel.h"
#include <QDebug>
#include <QStyleOptionViewItem>
#include <QApplication>
#include <QPixmap>
#include <QPainter>

CardViewItemDelegate::CardViewItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    qDebug()<<"CardViewItemDelegate::CardViewItemDelegate";
}

CardViewItemDelegate::~CardViewItemDelegate()
{
    qDebug()<<"CardViewItemDelegate::~CardViewItemDelegate()";
}

static void extractFolderName(const QString& path, QString& folderName) {
    QStringList tmp = path.split("/");
    if(tmp.size() > 1) {
        folderName = tmp.at(tmp.size()-1);
    }
}

QSize CardViewItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const{
    return QStyledItemDelegate::sizeHint(option,index);
}

void CardViewItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItemV4 optionV4 = option;
    optionV4.rect.setWidth(160);
    optionV4.rect.setHeight(160);
    // 重绘背景
    QRect icon_rect(optionV4.rect.topLeft().x()-2, optionV4.rect.topLeft().y()-2, 164, 164);
    QPen pen(optionV4.palette.color(QPalette::Normal, QPalette::Text));
    pen.setColor(Qt::transparent);
    painter->setPen(pen);
    painter->drawRect(icon_rect);
    if(optionV4.state & QStyle::State_Selected) {
        QPoint point(optionV4.rect.topLeft());
        point.setX(point.x()+1);
        point.setY(point.y()+1);
        QSize size(optionV4.decorationSize);
        size.setHeight(size.height()+2);
        size.setWidth(size.width()+2);
        painter->setPen("#ee9304");
//        painter->setPen("transparent");
        painter->drawRect(QRect(point, size));
    }
    bool isHover = false;
    if((optionV4.state & QStyle::State_MouseOver) && !(optionV4.state & QStyle::State_Selected)) {
        isHover = true;
    }
    initStyleOption(&optionV4, index);
    QString folderName;
    extractFolderName(optionV4.text, folderName);
//    if(optionV4.state & QStyle::State_Selected) {
//        qDebug() <<"optionV4.text ="<<optionV4.text<<"folderName="<<folderName;
//    }
    optionV4.text = "";
    QStyle *style = optionV4.widget? optionV4.widget->style() : QApplication::style();
    // 去掉selected状态，使得选中时不会高亮
    optionV4.state = optionV4.state & (~QStyle::State_Selected);
    style->drawControl(QStyle::CE_ItemViewItem, &optionV4, painter);
    if(isHover) {
        // 重绘decoration
        QRect icon_rect(optionV4.rect.topLeft().x()-2, optionV4.rect.topLeft().y()-2, 164, 164);
        painter->drawPixmap(icon_rect, optionV4.icon.pixmap(icon_rect.size()).scaled(icon_rect.size(),Qt::KeepAspectRatio));
        QPen pen(optionV4.palette.color(QPalette::Normal, QPalette::Text));
        pen.setColor("#ADADAD");
        painter->setPen(pen);
        QRect rect(icon_rect.topLeft().x(), icon_rect.bottomLeft().y()-24, icon_rect.width(), 24);
        QTextOption textOption(Qt::AlignCenter);
        textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter->fillRect(rect, QColor(54, 54, 54, 153));//bar 44, 44, 44, 153
        painter->drawText(rect, folderName, textOption);
    }
}
