#include "CardListView.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>
CardListView::CardListView(QWidget *parent) :
    QListView(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setStyleSheet("QListView{border:0px;border-radius:0px;background-color:cyan;}");
    setMovement(QListView::Static);
    setViewMode(QListView::IconMode);
    setFlow(QListView::TopToBottom);
    setAttribute(Qt::WA_MSWindowsUseDirect3D,0);
    setResizeMode(QListView::Adjust);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setObjectName("m_listView");
    setAlternatingRowColors(true);//设置隔行变色
    setStyleSheet("#m_listView{background-color:transparent; \
                  selection-background-color:transparent; \
            alternate-background-color:transparent;border:0px;}");

    viewport()->installEventFilter(this);
    setAcceptDrops(true);
    setAutoScroll(true);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}

CardListView::~CardListView()
{
    qDebug()<<"CardListView::~CardListView()";
}
