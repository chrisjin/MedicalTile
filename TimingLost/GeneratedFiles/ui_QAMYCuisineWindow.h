/********************************************************************************
** Form generated from reading UI file 'QAMYCuisineWindow.ui'
**
** Created: Fri Mar 21 11:15:41 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QAMYCUISINEWINDOW_H
#define UI_QAMYCUISINEWINDOW_H

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

class Ui_QAMYCuisineWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QAMYCuisineWindow)
    {
        if (QAMYCuisineWindow->objectName().isEmpty())
            QAMYCuisineWindow->setObjectName(QString::fromUtf8("QAMYCuisineWindow"));
        QAMYCuisineWindow->resize(400, 300);
        menuBar = new QMenuBar(QAMYCuisineWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QAMYCuisineWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QAMYCuisineWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QAMYCuisineWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(QAMYCuisineWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QAMYCuisineWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QAMYCuisineWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QAMYCuisineWindow->setStatusBar(statusBar);

        retranslateUi(QAMYCuisineWindow);

        QMetaObject::connectSlotsByName(QAMYCuisineWindow);
    } // setupUi

    void retranslateUi(QMainWindow *QAMYCuisineWindow)
    {
        QAMYCuisineWindow->setWindowTitle(QApplication::translate("QAMYCuisineWindow", "QAMYCuisineWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QAMYCuisineWindow: public Ui_QAMYCuisineWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QAMYCUISINEWINDOW_H
