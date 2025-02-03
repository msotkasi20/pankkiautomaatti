#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QJsonArray>

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

private:
    Ui::creditwindow *ui;
    QString idcard;
    double creditlimit;

    void fetchCreditAccount();
    QNetworkAccessManager *networkManager;

private slots:
    void showTime();
};

#endif // CREDITWINDOW_H
