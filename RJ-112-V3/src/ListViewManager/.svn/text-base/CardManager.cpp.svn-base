#include "CardManager.h"
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QPixmap>
#include <QUrl>
#include <QScrollBar>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include "CardViewItemDelegate.h"
#include "CardInfo.h"
#include "../MainWidget.h"
CardManager::CardManager(QWidget *parent) :
    QWidget(parent)
{
    setupUI();
    createconnections();
}

void CardManager::setupUI()
{
    setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(initCardViewWidget());

    setLayout(mainLayout);
}

void CardManager::createconnections()
{
    connect(m_cardView, SIGNAL(clicked(QModelIndex)), this, SLOT(toggleSelectAll()));
    connect(m_cardSelectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(toggleSelectAll(QItemSelection,QItemSelection)));
}

void CardManager::toggleSelectAll() {
//    if(_selectAllButton->isChecked()) {
//        _selectAllButton->setChecked(false);
//    }
}

void CardManager::toggleSelectAll(const QItemSelection& selection, const QItemSelection& pselection) {
    Q_UNUSED(pselection);
//    if(selection.indexes().count() <= 1 && _selectAllButton->isChecked()) {
//        _selectAllButton->setChecked(false);
//    }
}

void CardManager::addFolder(const QString &dirPath) {
    QDir dir(dirPath);
    QStringList pics;
    QFileInfoList infos = dir.entryInfoList(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot | QDir::System);
    foreach(const QFileInfo& info, infos) {
//        if(info.isFile() && ThumbnailProvider::globalInstance()->isImage(info.suffix())) {
//            pics << info.absoluteFilePath();
//        }
//        else if(info.isDir()) {
//            addFolder(info.absoluteFilePath());
//        }
    }
    if(pics.size()) {
//        ThumbnailProvider::globalInstance()->loadcomputerImages(pics);
    }
}

QWidget* CardManager::initCardViewWidget() {
    m_stackedWidget = new QStackedWidget;
    m_stackedWidget->setAttribute(Qt::WA_LayoutOnEntireRect);
    m_stackedWidget->setObjectName("stackedWidget");
    m_stackedWidget->setStyleSheet("#stackedWidget{border:0px; background: transparent;}");

    QWidget *noCardPage = new QWidget;
    QHBoxLayout *noCardLayout = new QHBoxLayout;
    QPixmap bitmap(":Main/picture_icon_nopictures.png");
    QLabel *label = new QLabel;
    label->setPixmap(bitmap);
    noCardLayout->addWidget(label, 0, Qt::AlignCenter);
    noCardPage->setLayout(noCardLayout);
    m_stackedWidget->addWidget(noCardPage);

    QWidget *cardViewPage = new QWidget;
    cardViewPage->setObjectName("cardViewPage");
    cardViewPage->setStyleSheet("#cardViewPage{border:0px; image: url(:Main/pictures_clack.png);}");
    cardViewPage->setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->setSizeConstraint(QLayout::SetMaximumSize);
    hBoxLayout->setContentsMargins(28, 26, 28, 26);//28, 26, 1, 28
    m_cardListModel = new CardListModel;
    m_dataChangedModel = new QSortFilterProxyModel(this);
    m_dataChangedModel->setSourceModel(m_cardListModel);
    m_dataChangedModel->sort(0);
    m_cardView = new CardListView;
    m_cardView->setModel(m_dataChangedModel);
    m_cardListModel->setPhotoListView(m_cardView); // 将view指针传递给model，调用itemIsVisiable实现model数据懒惰加载
    m_cardSelectionModel = m_cardView->selectionModel();
    connect(m_cardListModel, SIGNAL(setCurrentIndex(QModelIndex)), m_cardView, SLOT(onSetCurrentIndex(QModelIndex)));
    connect(MainWidget::instance(), SIGNAL(preappendImage(QStringList)), m_cardListModel, SLOT(onPreappendImage(QStringList)));
    m_cardView->setObjectName("photoView");
    m_cardView->setStyleSheet("#photoView{border:0px; background: transparent;}");
    m_cardView->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    m_cardView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_cardView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_cardView->setViewMode(QListView::IconMode);
    m_cardView->setFlow(QListView::LeftToRight);
    m_cardView->setResizeMode(QListView::Adjust);
    m_cardView->setGridSize(QSize(160, 160));
    m_cardView->setIconSize(QSize(156, 156));
    m_cardView->setSpacing(0);
    m_cardView->setUniformItemSizes(true);
    m_cardView->setMovement(QListView::Static);
    m_cardView->setAttribute(Qt::WA_MacShowFocusRect, 0);
    m_cardView->setFocus();
    m_cardView->resize(840, m_cardView->height());
//    _photoView->setVerticalScrollBar(new NScrollBar);
    m_cardView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_cardView->setItemDelegate(new CardViewItemDelegate);
    m_cardView->setMouseTracking(true);
    hBoxLayout->addWidget(m_cardView);
    cardViewPage->setLayout(hBoxLayout);

    m_stackedWidget->addWidget(cardViewPage);

    m_stackedWidget->setCurrentIndex(0);
    return m_stackedWidget;
}

void CardManager::onSearchTextChanged(const QString &text) {
    QRegExp regExp(text, Qt::CaseInsensitive, QRegExp::FixedString);
    m_dataChangedModel->setFilterRegExp(regExp);
}

void CardManager::onNoPictures() {
    m_stackedWidget->setCurrentIndex(0);
}

void CardManager::onHasPictures() {
    m_stackedWidget->setCurrentIndex(1);
}
