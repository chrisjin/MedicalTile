/********************************************************************************
** Form generated from reading UI file 'QAMYWindow.ui'
**
** Created: Wed Mar 11 01:37:36 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QAMYWINDOW_H
#define UI_QAMYWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QAMYWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QAMYWindow)
    {
        if (QAMYWindow->objectName().isEmpty())
            QAMYWindow->setObjectName(QString::fromUtf8("QAMYWindow"));
        QAMYWindow->resize(400, 300);
        menuBar = new QMenuBar(QAMYWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QAMYWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QAMYWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QAMYWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(QAMYWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QAMYWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QAMYWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QAMYWindow->setStatusBar(statusBar);

        retranslateUi(QAMYWindow);

        QMetaObject::connectSlotsByName(QAMYWindow);
    } // setupUi

    void retranslateUi(QMainWindow *QAMYWindow)
    {
        QAMYWindow->setWindowTitle(QApplication::translate("QAMYWindow", "QAMYWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QAMYWindow: public Ui_QAMYWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QAMYWINDOW_H
