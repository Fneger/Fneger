/********************************************************************************
** Form generated from reading UI file 'zpmainframe.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZPMAINFRAME_H
#define UI_ZPMAINFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ZPMainFrame
{
public:
    QAction *actionExit;
    QAction *action_Start_Stop;
    QAction *action_About;
    QAction *actionReload_config_file;
    QAction *actionShow_Window;
    QAction *actionStop_Debug;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *plainTextEdit_status_net;
    QTextEdit *DebugTextEdit;
    QMenuBar *menuBar;
    QMenu *menu_Control;
    QMenu *menu_Help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ZPMainFrame)
    {
        if (ZPMainFrame->objectName().isEmpty())
            ZPMainFrame->setObjectName(QString::fromUtf8("ZPMainFrame"));
        ZPMainFrame->resize(1080, 553);
        ZPMainFrame->setToolTipDuration(-1);
        ZPMainFrame->setIconSize(QSize(16, 16));
        ZPMainFrame->setToolButtonStyle(Qt::ToolButtonIconOnly);
        ZPMainFrame->setAnimated(true);
        ZPMainFrame->setTabShape(QTabWidget::Rounded);
        actionExit = new QAction(ZPMainFrame);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        action_Start_Stop = new QAction(ZPMainFrame);
        action_Start_Stop->setObjectName(QString::fromUtf8("action_Start_Stop"));
        action_Start_Stop->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/Resources/cn11.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/icons/Resources/cn6.png"), QSize(), QIcon::Normal, QIcon::On);
        action_Start_Stop->setIcon(icon);
        action_About = new QAction(ZPMainFrame);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/Resources/4013.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_About->setIcon(icon1);
        actionReload_config_file = new QAction(ZPMainFrame);
        actionReload_config_file->setObjectName(QString::fromUtf8("actionReload_config_file"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/Resources/Color, Lime.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReload_config_file->setIcon(icon2);
        actionShow_Window = new QAction(ZPMainFrame);
        actionShow_Window->setObjectName(QString::fromUtf8("actionShow_Window"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/Resources/Color, Bondi.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShow_Window->setIcon(icon3);
        actionStop_Debug = new QAction(ZPMainFrame);
        actionStop_Debug->setObjectName(QString::fromUtf8("actionStop_Debug"));
        actionStop_Debug->setCheckable(true);
        QIcon icon4;
        QString iconThemeName = QString::fromUtf8("debug");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8(":/icons/Resources/hanukkah_03.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionStop_Debug->setIcon(icon4);
        centralWidget = new QWidget(ZPMainFrame);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        plainTextEdit_status_net = new QPlainTextEdit(centralWidget);
        plainTextEdit_status_net->setObjectName(QString::fromUtf8("plainTextEdit_status_net"));

        horizontalLayout->addWidget(plainTextEdit_status_net);

        DebugTextEdit = new QTextEdit(centralWidget);
        DebugTextEdit->setObjectName(QString::fromUtf8("DebugTextEdit"));

        horizontalLayout->addWidget(DebugTextEdit);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        ZPMainFrame->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ZPMainFrame);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1080, 23));
        menu_Control = new QMenu(menuBar);
        menu_Control->setObjectName(QString::fromUtf8("menu_Control"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        ZPMainFrame->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ZPMainFrame);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(true);
        mainToolBar->setAllowedAreas(Qt::AllToolBarAreas);
        mainToolBar->setFloatable(false);
        ZPMainFrame->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ZPMainFrame);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ZPMainFrame->setStatusBar(statusBar);

        menuBar->addAction(menu_Control->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_Control->addAction(action_Start_Stop);
        menu_Control->addAction(actionReload_config_file);
        menu_Control->addSeparator();
        menu_Control->addAction(actionExit);
        menu_Help->addAction(action_About);
        mainToolBar->addAction(action_Start_Stop);
        mainToolBar->addAction(actionReload_config_file);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_About);
        mainToolBar->addAction(actionStop_Debug);

        retranslateUi(ZPMainFrame);

        QMetaObject::connectSlotsByName(ZPMainFrame);
    } // setupUi

    void retranslateUi(QMainWindow *ZPMainFrame)
    {
        ZPMainFrame->setWindowTitle(QApplication::translate("ZPMainFrame", "ZPMainFrame", nullptr));
        actionExit->setText(QApplication::translate("ZPMainFrame", "E&xit", nullptr));
        action_Start_Stop->setText(QApplication::translate("ZPMainFrame", "&Start/Stop", nullptr));
#ifndef QT_NO_TOOLTIP
        action_Start_Stop->setToolTip(QApplication::translate("ZPMainFrame", "Start or stop the server", nullptr));
#endif // QT_NO_TOOLTIP
        action_About->setText(QApplication::translate("ZPMainFrame", "&About", nullptr));
        actionReload_config_file->setText(QApplication::translate("ZPMainFrame", "&Reload config file", nullptr));
#ifndef QT_NO_TOOLTIP
        actionReload_config_file->setToolTip(QApplication::translate("ZPMainFrame", "Reload Config file", nullptr));
#endif // QT_NO_TOOLTIP
        actionShow_Window->setText(QApplication::translate("ZPMainFrame", "Show&Window", nullptr));
#ifndef QT_NO_TOOLTIP
        actionShow_Window->setToolTip(QApplication::translate("ZPMainFrame", "Show main window", nullptr));
#endif // QT_NO_TOOLTIP
        actionStop_Debug->setText(QApplication::translate("ZPMainFrame", "Stop&Debug", nullptr));
#ifndef QT_NO_TOOLTIP
        actionStop_Debug->setToolTip(QApplication::translate("ZPMainFrame", "Stop Debug", nullptr));
#endif // QT_NO_TOOLTIP
        menu_Control->setTitle(QApplication::translate("ZPMainFrame", "&Control", nullptr));
        menu_Help->setTitle(QApplication::translate("ZPMainFrame", "&Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ZPMainFrame: public Ui_ZPMainFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZPMAINFRAME_H
