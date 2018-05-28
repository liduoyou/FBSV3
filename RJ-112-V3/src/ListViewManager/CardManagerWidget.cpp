#include "CardManagerWidget.h"
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
#include "../DataHeaderDefine.h"
#include "CardInfo.h"
#include "../MainWidget.h"
#include "../Component/NScrollBar.h"
CardManagerWidget::CardManagerWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUI();
    createconnections();
}

void CardManagerWidget::setupUI()
{
    setAttribute(Qt::WA_LayoutUsesWidgetRect);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(initCardViewWidget());

    setLayout(mainLayout);
}

void CardManagerWidget::createconnections()
{
    connect(m_cardView, SIGNAL(clicked(QModelIndex)), this, SLOT(toggleSelectAll()));
    connect(m_cardSelectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(toggleSelectAll(QItemSelection,QItemSelection)));
    connect(m_cardListModel, SIGNAL(setCurrentIndex(QModelIndex)), m_cardView, SLOT(onSetCurrentIndex(QModelIndex)));
    connect(MainWidget::instance(), SIGNAL(preappendImage(QStringList)), m_cardListModel, SLOT(onPreappendImage(QStringList)));
    connect(MainWidget::instance(), SIGNAL(hasCards()), this, SLOT(onHasCards()));
    connect(MainWidget::instance(), SIGNAL(noCards()), this, SLOT(onNoCards()));
}

void CardManagerWidget::toggleSelectAll(){
//    if(_selectAllButton->isChecked()) {
//        _selectAllButton->setChecked(false);
//    }
}

void CardManagerWidget::toggleSelectAll(const QItemSelection& selection, const QItemSelection& pselection) {
    Q_UNUSED(pselection);
//    if(selection.indexes().count() <= 1 && _selectAllButton->isChecked()) {
//        _selectAllButton->setChecked(false);
//    }
}

void CardManagerWidget::addFolder(const QString &dirPath) {
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

QWidget* CardManagerWidget::initCardViewWidget() {
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
#ifdef MAXRESOLUTION
    cardViewPage->setStyleSheet("#cardViewPage{border:0px; image: url(:Main/pictures_clack.png);}");
#else
    cardViewPage->setStyleSheet("#cardViewPage{border:0px;}");
#endif
    cardViewPage->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    cardViewPage->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->setSizeConstraint(QLayout::SetMaximumSize);
#ifdef MAXRESOLUTION
    hBoxLayout->setContentsMargins(160, 20, 0, 20);
#else
    hBoxLayout->setContentsMargins(40, 0, 0, 0);
#endif
    m_cardListModel = new CardListModel;
    m_cardSortModel = new QSortFilterProxyModel(this);
    m_cardSortModel->setSourceModel(m_cardListModel);
    m_cardSortModel->sort(0);
    m_cardView = new CardListView;
    m_cardView->setModel(m_cardSortModel);
    m_cardListModel->setPhotoListView(m_cardView); // 将view指针传递给model，调用itemIsVisiable实现model数据懒惰加载
    m_cardSelectionModel = m_cardView->selectionModel();
    m_cardView->setObjectName("cardView");
    m_cardView->setStyleSheet("#cardView{border:0px; background-color:transparent;}");
    m_cardView->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    m_cardView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_cardView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_cardView->setViewMode(QListView::IconMode);
    m_cardView->setFlow(QListView::LeftToRight);
    m_cardView->setResizeMode(QListView::Adjust);
    m_cardView->setGridSize(QSize(180, 180));
    m_cardView->setIconSize(QSize(156, 156));
    m_cardView->setSpacing(0);
    m_cardView->setUniformItemSizes(true);
    m_cardView->setMovement(QListView::Static);
    m_cardView->setAttribute(Qt::WA_MacShowFocusRect, 0);
    m_cardView->setFocusPolicy(Qt::NoFocus);
    m_cardView->resize(840, m_cardView->height());
    m_cardView->setVerticalScrollBar(new NScrollBar);
    m_cardView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_cardViewItemDelegate = new CardViewItemDelegate;
    m_cardView->setItemDelegate(m_cardViewItemDelegate);
    m_cardView->setMouseTracking(true);
    hBoxLayout->addWidget(m_cardView);
    cardViewPage->setLayout(hBoxLayout);

    m_stackedWidget->addWidget(cardViewPage);

    m_stackedWidget->setCurrentIndex(0);
    return m_stackedWidget;
}

void CardManagerWidget::onSearchTextChanged(const QString &text) {
    QRegExp regExp(text, Qt::CaseInsensitive, QRegExp::FixedString);
    m_cardSortModel->setFilterRegExp(regExp);
}

void CardManagerWidget::onNoCards() {
    m_stackedWidget->setCurrentIndex(0);
}

void CardManagerWidget::onHasCards() {
    m_stackedWidget->setCurrentIndex(1);
}
