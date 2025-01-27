#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
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
    connect(reply, &QNetworkReply::finished, this, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Parse the JSON response
            QJsonDocument responseDoc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject responseObj = responseDoc.object();

            bool success = responseObj.value("success").toBool();
            if (success) {
                QString token = responseObj.value("token").toString();
                QMessageBox::information(this, "Login Success", "Authentication succeeded.");
                // Save token or proceed to the main application
            } else {
                QString message = responseObj.value("message").toString();
                QMessageBox::warning(this, "Login Failed", message);
            }
        } else {
            QMessageBox::critical(this, "Network Error", reply->errorString());
        }
        reply->deleteLater();
    });
}

