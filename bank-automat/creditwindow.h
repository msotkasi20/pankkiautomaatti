#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QTimer>
#include <QPushButton>
#include <QWidget>
#include <QStandardItemModel>
#include "keyboard.h"

class keyboard;

namespace Ui {
class creditwindow;
}

class creditwindow : public QDialog
{
    Q_OBJECT

public:
    explicit creditwindow(const QString &idcard, QWidget *parent = nullptr);
    ~creditwindow();
    void updatebalancedisplay();
    void creditWithdraw(int amount);
    void setSum(int amount);

    keyboard *virtualKeyboard;

private:
    Ui::creditwindow *ui;
    QString idcard;
    double creditlimit;
    int idaccount;
    int amount;

    void fetchCreditAccount();
    void fetchTransactions();
    QNetworkAccessManager *networkManager;

    QTimer *inactivityTimer;
    void resetInactivityTimer();
    void closeDueToInactivity();

    QList<QPair<QString, QString>> allTransactions;
    int currentPage = 0;   // Tracks the current page number
    int rowsPerPage = 10;  // Defines how many rows per page

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void showTime();
    void showPage1();
    void showPage2();
    void showPage3();
    void logOut();
    void updateTableView();
    void nextPage();
    void prevPage();
};

#endif // CREDITWINDOW_H