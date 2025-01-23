#include "accoutmain.h"
#include "ui_accoutmain.h"
#include <QTimer>
#include <QDateTime>


accoutmain::accoutmain(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::accoutmain)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer -> start();

    QDateTime dateTime = QDateTime::currentDateTime();
    QString datetimetext=dateTime.toString();
    ui->dateTime->setText(datetimetext);
}

accoutmain::~accoutmain()
{
    delete ui;
}

void accoutmain::showTime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->digitalClock->setText(time_text);
}
