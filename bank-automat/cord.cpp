#include "cord.h"
#include "ui_cord.h"
#include <QTimer>
#include <QDateTime>


CorD::CorD(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CorD)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer -> start();

    QDateTime dateTime = QDateTime::currentDateTime();
    QString datetimetext=dateTime.toString();
    ui->dateTime->setText(datetimetext);
}

CorD::~CorD()
{
    delete ui;
}

void CorD::showTime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->digitalClock->setText(time_text);
}
