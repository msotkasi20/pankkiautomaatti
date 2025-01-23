#ifndef CORD_H
#define CORD_H

#include <QDialog>

namespace Ui {
class CorD;
}

class CorD : public QDialog
{
    Q_OBJECT

public:
    explicit CorD(QWidget *parent = nullptr);
    ~CorD();

private:
    Ui::CorD *ui;

private slots:
    void showTime();
};

#endif // CORD_H
