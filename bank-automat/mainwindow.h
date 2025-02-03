#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    keyboard *keyboard;

private:
    Ui::MainWindow *ui;

private slots:
    void showTime();
    void on_loginBtn_clicked();
    void showKeyboard(QLineEdit *targetField);
};
#endif // MAINWINDOW_H
