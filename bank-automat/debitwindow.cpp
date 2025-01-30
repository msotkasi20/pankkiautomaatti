#include "debitwindow.h"
#include "ui_debitwindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QInputDialog>
#include <QMessageBox>

debitwindow::debitwindow(const QString &idcard, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::debitwindow)
    , idcard(idcard)
    , networkManager(new QNetworkAccessManager(this))
{
    qDebug() << "debitwindow created with idcard: " << idcard;


    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer -> start();

    QDateTime dateTime = QDateTime::currentDateTime();
    QString datetimetext=dateTime.toString();
    ui->dateTime->setText(datetimetext);

    fetchDebitAccount();

    qDebug() << idcard;
}

debitwindow::~debitwindow()
{
    delete ui;
}

void debitwindow::fetchDebitAccount()
{
 //Haetaan debit-tili
    QUrl url(QString("http://localhost:3000/accounts_cards/by-card-and-type?idcard=%1&type=debit").arg(idcard));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //Lähetetään GET pyyntö
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        if (reply->error() == QNetworkReply::NoError){
            //Parse the JSON response
            QByteArray responseData = reply ->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObj = jsonDoc.object();

            bool success = jsonObj.value("success").toBool();
            if(success) {
                QJsonObject accountData = jsonObj.value("data").toObject();
                QString accountId = accountData.value("idaccounts").toString();
                double balance = accountData.value("balance").toDouble();

                qDebug() << "Full JSON response: " << jsonDoc.toJson();

            } else {
                QMessageBox::warning(this, "Error", jsonObj.value("error").toString());
            }
        } else {
            QMessageBox::critical(this, "Network Error", "Failed to fetch debit account: "+ reply->errorString());
        }
        reply->deleteLater();
    });

}

void debitwindow::showTime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->digitalClock->setText(time_text);
}


