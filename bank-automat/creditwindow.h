#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>

namespace Ui {
class creditwindow;
}

class creditwindow : public QDialog
{
    Q_OBJECT

public:
    explicit creditwindow(const QString &idcard, QWidget *parent = nullptr);
    ~creditwindow();

private:
    Ui::creditwindow *ui;
    QString idcard;

private slots:
    void showTime();
};

#endif // CREDITWINDOW_H
