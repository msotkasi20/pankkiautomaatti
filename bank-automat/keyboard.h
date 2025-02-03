#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>

class keyboard : public QWidget
{
    Q_OBJECT
public:
    explicit keyboard(QLineEdit *targetField, QWidget *parent = nullptr);

signals:

private slots:
    void keyPressed();

private:
    QLineEdit *targetField;
};

#endif // KEYBOARD_H
