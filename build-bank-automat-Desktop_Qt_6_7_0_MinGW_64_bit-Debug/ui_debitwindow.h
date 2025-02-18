/********************************************************************************
** Form generated from reading UI file 'debitwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBITWINDOW_H
#define UI_DEBITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_debitwindow
{
public:
    QLabel *label;
    QLabel *digitalClock;
    QLabel *dateTime;
    QWidget *actionsWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *nostoBtn;
    QPushButton *balanceBtn;
    QPushButton *tilitapahtumatBtn;
    QPushButton *logoutBtn;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QPushButton *kakskytBtn;
    QPushButton *nelkytBtn;
    QPushButton *viiskytBtn;
    QPushButton *sataBtn;
    QPushButton *muuBtn;
    QPushButton *withdrawBtn;
    QLineEdit *nostoSumma;
    QLabel *uusiBalance;
    QTableView *tilitapahtumatView;
    QWidget *page_3;
    QWidget *page_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLabel *balance;

    void setupUi(QDialog *debitwindow)
    {
        if (debitwindow->objectName().isEmpty())
            debitwindow->setObjectName("debitwindow");
        debitwindow->resize(800, 600);
        debitwindow->setStyleSheet(QString::fromUtf8("background-image: url(:/res/background.jpg);"));
        label = new QLabel(debitwindow);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 111, 20));
        digitalClock = new QLabel(debitwindow);
        digitalClock->setObjectName("digitalClock");
        digitalClock->setGeometry(QRect(630, 490, 221, 111));
        QFont font;
        font.setFamilies({QString::fromUtf8("Ebrima")});
        digitalClock->setFont(font);
        dateTime = new QLabel(debitwindow);
        dateTime->setObjectName("dateTime");
        dateTime->setGeometry(QRect(630, 490, 61, 51));
        dateTime->setFont(font);
        actionsWidget = new QWidget(debitwindow);
        actionsWidget->setObjectName("actionsWidget");
        actionsWidget->setGeometry(QRect(100, 190, 161, 181));
        verticalLayout = new QVBoxLayout(actionsWidget);
        verticalLayout->setObjectName("verticalLayout");
        nostoBtn = new QPushButton(actionsWidget);
        nostoBtn->setObjectName("nostoBtn");

        verticalLayout->addWidget(nostoBtn);

        balanceBtn = new QPushButton(actionsWidget);
        balanceBtn->setObjectName("balanceBtn");

        verticalLayout->addWidget(balanceBtn);

        tilitapahtumatBtn = new QPushButton(actionsWidget);
        tilitapahtumatBtn->setObjectName("tilitapahtumatBtn");

        verticalLayout->addWidget(tilitapahtumatBtn);

        logoutBtn = new QPushButton(actionsWidget);
        logoutBtn->setObjectName("logoutBtn");

        verticalLayout->addWidget(logoutBtn);

        stackedWidget = new QStackedWidget(debitwindow);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(390, 140, 321, 261));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 255));"));
        page = new QWidget();
        page->setObjectName("page");
        verticalLayoutWidget = new QWidget(page);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 34, 95, 181));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        kakskytBtn = new QPushButton(verticalLayoutWidget);
        kakskytBtn->setObjectName("kakskytBtn");

        verticalLayout_3->addWidget(kakskytBtn);

        nelkytBtn = new QPushButton(verticalLayoutWidget);
        nelkytBtn->setObjectName("nelkytBtn");

        verticalLayout_3->addWidget(nelkytBtn);

        viiskytBtn = new QPushButton(verticalLayoutWidget);
        viiskytBtn->setObjectName("viiskytBtn");

        verticalLayout_3->addWidget(viiskytBtn);

        sataBtn = new QPushButton(verticalLayoutWidget);
        sataBtn->setObjectName("sataBtn");

        verticalLayout_3->addWidget(sataBtn);

        muuBtn = new QPushButton(verticalLayoutWidget);
        muuBtn->setObjectName("muuBtn");

        verticalLayout_3->addWidget(muuBtn);

        withdrawBtn = new QPushButton(page);
        withdrawBtn->setObjectName("withdrawBtn");
        withdrawBtn->setGeometry(QRect(130, 220, 51, 29));
        nostoSumma = new QLineEdit(page);
        nostoSumma->setObjectName("nostoSumma");
        nostoSumma->setGeometry(QRect(10, 220, 113, 28));
        uusiBalance = new QLabel(page);
        uusiBalance->setObjectName("uusiBalance");
        uusiBalance->setGeometry(QRect(190, 220, 81, 31));
        stackedWidget->addWidget(page);
        tilitapahtumatView = new QTableView();
        tilitapahtumatView->setObjectName("tilitapahtumatView");
        stackedWidget->addWidget(tilitapahtumatView);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        horizontalLayoutWidget = new QWidget(page_2);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(40, 90, 241, 81));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        balance = new QLabel(horizontalLayoutWidget);
        balance->setObjectName("balance");

        horizontalLayout->addWidget(balance);

        stackedWidget->addWidget(page_2);

        retranslateUi(debitwindow);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(debitwindow);
    } // setupUi

    void retranslateUi(QDialog *debitwindow)
    {
        debitwindow->setWindowTitle(QCoreApplication::translate("debitwindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("debitwindow", "Debit account", nullptr));
        digitalClock->setText(QCoreApplication::translate("debitwindow", "Clock", nullptr));
        dateTime->setText(QCoreApplication::translate("debitwindow", "Date", nullptr));
        nostoBtn->setText(QCoreApplication::translate("debitwindow", "Nosto", nullptr));
        balanceBtn->setText(QCoreApplication::translate("debitwindow", "N\303\244yt\303\244 saldo", nullptr));
        tilitapahtumatBtn->setText(QCoreApplication::translate("debitwindow", "Tilitapahtumat", nullptr));
        logoutBtn->setText(QCoreApplication::translate("debitwindow", "Kirjaudu ulos", nullptr));
        kakskytBtn->setText(QCoreApplication::translate("debitwindow", "20", nullptr));
        nelkytBtn->setText(QCoreApplication::translate("debitwindow", "40", nullptr));
        viiskytBtn->setText(QCoreApplication::translate("debitwindow", "50", nullptr));
        sataBtn->setText(QCoreApplication::translate("debitwindow", "100", nullptr));
        muuBtn->setText(QCoreApplication::translate("debitwindow", "Muu", nullptr));
        withdrawBtn->setText(QCoreApplication::translate("debitwindow", "Nosta", nullptr));
        uusiBalance->setText(QString());
        label_3->setText(QCoreApplication::translate("debitwindow", "Saldo:", nullptr));
        balance->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class debitwindow: public Ui_debitwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBITWINDOW_H
