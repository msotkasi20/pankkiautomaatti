#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QTimer>

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

    QTimer *inactivityTimer;
    void resetInactivityTimer();
    void closeDueToInactivity();
    keyboard *virtualKeyboard;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void showTime();
};

#endif // CREDITWINDOW_H
