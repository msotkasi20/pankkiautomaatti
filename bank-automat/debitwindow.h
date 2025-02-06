#ifndef DEBITWINDOW_H
#define DEBITWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QTimer>


namespace Ui {
class debitwindow;
}

class debitwindow : public QDialog
{
    Q_OBJECT

public:
    explicit debitwindow(const QString &idcard, QWidget *parent = nullptr);
    ~debitwindow();
    void updatebalancedisplay();

private:
    Ui::debitwindow *ui;
    QString idcard;
    double balance;

    void fetchDebitAccount();
    QNetworkAccessManager *networkManager;

    QTimer *inactivityTimer;
    void resetInactivityTimer();
    void closeDueToInactivity();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void showTime();
};

#endif // DEBITWINDOW_H
