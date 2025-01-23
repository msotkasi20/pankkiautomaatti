#ifndef ACCOUTMAIN_H
#define ACCOUTMAIN_H

#include <QDialog>

namespace Ui {
class accoutmain;
}

class accoutmain : public QDialog
{
    Q_OBJECT

public:
    explicit accoutmain(QWidget *parent = nullptr);
    ~accoutmain();

private:
    Ui::accoutmain *ui;

private slots:
    void showTime();
};

#endif // ACCOUTMAIN_H
