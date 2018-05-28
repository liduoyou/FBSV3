#include "CardWidget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QPainter>
#include <QStyleOption>
#include <QProgressBar>
#include "../DataHeaderDefine.h"
CardWidget::CardWidget(QWidget *parent)
    : QWidget(parent)
    , m_size(m_CardWidthstandard,(int)(m_CardWidthstandard+0.618*m_CardWidthstandard))
    , m_LabelTitleimage(NULL)
    , m_LabelTitleName(NULL)
    , m_LabelValue(NULL)
    , m_LabelUnit(NULL)
    , m_ProgressbarStatus(NULL)
    , m_currentvalue(0.000)
    , m_bartype(false)
{
    setupUI();
}

CardWidget::~CardWidget()
{
    qDebug()<<"CardWidget::~CardWidget()";
}

void CardWidget::setImageFilename(QString filename)
{
    m_imagefilename = filename;
}

QString CardWidget::getImageFilename() const
{
    return m_imagefilename;
}

void CardWidget::setTitlename(QString titlename)
{
    m_titlename = titlename;
}

QString CardWidget::getTitlename() const
{
    return m_titlename;
}

void CardWidget::setCurrentValue(double value)
{
    m_currentvalue = value;
    accordingToValueChange();
}

double CardWidget::getCurrentValue() const
{
    return m_currentvalue;
}

void CardWidget::setUnit(QString unit)
{
    m_unit = unit;
}

QString CardWidget::getUnit() const
{
    return m_unit;
}

void CardWidget::setBarChangeflag(bool bartype)
{
    m_bartype = bartype;
}

bool CardWidget::getBarChangeflag() const
{
    return m_bartype;
}

int CardWidget::updateProgressBarStatusValue(double curValue, double earlywarn, double warn)
{
    int value;
    value = ((double)curValue/warn)*100;
    int pxValue = m_CardWidthstandard/3/2;
    QString styleSheet;

    if(curValue >= warn){
        m_ProgressbarStatus->setValue(100);
        styleSheet = "QLabel{border:0px;color:#FB5D51;font-size:%1px;background-color:transparent;}";
        m_LabelValue->setStyleSheet(styleSheet.arg(QString::number(pxValue)));
        m_ProgressbarStatus->setStyleSheet("QProgressBar{border:2px solid #FB5D51;border-radius: 0px;}\
                                           QProgressBar::chunk {background-color: #FB5D51;}");
        return 1;
    }else if(curValue >= earlywarn && curValue < warn){
        m_ProgressbarStatus->setValue(value);
        styleSheet = "QLabel{border:0px;color:#F9BE34;font-size:%1px;background-color:transparent;}";
        m_LabelValue->setStyleSheet(styleSheet.arg(QString::number(pxValue)));
        m_ProgressbarStatus->setStyleSheet("QProgressBar{border:2px solid #F9BE34;border-radius: 0px;}\
                                           QProgressBar::chunk {background-color: #F9BE34;}");
        return 2;
    }else if (curValue < earlywarn){
        m_ProgressbarStatus->setValue(value);
        styleSheet = "QLabel{border:0px;color:black;font-size:%1px;background-color:transparent;}";
        m_LabelValue->setStyleSheet(styleSheet.arg(QString::number(pxValue)));
        m_ProgressbarStatus->setStyleSheet("QProgressBar{border:2px solid #0f9d58;border-radius: 0px;}\
                                           QProgressBar::chunk {background-color: #0f9d58;}");
        return 0;
    }
    return 0;
}

