/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *loginBtn;
    QLabel *label;
    QLineEdit *username;
    QLineEdit *cardpin;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *digitalClock;
    QLabel *dateTime;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(812, 627);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        loginBtn = new QPushButton(centralwidget);
        loginBtn->setObjectName("loginBtn");
        loginBtn->setGeometry(QRect(350, 320, 161, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(10);
        font.setBold(true);
        loginBtn->setFont(font);
        loginBtn->setStyleSheet(QString::fromUtf8("background-color:rgb(47, 117, 168);\n"
"color: white;\n"
""));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 100, 281, 51));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(16);
        font1.setBold(true);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("\n"
"color: white;\n"
""));
        username = new QLineEdit(centralwidget);
        username->setObjectName("username");
        username->setGeometry(QRect(370, 210, 113, 28));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        username->setFont(font2);
        username->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: rgb(47, 117, 168);\n"
"    color: white;\n"
"    border: none;  /* Ei reunaa normaalissa tilassa */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    background-color: rgb(47, 117, 168);  /* Kentt\303\244 pysyy samassa v\303\244riss\303\244 */\n"
"    border: 2px solid rgb(124, 209, 255);  /* Sininen reunus, kun kentt\303\244 on valittu */\n"
"    cursor: IBeam;  /* Asettaa tekstikursorin kentt\303\244\303\244n */\n"
"}\n"
"\n"
"\n"
"\n"
""));
        username->setFrame(false);
        cardpin = new QLineEdit(centralwidget);
        cardpin->setObjectName("cardpin");
        cardpin->setGeometry(QRect(370, 260, 113, 28));
        cardpin->setFont(font2);
        cardpin->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        cardpin->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: rgb(47, 117, 168);\n"
"    color: white;\n"
"    border: none;  /* Ei reunaa normaalissa tilassa */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    background-color: rgb(47, 117, 168);  /* Kentt\303\244 pysyy samassa v\303\244riss\303\244 */\n"
"    border: 2px solid rgb(124, 209, 255);  /* Sininen reunus, kun kentt\303\244 on valittu */\n"
"    cursor: IBeam;  /* Asettaa tekstikursorin kentt\303\244\303\244n */\n"
"}\n"
"\n"
"\n"
"\n"
""));
        cardpin->setFrame(false);
        cardpin->setEchoMode(QLineEdit::EchoMode::Password);
        cardpin->setCursorMoveStyle(Qt::CursorMoveStyle::VisualMoveStyle);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(-10, -20, 821, 611));
        label_2->setStyleSheet(QString::fromUtf8("background-image: url(:/res/background.jpg);"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(290, 260, 121, 20));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setBold(true);
        label_3->setFont(font3);
        label_3->setStyleSheet(QString::fromUtf8("\n"
"color: white;\n"
""));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(260, 210, 121, 20));
        label_4->setFont(font3);
        label_4->setStyleSheet(QString::fromUtf8("\n"
"color: white;\n"
""));
        digitalClock = new QLabel(centralwidget);
        digitalClock->setObjectName("digitalClock");
        digitalClock->setGeometry(QRect(670, 490, 221, 111));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Ebrima")});
        digitalClock->setFont(font4);
        dateTime = new QLabel(centralwidget);
        dateTime->setObjectName("dateTime");
        dateTime->setGeometry(QRect(670, 500, 121, 51));
        dateTime->setFont(font4);
        MainWindow->setCentralWidget(centralwidget);
        label_2->raise();
        loginBtn->raise();
        label->raise();
        username->raise();
        cardpin->raise();
        label_3->raise();
        label_4->raise();
        digitalClock->raise();
        dateTime->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 812, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        loginBtn->setText(QCoreApplication::translate("MainWindow", "Kirjaudu", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Tervetuloa!", nullptr));
        label_2->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Pin koodi", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Kortin numero", nullptr));
        digitalClock->setText(QCoreApplication::translate("MainWindow", "Clock", nullptr));
        dateTime->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
