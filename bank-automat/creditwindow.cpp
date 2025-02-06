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
    , virtualKeyboard(nullptr)
    , ui(new Ui::creditwindow)
    , idcard(idcard)
    , creditlimit(0.0)
    , networkManager(new QNetworkAccessManager(this))
    , inactivityTimer(new QTimer(this))
{
    qDebug() << "creditwindow created with idcard: " << idcard;

    ui->setupUi(this);


    virtualKeyboard = new keyboard(nullptr, this);
    virtualKeyboard->move(440,200);
    virtualKeyboard->show();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer -> start();

    QDateTime dateTime = QDateTime::currentDateTime();
    QString datetimetext=dateTime.toString();
    ui->dateTime->setText(datetimetext);

    inactivityTimer->setInterval(30000); // 30 sekunttia
    connect(inactivityTimer, &QTimer::timeout, this, &creditwindow::closeDueToInactivity);
    inactivityTimer->start();

    this->installEventFilter(this);

    fetchCreditAccount();

    connect(ui->nostoBtn, &QPushButton::clicked, this, &creditwindow::showPage1);
    connect(ui->tilitapahtumatBtn, &QPushButton::clicked, this, &creditwindow::showPage2);
    connect(ui->creditlimitBtn, &QPushButton::clicked, this, &creditwindow::showPage3);
    connect(ui->logoutBtn, &QPushButton::clicked, this, &creditwindow::logOut);

    ui->muuBtn->installEventFilter(this);

    ui->muuSumma->installEventFilter(this);



creditwindow::~creditwindow()
{
    delete ui;
    delete virtualKeyboard;
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

void creditwindow::resetInactivityTimer()
{
    inactivityTimer->start(); //Restarttaa ajastimen (30 sek)
}

void creditwindow::closeDueToInactivity()
{
    qDebug() << "Closing due to inactivity.";
    close();
}


bool creditwindow::eventFilter(QObject *obj, QEvent *event)
{

    if(event->type() == QEvent::MouseMove || event->type() == QEvent::KeyPress) {        //Jos liikutetaan hiirtä tai painetaan näppäintä ajastin resettaa.
        resetInactivityTimer(); //Kutsutaan funktiota resetInactivityTimer
    }

    if (obj == ui->muuBtn && event->type() == QEvent::MouseButtonPress)
    {
        ui->muuSumma->setFocus();
        virtualKeyboard->setTargetField(ui->muuSumma);
        return true;

    }

    // if (ui->muuBtn && event->type() == QEvent::MouseButtonPress)
    // {
    //     virtualKeyboard->show();
    //     ui->muuSumma->setFocus();
    //     return true;

    // }
    return QDialog::eventFilter(obj, event);


}

void creditwindow::showTime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->digitalClock->setText(time_text);
}

void creditwindow::showPage1()
{
    ui->stackedWidget->setCurrentIndex(0); //Näyttää "Nosto" sivun

    virtualKeyboard->show();


}

void creditwindow::showPage2()
{
    ui->stackedWidget->setCurrentIndex(1);

    virtualKeyboard->close();

}

void creditwindow::showPage3()
{
    ui->stackedWidget->setCurrentIndex(2);

    virtualKeyboard->close();


}

void creditwindow::logOut()
{
    inactivityTimer->stop();
    qDebug() << "logoutBtn clicked.";
    close();
}


