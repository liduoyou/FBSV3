#-------------------------------------------------
#
# Project created by QtCreator 2015-07-12T08:07:38
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += xml
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RJ-112-V3
TEMPLATE = app
TRANSLATIONS+=international.ts

SOURCES += src/MainWidget.cpp \
    src/MainWindow.cpp \
    src/main.cpp \
    src/Component/CardWidget.cpp \
    src/Component/VScrollArea.cpp \
    src/Component/HScrollArea.cpp \
    src/Component/ZoomPushButton.cpp \
    src/Component/CustomLabel.cpp \
    src/Component/NScrollBar.cpp \
    src/BaseClass/LittleVehicle.cpp \
    src/BaseClass/Hook.cpp \
    src/BaseClass/BigVehicle.cpp \
    src/BaseDB/CDateBase.cpp \
    src/BaseWidgets/LittleVehicleWidget.cpp \
    src/BaseWidgets/HookWidget.cpp \
    src/BaseWidgets/BigVehicleWidget.cpp \
    src/UI/NavigatePointWidget.cpp \
    src/UI/AbstractWidget.cpp \
    src/ListViewManager/CardInfo.cpp \
    src/ListViewManager/CardViewItemDelegate.cpp \
    src/ListViewManager/CardListView.cpp \
    src/ListViewManager/CardListModel.cpp \
    src/ListViewManager/CardManagerWidget.cpp \
    src/ListViewManager/ThumbnailProvider.cpp \
    src/QThread/TcpClientThread.cpp \
    src/QThread/RelayStatusThread.cpp \
    src/QThread/QZigbeeThread.cpp \
    src/SerialPort/qextserialport.cpp \
    src/SerialPort/qextserialbase.cpp \
    src/SerialPort/posix_qextserialport.cpp \
    src/QThread/CpuMemThread.cpp \
    src/Component/CommonNotifyWidget.cpp \
    src/Component/CommonNotify.cpp \
    src/Menu/MuteSelectionDelegate.cpp \
    src/Menu/MenuListWidget.cpp \
    src/Menu/MenuItemWidget.cpp \
    src/Menu/MenuInfo.cpp \
    src/UI/ControlPanel.cpp \
    src/UI/CustomTabWidget.cpp \
    src/UI/DetailWidget.cpp \
    src/Component/NavigationNode.cpp \
    src/Component/RoundWidget.cpp \
    src/Component/CPushbutton.cpp \
    src/Component/SubLimitStatus.cpp \
    src/AcquisitionPort/AcquisitionPortManager.cpp \
    src/AcquisitionPort/AcquisitionPort.cpp \
    src/Settings/SettingsManager.cpp \
    src/Settings/ReadConfig.cpp

HEADERS  += src/MainWidget.h \
    src/MainWindow.h \
    src/DataHeaderDefine.h \
    src/Component/CardWidget.h \
    src/Component/VScrollArea.h \
    src/Component/HScrollArea.h \
    src/Component/ZoomPushButton.h \
    src/Component/CustomLabel.h \
    src/Component/NScrollBar.h \
    src/BaseClass/LittleVehicle.h \
    src/BaseClass/Hook.h \
    src/BaseClass/BigVehicle.h \
    src/BaseDB/CDateBase.h \
    src/BaseWidgets/LittleVehicleWidget.h \
    src/BaseWidgets/HookWidget.h \
    src/BaseWidgets/BigVehicleWidget.h \
    src/UI/NavigatePointWidget.h \
    src/UI/AbstractWidget.h \
    src/ListViewManager/CardInfo.h \
    src/ListViewManager/CardViewItemDelegate.h \
    src/ListViewManager/CardListView.h \
    src/ListViewManager/CardListModel.h \
    src/ListViewManager/CardManagerWidget.h \
    src/ListViewManager/ThumbnailProvider.h \
    src/QThread/TcpClientThread.h \
    src/QThread/RelayStatusThread.h \
    src/QThread/QZigbeeThread.h \
    src/QThread/CpuMemThread.h \
    src/SerialPort/qextserialport.h \
    src/SerialPort/qextserialbase.h \
    src/SerialPort/posix_qextserialport.h \
    src/Component/CommonNotifyWidget.h \
    src/Component/CommonNotify.h \
    src/Menu/MuteSelectionDelegate.h \
    src/Menu/MenuListWidget.h \
    src/Menu/MenuItemWidget.h \
    src/Menu/MenuInfo.h \
    src/UI/ControlPanel.h \
    src/UI/CustomTabWidget.h \
    src/UI/DetailWidget.h \
    src/Component/NavigationNode.h \
    src/Component/RoundWidget.h \
    src/Component/CPushbutton.h \
    src/Component/SubLimitStatus.h \
    src/AcquisitionPort/AcquisitionPortManager.h \
    src/AcquisitionPort/AcquisitionPort.h \
    src/Settings/SettingsManager.h \
    src/Settings/ReadConfig.h

RESOURCES += \
    res/resource.qrc

OTHER_FILES +=