int CardWidget::updateProgressBarStatusValue(double curValue, double maxValue,
                                             double warn1, double earlywarn1,
                                             double earlywarn2, double warn2)
{
    int value;
    value = ((double)curValue/maxValue)*100;
    int pxValue = m_CardWidthstandard/3/2;
    QString styleSheet;

    if ((curValue > earlywarn1 && curValue < earlywarn2) || curValue == 0){
        m_ProgressbarStatus->setValue(value);
        styleSheet = "QLabel{border:0px;color:black;font-size:%1px;background-color:transparent;}";
        m_LabelValue->setStyleSheet(styleSheet.arg(QString::number(pxValue)));
        m_ProgressbarStatus->setStyleSheet("QProgressBar{border:2px solid #0f9d58;border-radius: 0px;}\
                                                 QProgressBar::chunk {background-color: #0f9d58;}");
        return 0;
    }else if(curValue <= warn1||curValue >= warn2){
        m_ProgressbarStatus->setValue(100);
        styleSheet = "QLabel{border:0px;color:#FB5D51;font-size:%1px;background-color:transparent;}";
        m_LabelValue->setStyleSheet(styleSheet.arg(QString::number(pxValue)));
        m_ProgressbarStatus->setStyleSheet("QProgressBar{border:2px solid #FB5D51;border-radius: 0px;}\
                                                 QProgressBar::chunk {background-color: #FB5D51;}");
        return 1;
    }else if((curValue > warn1 && curValue <= earlywarn1)||
             (curValue >= earlywarn2 && curValue < warn2)){
        m_ProgressbarStatus->setValue(value);
        styleSheet = "QLabel{border:0px;color:#F9BE34;font-size:%1px;background-color:transparent;}";
        m_LabelValue->setStyleSheet(styleSheet.arg(QString::number(pxValue)));
        m_ProgressbarStatus->setStyleSheet("QProgressBar{border:2px solid #F9BE34;border-radius: 0px;}\
                                                 QProgressBar::chunk {background-color: #F9BE34;}");
        return 2;
    }
    return 0;
}

