#include "creditwindow.h"
#include "ui_creditwindow.h"
#include <QTimer>
#include <QDateTime>

creditwindow::creditwindow(const QString &idcard, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creditwindow)
    , idcard(idcard){
    qDebug() << "creditwindow created with idcard: " << idcard;

    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer -> start();

    QDateTime dateTime = QDateTime::currentDateTime();
    QString datetimetext=dateTime.toString();
    ui->dateTime->setText(datetimetext);
}

creditwindow::~creditwindow()
{
    delete ui;
}

void creditwindow::showTime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->digitalClock->setText(time_text);
}
