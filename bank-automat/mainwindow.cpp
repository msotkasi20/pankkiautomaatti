#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QInputDialog>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer -> start();

    QDateTime dateTime = QDateTime::currentDateTime();
    QString datetimetext=dateTime.toString();
    ui->dateTime->setText(datetimetext);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->digitalClock->setText(time_text);
}

void MainWindow::on_loginBtn_clicked()
{
    QString idcard = ui->username->text();
    QString cardpin = ui->cardpin->text();

    if(idcard.isEmpty() || cardpin.isEmpty()){
        QMessageBox::warning(this, "Input Error", "Please fill in both fields.");
        return;
    }

    // Prepare the network request
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("http://localhost:3000/login");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //Prepare the JSON payload
    QJsonObject payload;
    payload["idcard"] = idcard;
    payload["cardpin"] = cardpin;
    QJsonDocument jsonDoc(payload);

    // Send the POST request
    QNetworkReply *reply = manager->post(request, jsonDoc.toJson());

    // Connect to the reply signal for handling response
    connect(reply, &QNetworkReply::finished, this, [reply, this, idcard]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Parse the JSON response
            QJsonDocument responseDoc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject responseObj = responseDoc.object();

            bool success = responseObj.value("success").toBool();
            if (success) {
                QString token = responseObj.value("token").toString();
                qDebug() << "Login successful. Token: " << token;

                QNetworkAccessManager *managerForCard = new QNetworkAccessManager(this);
                QUrl cardUrl(QString("http://localhost:3000/card/%1").arg(idcard));
                QNetworkRequest cardRequest(cardUrl);
                cardRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

                QNetworkReply *cardReply = managerForCard->get(cardRequest);

                connect(cardReply, &QNetworkReply::finished, this, [cardReply, this]() {
                    if (cardReply->error() == QNetworkReply::NoError){
                    QByteArray cardResponse = cardReply->readAll();
                    QJsonDocument cardResponseDoc = QJsonDocument::fromJson(cardResponse);
                    QJsonObject cardResponseObj = cardResponseDoc.object();

                    QJsonObject dataObj = cardResponseObj.value("data").toObject();
                    QString cardType = dataObj.value("type").toString();

                    //QString cardType = cardResponseObj.value("type").toString();
                    qDebug() << "Card Type: " << cardType;

                    if (!cardType.isEmpty()){

                    } else {
                        qDebug() << "Card type not found in the response.";
                    }



                if (cardType == "dual") {
                    QStringList options = { "Credit", "Debit" };
                    bool ok = false;
                    QString choice = QInputDialog::getItem(this, "Select Card Type", "Choose Credit or Debit", options, 0, false, &ok);

                    if (ok && !choice.isEmpty()) {
                        qDebug() << "User selected card type: " << choice;

                    } else {
                    qDebug() << "No card type selected.";

                    }

                } else {
                    qDebug() << "Card type: " << cardType;
                }
                } else {
                    QMessageBox::critical(this, "Card Data Error", "Failed to retrieve card data: " + cardReply->errorString());
                }
                cardReply->deleteLater();
                });
            } else {
                 QMessageBox::warning(this, "Login Failed", responseObj.value("message").toString());
            }
        } else {
            QMessageBox::critical(this, "Network Error", "Login request failed: " + reply->errorString());
        }
        reply->deleteLater();

    });

}

