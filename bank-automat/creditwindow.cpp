#include "creditwindow.h"
#include "ui_creditwindow.h"
#include <QTimer>
#include <QDateTime>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QInputDialog>
#include <QMessageBox>

creditwindow::creditwindow(const QString &idcard, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creditwindow)
    , idcard(idcard)
    , creditlimit(0.0)
    , networkManager(new QNetworkAccessManager(this))
{
    qDebug() << "creditwindow created with idcard: " << idcard;

    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer -> start();

    QDateTime dateTime = QDateTime::currentDateTime();
    QString datetimetext=dateTime.toString();
    ui->dateTime->setText(datetimetext);

    fetchCreditAccount();
}

creditwindow::~creditwindow()
{
    delete ui;
}

void creditwindow::updatebalancedisplay()
{
    ui->creditlimit->setText(QString::number(creditlimit,'f',2));
}

void creditwindow::fetchCreditAccount()
{
    QUrl url(QString("http://localhost:3000/accounts_cards/by-card-and-type?idcard=%1&type=credit").arg(idcard));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        if (reply->error() == QNetworkReply::NoError){
            //Parse the JSON response
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObj = jsonDoc.object();

            qDebug() << "Full JSON response: " << jsonDoc.toJson(QJsonDocument::Indented);

            bool success = jsonObj.value("success").toBool();
            if (success) {
                // Tarkistetaan että "data" on array
                if (!jsonObj.contains("data") || !jsonObj["data"].isArray()) {
                    qDebug() << "Error: 'data' field is missing or is not an array.";
                    return;
                }

                QJsonArray dataArray = jsonObj["data"].toArray();
                if (dataArray.isEmpty()) {
                    qDebug() << "Error: 'data' array is empty.";
                    return;
                }

                // Haetaan ensimmäinen objekti taulukosta
                QJsonObject accountData = dataArray.first().toObject();

                // Päivitetään balance
                this->creditlimit = accountData.value("creditlimit").toDouble();

                // Debug-tulosteet
                qDebug() << "Fetched creditlimit: " << creditlimit;

                // Päivitetään UI
                updatebalancedisplay();

            } else {
                QMessageBox::warning(this, "Error", jsonObj.value("error").toString());
            }
        } else {
            QMessageBox::critical(this, "Network Error", "Failed to fetch credit account: "+ reply->errorString());
        }
        reply->deleteLater();
    });
}

void creditwindow::showTime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->digitalClock->setText(time_text);
}
