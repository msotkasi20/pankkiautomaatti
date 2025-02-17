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
#include <QThread>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QTableView>


creditwindow::creditwindow(const QString &idcard, QWidget *parent)
    : QDialog(parent)
    , virtualKeyboard(nullptr)
    , ui(new Ui::creditwindow)
    , idcard(idcard)
    , creditlimit(0.0)
    , idaccount(idaccount)
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
    connect(ui->tilitapahtumatBtn, &QPushButton::clicked, this, &creditwindow::fetchTransactions);

    connect(ui->creditlimitBtn, &QPushButton::clicked, this, &creditwindow::showPage3);
    connect(ui->logoutBtn, &QPushButton::clicked, this, &creditwindow::logOut);

    ui->muuBtn->installEventFilter(this);

    ui->nostoSumma->installEventFilter(this);

    connect(ui->kakskytBtn, &QPushButton::clicked, this, [this]() { setSum(20); });
    connect(ui->nelkytBtn, &QPushButton::clicked, this, [this]() { setSum(40); });
    connect(ui->viiskytBtn, &QPushButton::clicked, this, [this]() { setSum(50); });
    connect(ui->sataBtn, &QPushButton::clicked, this, [this]() { setSum(100); });
    connect(ui->withdrawBtn, &QPushButton::clicked, this, [this]() {
        int amount = ui->nostoSumma->text().toInt();
        creditWithdraw(amount);
        fetchTransactions();
    });


}



creditwindow::~creditwindow()
{
    delete ui;
    delete virtualKeyboard;
}

void creditwindow::updatebalancedisplay()
{
    ui->creditlimit->clear();
    ui->creditlimit->setText(QString::number(creditlimit,'f',2));
}

void creditwindow::creditWithdraw(int amount)
{

    if (amount % 10 == 0){
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url(QString("http://localhost:3000/transaction"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject payload;
    payload["amount"] = amount;
    payload["idaccounts"] = idaccount;
    payload["action"] = "withdraw";
    QJsonDocument jsonDoc(payload);

    QNetworkReply *reply = manager->post(request, jsonDoc.toJson());


    ui->uusicreditlimit->setText("Nostit: " + QString::number(amount));

     QTimer::singleShot(500, this, &creditwindow::fetchCreditAccount);

    } else {
        QMessageBox nostoError;
        nostoError.setText("Nostettava summa kymmenen euron tarkkuudella");
        nostoError.exec();
    }
    qDebug() << "working version";

}

void creditwindow::setSum(int amount)
{
    ui->nostoSumma->setText(QString::number(amount));
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

                // Päivitetään creditlimit ja idaccount
                this->creditlimit = accountData.value("creditlimit").toDouble();
                this->idaccount = accountData.value("idaccounts").toInt();

                // Debug-tulosteet
                qDebug() << "Fetched creditlimit: " << creditlimit;
                qDebug() << "Fetched idaccount: " << idaccount;

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

void creditwindow::fetchTransactions()
{
    qDebug() << idaccount;
    QUrl url(QString("http://localhost:3000/transaction/byAccountId/%1").arg(idaccount));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->get(request);



    connect(reply, &QNetworkReply::finished, this, [reply](){

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

                QStandardItemModel *transactionModel = new QStandardItemModel(this);
                transactionModel->setHorizontalHeaderLabels({"Määrä", "Päivämäärä"});

                for (int i = dataArray.size() - 1; i >= 0; --i) {
                    QJsonValue value = dataArray[i];
                    if (value.isObject()) {
                        QJsonObject transaction = value.toObject();

                        double amount = transaction["amount"].toDouble();
                        QString date = transaction["actiontimestamp"].toString();

                        QList<QStandardItem *> rowItems;
                        rowItems.append(new QStandardItem(QString::number(amount, 'f', 2)));
                        rowItems.append(new QStandardItem(date));

                        transactionModel->appendRow(rowItems);

                    }
                }
                QTableView *tableView = qobject_cast<QTableView *>(ui->tilitapahtumatView);
                if(tableView) {
                    tableView->setModel(transactionModel);

                    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                }
            } else {
                qDebug() << "Error: Transaction fetch failed.";

            }
            reply->deleteLater();
        }
     });
}



void creditwindow::resetInactivityTimer()
{
    inactivityTimer->start(); //Restarttaa ajastimen (30 sek)
    qDebug() << "Timer restarted.";
}

void creditwindow::closeDueToInactivity()
{
    qDebug() << "Closing due to inactivity.";
    close();
    QMessageBox logout;
    logout.setText("Sinut on kirjattu ulos\nKirjaudu sisään uudelleen");
    logout.exec();
}


bool creditwindow::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseMove || event->type() == QEvent::KeyPress) {        //Jos liikutetaan hiirtä tai painetaan näppäintä ajastin resettaa.
        qDebug() << "Liikettä tunnistettu.";
        resetInactivityTimer(); //Kutsutaan funktiota resetInactivityTimer
    }

    if (obj == ui->muuBtn && event->type() == QEvent::MouseButtonPress)
    {
        ui->nostoSumma->setFocus();
        virtualKeyboard->setTargetField(ui->nostoSumma);
        return true;

    }

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




