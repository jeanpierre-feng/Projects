/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *layout_scene;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    //Buttons
    QPushButton *QuitButton;
    QPushButton *ResetButton ;
    QPushButton *EraseButton;
    QPushButton *PathWidthButton ;
    QPushButton *PathDeepButton ;
    QPushButton *DijkstraButton ;
    QPushButton *AStarButton;

    //Labels
    QLabel *PathWidthLabel;
    QLabel *PathWidthTimer;

    QLabel *PathDeepLabel;
    QLabel *PathDeepTimer;

    QLabel *DijkstraLabel;
    QLabel *DijkstraTimer;


    QLabel *AStarLabel;
    QLabel *AStarTimer;



    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(758, 475);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QuitButton = new QPushButton(centralwidget);
        QuitButton->setObjectName(QString::fromUtf8("QuitButton"));
        QuitButton->setGeometry(QRect(640, 390, 80, 20));

        ResetButton = new QPushButton(centralwidget);
        ResetButton->setObjectName(QString::fromUtf8("ResetButton"));
        ResetButton->setGeometry(QRect(640, 410, 80, 20));

        EraseButton = new QPushButton(centralwidget);
        EraseButton->setObjectName(QString::fromUtf8("EraseButton"));
        EraseButton->setGeometry(QRect(640, 430, 80, 20));

        PathWidthButton = new QPushButton(centralwidget);
        PathWidthButton ->setObjectName(QString::fromUtf8("PathWidthButton"));
        PathWidthButton ->setGeometry(QRect(40, 390, 92, 27));

        PathDeepButton = new QPushButton(centralwidget);
        PathDeepButton ->setObjectName(QString::fromUtf8("PathDeepButton"));
        PathDeepButton ->setGeometry(QRect(40, 420, 92, 27));

        DijkstraButton = new QPushButton(centralwidget);
        DijkstraButton ->setObjectName(QString::fromUtf8("DijkstraButton"));
        DijkstraButton ->setGeometry(QRect(140, 390, 92, 27));

        AStarButton = new QPushButton(centralwidget);
        AStarButton ->setObjectName(QString::fromUtf8("AStarButton"));
        AStarButton ->setGeometry(QRect(140, 420, 92, 27));

        PathWidthLabel = new QLabel(centralwidget);
        PathWidthLabel ->setObjectName(QString::fromUtf8("PathWidthLabel"));
        PathWidthLabel ->setGeometry(QRect(340, 390, 110, 13));

        PathWidthTimer = new QLabel(centralwidget);
        PathWidthTimer ->setObjectName(QString::fromUtf8("PathWidthTimer"));
        PathWidthTimer ->setGeometry(QRect(340, 403, 92, 13));

        PathDeepLabel = new QLabel(centralwidget);
        PathDeepLabel ->setObjectName(QString::fromUtf8("PathDeepLabel"));
        PathDeepLabel ->setGeometry(QRect(340, 420, 110, 13));

        PathDeepTimer = new QLabel(centralwidget);
        PathDeepTimer ->setObjectName(QString::fromUtf8("PathDeepTimer"));
        PathDeepTimer ->setGeometry(QRect(340, 433, 92, 13));

        DijkstraLabel = new QLabel(centralwidget);
        DijkstraLabel ->setObjectName(QString::fromUtf8("DijkstraLabel"));
        DijkstraLabel ->setGeometry(QRect(460, 390, 110, 13));

        DijkstraTimer = new QLabel(centralwidget);
        DijkstraTimer ->setObjectName(QString::fromUtf8("DijkstraTimer"));
        DijkstraTimer ->setGeometry(QRect(460, 403, 92, 13));

        AStarLabel = new QLabel(centralwidget);
        AStarLabel ->setObjectName(QString::fromUtf8("AStarLabel"));
        AStarLabel ->setGeometry(QRect(460, 420, 110, 13));

        AStarTimer = new QLabel(centralwidget);
        AStarTimer ->setObjectName(QString::fromUtf8("AStarTimer"));
        AStarTimer ->setGeometry(QRect(460, 433, 92, 13));

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 20, 721, 351));
        layout_scene = new QVBoxLayout(verticalLayoutWidget);
        layout_scene->setObjectName(QString::fromUtf8("layout_scene"));
        layout_scene->setContentsMargins(0, 0, 0, 0);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 758, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        QuitButton->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        ResetButton->setText(QApplication::translate("MainWindow", "Reset/Restart", nullptr));
        EraseButton->setText(QApplication::translate("MainWindow", "Erase", nullptr));

        PathWidthButton->setText(QApplication::translate("MainWindow", "Path Width (4)", nullptr));
        PathDeepButton->setText(QApplication::translate("MainWindow", "Path Deep", nullptr));
        DijkstraButton->setText(QApplication::translate("MainWindow", "Dijkstra", nullptr));
        AStarButton->setText(QApplication::translate("MainWindow", "Path Width (8)", nullptr));

        PathWidthLabel->setText(QApplication::translate("MainWindow", "Path Width (4) Timer :", nullptr));
        PathDeepLabel->setText(QApplication::translate("MainWindow", "Path Deep Timer :", nullptr));
        DijkstraLabel->setText(QApplication::translate("MainWindow", "Dijkstra Timer :", nullptr));
        AStarLabel->setText(QApplication::translate("MainWindow", "Path Width (8) Timer :", nullptr));

        PathWidthTimer->setText(QApplication::translate("MainWindow", "****", nullptr));
        PathDeepTimer->setText(QApplication::translate("MainWindow", "****", nullptr));
        DijkstraTimer->setText(QApplication::translate("MainWindow", "****", nullptr));
        AStarTimer->setText(QApplication::translate("MainWindow", "****", nullptr));




    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
