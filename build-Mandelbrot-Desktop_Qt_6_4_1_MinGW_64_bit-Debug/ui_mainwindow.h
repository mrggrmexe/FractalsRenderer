/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *MainLabel;
    QWidget *glow;
    QWidget *widget;
    QPushButton *pushButton;
    QLabel *MainLabel_2;
    QLineEdit *lineEdit;
    QLabel *MainLabel_3;
    QWidget *widget_2;
    QLabel *MainLabel_4;
    QLabel *MainLabel_5;
    QLabel *MainLabel_6;
    QLabel *MainLabel_7;
    QLabel *MainLabel_8;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *widget_3;
    QGraphicsView *myView;
    QWidget *kostil;
    QWidget *choose;
    QLabel *label_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1042, 625);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 2, 10);"));
        MainLabel = new QLabel(centralwidget);
        MainLabel->setObjectName("MainLabel");
        MainLabel->setGeometry(QRect(55, 10, 171, 31));
        QFont font;
        font.setPointSize(24);
        MainLabel->setFont(font);
        MainLabel->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        glow = new QWidget(centralwidget);
        glow->setObjectName("glow");
        glow->setGeometry(QRect(40, 550, 0, 3));
        glow->setStyleSheet(QString::fromUtf8("background-color: rgb(108, 173, 255);"));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(40, 70, 300, 211));
        widget->setStyleSheet(QString::fromUtf8("border-width: 5px;\n"
"border-radius: 10px;\n"
"border: rgb(150,150, 150);\n"
"border-width: 1px;\n"
"background-color: rgb(15, 15, 25);"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 150, 261, 41));
        QFont font1;
        font1.setPointSize(22);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("background:rgb(146, 150, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-color: rgb(0, 0, 0);\n"
"border-width: 5px;\n"
"border-radius: 10px;\n"
"border-color:rgb(146, 150, 255);"));
        MainLabel_2 = new QLabel(widget);
        MainLabel_2->setObjectName("MainLabel_2");
        MainLabel_2->setGeometry(QRect(19, 15, 261, 31));
        QFont font2;
        font2.setPointSize(18);
        MainLabel_2->setFont(font2);
        MainLabel_2->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(70, 80, 201, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("border-width: 10px;\n"
"border-radius: 10px;\n"
"border: rgb(50,50, 50);\n"
"border-style: solid;\n"
"border-width: 2px;\n"
"background-color: rgb(0, 0, 0);\n"
"color: rgb(211, 224, 255);"));
        MainLabel_3 = new QLabel(widget);
        MainLabel_3->setObjectName("MainLabel_3");
        MainLabel_3->setGeometry(QRect(25, 83, 31, 31));
        QFont font3;
        font3.setPointSize(37);
        MainLabel_3->setFont(font3);
        MainLabel_3->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(40, 300, 300, 230));
        widget_2->setStyleSheet(QString::fromUtf8("border-width: 5px;\n"
"border-radius: 10px;\n"
"border: rgb(150,150, 150);\n"
"border-width: 1px;\n"
"background-color: rgb(15, 15, 25);"));
        MainLabel_4 = new QLabel(widget_2);
        MainLabel_4->setObjectName("MainLabel_4");
        MainLabel_4->setGeometry(QRect(19, 15, 191, 31));
        MainLabel_4->setFont(font2);
        MainLabel_4->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        MainLabel_5 = new QLabel(widget_2);
        MainLabel_5->setObjectName("MainLabel_5");
        MainLabel_5->setGeometry(QRect(20, 80, 61, 31));
        MainLabel_5->setFont(font2);
        MainLabel_5->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        MainLabel_6 = new QLabel(widget_2);
        MainLabel_6->setObjectName("MainLabel_6");
        MainLabel_6->setGeometry(QRect(20, 110, 111, 31));
        MainLabel_6->setFont(font2);
        MainLabel_6->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        MainLabel_7 = new QLabel(widget_2);
        MainLabel_7->setObjectName("MainLabel_7");
        MainLabel_7->setGeometry(QRect(20, 140, 101, 31));
        MainLabel_7->setFont(font2);
        MainLabel_7->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        MainLabel_8 = new QLabel(widget_2);
        MainLabel_8->setObjectName("MainLabel_8");
        MainLabel_8->setGeometry(QRect(20, 170, 101, 31));
        MainLabel_8->setFont(font2);
        MainLabel_8->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setGeometry(QRect(160, 80, 131, 31));
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 110, 121, 31));
        label_2->setFont(font2);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(160, 140, 101, 31));
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        label_4 = new QLabel(widget_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(160, 170, 131, 31));
        label_4->setFont(font2);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(355, 70, 600, 460));
        widget_3->setStyleSheet(QString::fromUtf8("border-width: 5px;\n"
"border-radius: 10px;\n"
"border: rgb(150,150, 150);\n"
"border-width: 1px;\n"
"background-color: rgb(15, 15, 25);"));
        myView = new QGraphicsView(widget_3);
        myView->setObjectName("myView");
        myView->setGeometry(QRect(20, 20, 560, 420));
        myView->setStyleSheet(QString::fromUtf8("border-width: 5px;\n"
"border-radius: 10px;\n"
""));
        kostil = new QWidget(widget_3);
        kostil->setObjectName("kostil");
        kostil->setGeometry(QRect(20, 20, 560, 420));
        kostil->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 73, 89);"));
        choose = new QWidget(centralwidget);
        choose->setObjectName("choose");
        choose->setGeometry(QRect(-800, -800, 120, 80));
        choose->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(460, 570, 121, 40));
        QFont font4;
        font4.setPointSize(34);
        label_5->setFont(font4);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(211, 224, 255);"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        MainLabel->setText(QCoreApplication::translate("MainWindow", "Mandelbrot", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "build", nullptr));
        MainLabel_2->setText(QCoreApplication::translate("MainWindow", "Set build", nullptr));
        MainLabel_3->setText(QCoreApplication::translate("MainWindow", "n", nullptr));
        MainLabel_4->setText(QCoreApplication::translate("MainWindow", "Information", nullptr));
        MainLabel_5->setText(QCoreApplication::translate("MainWindow", "Scale:", nullptr));
        MainLabel_6->setText(QCoreApplication::translate("MainWindow", "Position:", nullptr));
        MainLabel_7->setText(QCoreApplication::translate("MainWindow", "Black:", nullptr));
        MainLabel_8->setText(QCoreApplication::translate("MainWindow", "Colored:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
