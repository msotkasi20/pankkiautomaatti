#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "debitwindow.h"
#include "creditwindow.h"
#include "keyboard.h"
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
    virtualKeyboard = nullptr;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer -> start();

    QDateTime dateTime = QDateTime::currentDateTime();
    QString datetimetext=dateTime.toString("dd MMMM");
    ui->dateTime->setText(datetimetext);

    ui->username->installEventFilter(this);
    ui->cardpin->installEventFilter(this);   
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(obj);
        if (lineEdit) {
            showKeyboard(lineEdit);
            return true;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::lockCard(int idcard)
{
    qDebug() << "Lukitusfunktio kutsuttu cardid: " << idcard;

    // Luodaan network manager
    QNetworkAccessManager *managerForCard = new QNetworkAccessManager(this);

    // Määritetään URL kortin ID:llä
    QUrl cardUrl(QString("http://localhost:3000/card/%1/lock").arg(idcard));
    QNetworkRequest cardRequest(cardUrl);
    cardRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // JSON payload
    QJsonObject payload;
    payload["locked"] = 1;  // Varmistetaan että vain 'locked' kenttä lähetetään
    QJsonDocument jsonDoc(payload);
    QByteArray requestData = jsonDoc.toJson();  // Muutetaan QByteArrayksi

    // Lähetetään PUT JSON bodyn mukana
    QNetworkReply *cardReply = managerForCard->put(cardRequest, requestData);

    // Käsitellään response asynkronisesti
    connect(cardReply, &QNetworkReply::finished, this, [cardReply]() {
        if (cardReply->error() == QNetworkReply::NoError) {
            QByteArray cardResponse = cardReply->readAll();
            QJsonDocument cardResponseDoc = QJsonDocument::fromJson(cardResponse);
            QJsonObject cardResponseObj = cardResponseDoc.object();

            // Debugataan response
            if (cardResponseObj.contains("data")) {
                QJsonObject dataObj = cardResponseObj.value("data").toObject();
                qDebug() << "Card locked successfully:" << dataObj;
            } else {
                qDebug() << "Unexpected response:" << cardResponseObj;
            }
        } else {
            qDebug() << "Error locking card:" << cardReply->errorString();
        }

        // Muistin tyhjennys
        cardReply->deleteLater();
    });
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

    // Valmistellaan network request
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("http://localhost:3000/login");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //Valmistellaan JSON payload
    QJsonObject payload;
    payload["idcard"] = idcard;
    payload["cardpin"] = cardpin;
    QJsonDocument jsonDoc(payload);

    // Lähetetään POST request
    QNetworkReply *reply = manager->post(request, jsonDoc.toJson());

    // Yhdistä reply-signaaliin vastauksen käsittelemiseksi
    connect(reply, &QNetworkReply::finished, this, [reply, this, idcard]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Parseroi JSON response
            QJsonDocument responseDoc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject responseObj = responseDoc.object();
            qDebug() << "Full JSON Response:" << responseDoc.toJson();

            bool success = responseObj.value("success").toBool();
            if (success) {
                QString token = responseObj.value("token").toString();
                qDebug() << "Login successful. Token: " << token;

                QNetworkAccessManager *managerForCard = new QNetworkAccessManager(this);
                QUrl cardUrl(QString("http://localhost:3000/card/%1").arg(idcard));
                QNetworkRequest cardRequest(cardUrl);
                cardRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

                QNetworkReply *cardReply = managerForCard->get(cardRequest);

                connect(cardReply, &QNetworkReply::finished, this, [cardReply, this, idcard]() {
                    if (cardReply->error() == QNetworkReply::NoError){
                        QByteArray cardResponse = cardReply->readAll();
                        QJsonDocument cardResponseDoc = QJsonDocument::fromJson(cardResponse);
                        QJsonObject cardResponseObj = cardResponseDoc.object();

                        QJsonObject dataObj = cardResponseObj.value("data").toObject();
                        QString cardType = dataObj.value("type").toString();

                        qDebug() << "Card Type: " << cardType;

                        //Valitaan ikkuna joka aukeaa.
                        if (cardType == "credit") {
                            creditwindow *creditWindow = new creditwindow(idcard, this);
                            creditWindow->show();
                        } else if (cardType == "debit") {
                            debitwindow *debitWindow = new debitwindow(idcard, this);
                            debitWindow->show();
                        }

                        //Kysytään kortti tyyppi kun kortti on dual
                        if (cardType == "dual") {
                            QStringList options = { "Credit", "Debit" };
                            bool ok = false;
                            QString choice = QInputDialog::getItem(this, "Select Card Type", "Choose Credit or Debit", options, 0, false, &ok);

                            if (ok && !choice.isEmpty()) {
                                qDebug() << "User selected card type: " << choice;
                                if (choice == "Credit") {
                                    creditwindow *creditWindow = new creditwindow(idcard, this);
                                    creditWindow->show();
                                    clearFields();


                                } else if (choice == "Debit"){
                                    debitwindow *debitWindow = new debitwindow(idcard, this);
                                    debitWindow->show();
                                    clearFields();

                                }

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
                // QMessageBox::warning(this, "Login Failed", responseObj.value("message").toString());
            }
        } else {
            // QMessageBox::critical(this, "Network Error", "Loginxrequest failed: " + reply->errorString());
            int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            qDebug() << "HTTP Status Code:" << statusCode;

            if (statusCode == 401) {
                QMessageBox::warning(this, "Login Failed", "Invalid PIN");

                // Kasvatetaan loginCounteria
                 loginCounter++;
                qDebug() << "Login counter:" << loginCounter;

                // Lukitaan kortti jos 3 epäonnistunutta yritystä
                if (loginCounter >= 3) {
                    int idcardInt = idcard.toInt();
                    lockCard(idcardInt);
                    qDebug() << "Lukittava kortti:" << idcardInt;
                }
            } else if (statusCode == 403) {
                QMessageBox::critical(this, "Card Locked", "Your cards is locked. Please contact customer support");
            }
        }

        reply->deleteLater();
    });
}

void MainWindow::clearFields() {
    ui->username->clear();
    ui->cardpin->clear();
}



void MainWindow::showKeyboard(QLineEdit *targetField)
{
    if (virtualKeyboard) {
        virtualKeyboard->close();
        virtualKeyboard->deleteLater();
        virtualKeyboard = nullptr;
    }
    targetField->setFocus();
    QCoreApplication::processEvents();

    virtualKeyboard = new keyboard(targetField, this);
    virtualKeyboard->move(550, 195); //Asettaa näppäimistölle paikan näytöllä
    virtualKeyboard->show();
    virtualKeyboard->raise();
}