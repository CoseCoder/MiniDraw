/********************************************************************************
** Form generated from reading UI file 'MiniDraw.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINIDRAW_H
#define UI_MINIDRAW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiniDrawClass
{
public:
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MiniDrawClass)
    {
        if (MiniDrawClass->objectName().isEmpty())
            MiniDrawClass->setObjectName(QStringLiteral("MiniDrawClass"));
        MiniDrawClass->resize(1181, 815);
        MiniDrawClass->setCursor(QCursor(Qt::CrossCursor));
        MiniDrawClass->setMouseTracking(true);
        MiniDrawClass->setAutoFillBackground(true);
        centralWidget = new QWidget(MiniDrawClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MiniDrawClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MiniDrawClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MiniDrawClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(MiniDrawClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1181, 30));
        MiniDrawClass->setMenuBar(menuBar);

        retranslateUi(MiniDrawClass);

        QMetaObject::connectSlotsByName(MiniDrawClass);
    } // setupUi

    void retranslateUi(QMainWindow *MiniDrawClass)
    {
        MiniDrawClass->setWindowTitle(QApplication::translate("MiniDrawClass", "MiniDraw", 0));
    } // retranslateUi

};

namespace Ui {
    class MiniDrawClass: public Ui_MiniDrawClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIDRAW_H
