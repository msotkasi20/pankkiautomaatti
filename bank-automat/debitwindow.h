#ifndef DEBITWINDOW_H
#define DEBITWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>

namespace Ui {
class debitwindow;
}

class debitwindow : public QDialog
{
    Q_OBJECT

public:
    explicit debitwindow(const QString &idcard, QWidget *parent = nullptr);
    ~debitwindow();

private:
    Ui::debitwindow *ui;
    QString idcard;

    void fetchDebitAccount();
    QNetworkAccessManager *networkManager;

private slots:
    void showTime();
};

#endif // DEBITWINDOW_H
