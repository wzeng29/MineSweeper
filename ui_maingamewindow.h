/********************************************************************************
** Form generated from reading UI file 'maingamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINGAMEWINDOW_H
#define UI_MAINGAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainGameWindow
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *MainGameWindow)
    {
        if (MainGameWindow->objectName().isEmpty())
            MainGameWindow->setObjectName(QString::fromUtf8("MainGameWindow"));
        MainGameWindow->resize(400, 300);
        MainGameWindow->resize(400, 23);
        centralWidget = new QWidget(MainGameWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainGameWindow->setCentralWidget(centralWidget);

        retranslateUi(MainGameWindow);

        QMetaObject::connectSlotsByName(MainGameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainGameWindow)
    {
        MainGameWindow->setWindowTitle(QCoreApplication::translate("MainGameWindow", "MineSweeper by Weiyi-Zeng", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainGameWindow: public Ui_MainGameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINGAMEWINDOW_H