void CardWidget::setupUI()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_LayoutUsesWidgetRect);
    setStyleSheet("QWidget{border:0px;}");
    setFixedSize(m_size);

    QVBoxLayout* m_vbox = new QVBoxLayout();
    m_vbox->setContentsMargins(0, 0, 0, 20);
    m_vbox->setSpacing((int)(m_CardWidthstandard-(int)m_CardWidthstandard*0.818));

    QHBoxLayout* m_hbox = new QHBoxLayout();
    m_hbox->setContentsMargins(5, 45, 5, 0);
    m_hbox->setSpacing(0);

    m_LabelTitleimage = new QLabel(this);
    m_LabelTitleimage->setScaledContents(true);
    m_LabelTitleimage->setWordWrap(true);
    m_LabelTitleimage->setFocusPolicy(Qt::NoFocus);
    m_LabelTitleimage->setFixedSize(m_CardWidthstandard,m_CardWidthstandard-(int)m_CardWidthstandard*0.318);
    QPixmap* icon = new QPixmap(":Main/Title.png");
    icon->scaled(m_LabelTitleimage->size(),Qt::KeepAspectRatio);
    m_LabelTitleimage->setPixmap(*icon);
    m_LabelTitleimage->move(0,0);

    m_LabelTitleName = new QLabel(this);
    m_LabelTitleName->setScaledContents(true);
    m_LabelTitleName->setWordWrap(true);
    m_LabelTitleName->setFocusPolicy(Qt::StrongFocus);
    m_LabelTitleName->setAlignment(Qt::AlignCenter);
    m_LabelTitleName->setFixedSize(m_CardWidthstandard/3,m_CardWidthstandard/3);
    m_LabelTitleName->setText(tr("吊 重"));
    int pxValue = m_CardWidthstandard/3/2;
    QString styleSheet = "QLabel{border:0px;color:black;border-radius:%1px;font-size:20px;background-color:white;}";
    m_LabelTitleName->setStyleSheet(styleSheet.arg(QString::number(pxValue)));
    m_LabelTitleName->move(m_CardWidthstandard/3,m_CardWidthstandard-(int)m_CardWidthstandard*0.318-(m_CardWidthstandard/3/2));
    m_LabelTitleName->raise();

    m_LabelValue = new QLabel();
    m_LabelValue->setWordWrap(true);
    m_LabelValue->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    m_LabelValue->setFixedHeight(m_CardWidthstandard/4);
    m_LabelValue->setText(tr("195.124"));
    pxValue = m_CardWidthstandard/6;
    styleSheet = "QLabel{border:0px;color:black;font-size:%1px;background-color:transparent;}";
    m_LabelValue->setStyleSheet(styleSheet.arg(QString::number(pxValue)));

    m_LabelUnit = new QLabel();
    m_LabelUnit->setWordWrap(true);
    m_LabelUnit->setAlignment(Qt::AlignRight|Qt::AlignBottom);
    m_LabelUnit->setFixedHeight(m_CardWidthstandard/4);
    m_LabelUnit->setText(tr("KN*M"));
    pxValue = m_CardWidthstandard/8;
    styleSheet = "QLabel{border:0px;color:black;font-size:%1px;background-color:transparent;}";
    m_LabelUnit->setStyleSheet(styleSheet.arg(QString::number(pxValue)));

    m_ProgressbarStatus = new QProgressBar();
    m_ProgressbarStatus->setRange(0,100);
    m_ProgressbarStatus->setFixedSize(m_CardWidthstandard-10,m_CardWidthstandard/6);
    m_ProgressbarStatus->setAlignment(Qt::AlignCenter);
    m_ProgressbarStatus->setTextVisible(false);
    m_ProgressbarStatus->setValue(50);
    m_ProgressbarStatus->setStyleSheet("QProgressBar{border:2px solid #0f9d58;border-radius:0px;} QProgressBar::chunk {background-color: #0f9d58;}");
    m_vbox->addWidget(m_LabelTitleimage,1,Qt::AlignTop);
    m_hbox->addWidget(m_LabelValue,1,Qt::AlignLeft);
    m_hbox->addWidget(m_LabelUnit,1,Qt::AlignRight);
    m_vbox->addLayout(m_hbox);
    m_vbox->addWidget(m_ProgressbarStatus,1,Qt::AlignCenter|Qt::AlignBottom);

    setLayout(m_vbox);
}

void CardWidget::accordingToValueChange()
{
    if(!getImageFilename().isEmpty()){
        QPixmap* icon = new QPixmap(getImageFilename());
        icon->scaled(m_LabelTitleimage->size(),Qt::KeepAspectRatio);
        m_LabelTitleimage->setPixmap(*icon);
    }
    if(!getTitlename().isEmpty()){
        m_LabelTitleName->setText(getTitlename());
    }
    m_LabelValue->setText(QString::number(getCurrentValue(),10,3));
    if(!getUnit().isEmpty()){
        m_LabelUnit->setText(getUnit());
    }
    if(getBarChangeflag()){
        updateProgressBarStatusValue(getCurrentValue(),getCurrentValue(),getCurrentValue());
    }else{
        updateProgressBarStatusValue(getCurrentValue(),getCurrentValue(),
                                     getCurrentValue(),getCurrentValue(),
                                     getCurrentValue(),getCurrentValue());
    }
}

void CardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//启用反走样以得到平滑的边缘
    painter.setPen(QColor("#FFFBF0"));//设置画笔
    painter.setBrush(QColor("#FFFBF0"));//设置画布

    painter.save();

    QRect bgRect;
    bgRect.setWidth(m_CardWidthstandard);
    bgRect.setHeight((int)(0.618*m_CardWidthstandard));
    bgRect.setWidth(rect().width());
    bgRect.setHeight(rect().height());
    painter.drawRect(bgRect);

    painter.restore();

    //set Style...
    QStyleOption opt;
    opt.init(this);
    painter.setClipping(true);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}

void CardWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
//    setFixedSize(m_Widthstandard,(int)0.618*m_Widthstandard);
}
