#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include "keyboard.h"

class keyboard;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    keyboard *virtualKeyboard;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::MainWindow *ui;
    int loginCounter = 0;

    void lockCard(int idcard);

private slots:
    void showTime();
    void on_loginBtn_clicked();
    void showKeyboard(QLineEdit *targetField);
};
#endif // MAINWINDOW_H