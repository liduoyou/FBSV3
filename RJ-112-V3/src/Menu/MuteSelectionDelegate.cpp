#include "muteselectiondelegate.h"
#include <QDebug>
#include <QStyleOptionViewItem>
#include <QApplication>
#include <QPixmap>
#include <QPainter>
MuteSelectionDelegate::MuteSelectionDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void MuteSelectionDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItemV4 optionV4 = option;
    // 去掉selected状态，使得选中时不会高亮
    optionV4.state = optionV4.state & (~QStyle::State_Selected);
    QStyledItemDelegate::paint(painter, optionV4, index);
}
