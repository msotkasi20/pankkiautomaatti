#include "debitwindow.h"
#include "ui_debitwindow.h"
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


debitwindow::debitwindow(const QString &idcard, QWidget *parent)
    : QDialog(parent)
    , virtualKeyboard(nullptr)
    , ui(new Ui::debitwindow)
    , idcard(idcard)
    , balance(0.0)
    , idaccount(idaccount)
    , networkManager(new QNetworkAccessManager(this))
    , inactivityTimer(new QTimer(this))
{
    qDebug() << "debitwindow created with idcard: " << idcard;

    ui->setupUi(this);

    virtualKeyboard = new keyboard(nullptr, this);
    virtualKeyboard->move(440,150);
    virtualKeyboard->close();

    ui->nextButton->hide();
    ui->prevButton->hide();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer -> start();

    QDateTime dateTime = QDateTime::currentDateTime();
    QString datetimetext=dateTime.toString("dd MMMM");
    ui->dateTime->setText(datetimetext);

    inactivityTimer->setInterval(30000); // 30 sekuntia
    connect(inactivityTimer, &QTimer::timeout, this, &debitwindow::closeDueToInactivity);
    inactivityTimer->start();

    this->installEventFilter(this);

    fetchDebitAccount();

    connect(ui->nostoBtn, &QPushButton::clicked, this, &debitwindow::showPage1);
    connect(ui->tilitapahtumatBtn, &QPushButton::clicked, this, &debitwindow::showPage2);
    connect(ui->tilitapahtumatBtn, &QPushButton::clicked, this, &debitwindow::fetchTransactions);

    connect(ui->nextButton, &QPushButton::clicked, this, &debitwindow::nextPage);
    connect(ui->prevButton, &QPushButton::clicked, this, &debitwindow::prevPage);

    connect(ui->balanceBtn, &QPushButton::clicked, this, &debitwindow::showPage3);
    connect(ui->logoutBtn, &QPushButton::clicked, this, &debitwindow::logOut);

    ui->muuBtn->installEventFilter(this);

    ui->nostoSumma->installEventFilter(this);

    connect(ui->kakskytBtn, &QPushButton::clicked, this, [this]() { setSum(20); });
    connect(ui->nelkytBtn, &QPushButton::clicked, this, [this]() { setSum(40); });
    connect(ui->viiskytBtn, &QPushButton::clicked, this, [this]() { setSum(50); });
    connect(ui->sataBtn, &QPushButton::clicked, this, [this]() { setSum(100); });
    connect(ui->withdrawBtn, &QPushButton::clicked, this, [this]() {
        int amount = ui->nostoSumma->text().toInt();
        debitWithdraw(amount);
        fetchTransactions();
    });
}

debitwindow::~debitwindow()
{
    delete ui;
    delete virtualKeyboard;
}

void debitwindow::updatebalancedisplay()
{
    ui->balance->clear();
    ui->balance->setText(QString::number(balance,'f',2));
}

void debitwindow::debitWithdraw(int amount)
{
    if (amount % 10 == 0 && amount <= balance){
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

        ui->uusiBalance->setText("Nostit: " + QString::number(amount));

        QTimer::singleShot(500, this, &debitwindow::fetchDebitAccount);

    } else if (amount % 10 != 0){
        QMessageBox nostoError;
        nostoError.setText("Nostettava summa kymmenen euron tarkkuudella");
        nostoError.exec();
    } else if (amount > balance){
        QMessageBox nostoError;
        nostoError.setText("Luottoraja ylittyy, nostoa ei voida suorittaa");
        nostoError.exec();
    }
}

void debitwindow::setSum(int amount)
{
    ui->nostoSumma->setText(QString::number(amount));
}

void debitwindow::fetchDebitAccount()
{
    QUrl url(QString("http://localhost:3000/accounts_cards/by-card-and-type?idcard=%1&type=debit").arg(idcard));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [reply, this](){
        if (reply->error() == QNetworkReply::NoError){
            //Parseroidaan JSON vastaus
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

                // Päivitetään balance ja idaccount
                this->balance = accountData.value("balance").toDouble();
                this->idaccount = accountData.value("idaccounts").toInt();

                // Debug-tulosteet
                qDebug() << "Fetched balance: " << balance;
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

void debitwindow::fetchTransactions()
{
    qDebug() << "Fetching transactions for account ID: " << idaccount;
    QUrl url(QString("http://localhost:3000/transaction/byAccountId/%1").arg(idaccount));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObj = jsonDoc.object();

            bool success = jsonObj.value("success").toBool();
            if (success) {
                if (!jsonObj.contains("data") || !jsonObj["data"].isArray()) {
                    qDebug() << "Error: 'data' field is missing or is not an array.";
                    return;
                }

                QJsonArray dataArray = jsonObj["data"].toArray();
                if (dataArray.isEmpty()) {
                    qDebug() << "Error: 'data' array is empty.";
                    return;
                }

                // Tallennetaan transactionit
                allTransactions.clear();
                for (const auto &value : dataArray) {
                    if (value.isObject()) {
                        QJsonObject transaction = value.toObject();
                        double amount = transaction["amount"].toDouble();
                        QString date = transaction["actiontimestamp"].toString();
                        allTransactions.append({QString::number(amount, 'f', 2), date});
                    }
                }

                // Käännetään lista näyttämään uusin transaction ensin
                std::reverse(allTransactions.begin(), allTransactions.end());

                // Resetoidaan sivutus
                currentPage = 0;
                updateTableView();
            } else {
                qDebug() << "Error: Transaction fetch failed.";
            }
            reply->deleteLater();
        }
    });
}

void debitwindow::updateTableView()
{
    if (allTransactions.isEmpty()) {
        qDebug() << "No transactions available to display.";
        return;
    }

    QTableView *tableView = qobject_cast<QTableView *>(ui->tilitapahtumatView);
    if (!tableView) return;

    QStandardItemModel *transactionModel = new QStandardItemModel(this);
    transactionModel->setHorizontalHeaderLabels({"Määrä", "Päivämäärä"});

    int startRow = currentPage * rowsPerPage;
    int endRow = qMin(startRow + rowsPerPage, allTransactions.size());

    // Näytetään sivulle relevantit transactionit
    for (int i = startRow; i < endRow; ++i) {
        QList<QStandardItem *> rowItems;
        rowItems.append(new QStandardItem(allTransactions[i].first));
        rowItems.append(new QStandardItem(allTransactions[i].second));
        transactionModel->appendRow(rowItems);
    }

    tableView->setModel(transactionModel);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Enabloi/Disabloi navigaatio buttons käytettäville sivuille
    ui->prevButton->setEnabled(currentPage > 0);
    ui->nextButton->setEnabled(endRow < allTransactions.size());
}

void debitwindow::nextPage()
{
    if ((currentPage + 1) * rowsPerPage < allTransactions.size()) {
        currentPage++;
        updateTableView();
    }
}

void debitwindow::prevPage()
{
    if (currentPage > 0) {
        currentPage--;
        updateTableView();
    }
}

void debitwindow::resetInactivityTimer()
{
    inactivityTimer->start(); //Restarttaa ajastimen (30 sek)
    qDebug() << "Timer restarted.";
}

void debitwindow::closeDueToInactivity()
{
    qDebug() << "Closing due to inactivity.";
    close();
    QMessageBox logout;
    logout.setText("Sinut on kirjattu ulos\nKirjaudu sisään uudelleen");
    logout.exec();
}

bool debitwindow::eventFilter(QObject *obj, QEvent *event)
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

void debitwindow::showTime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->digitalClock->setText(time_text);
}

void debitwindow::showPage1()
{
    ui->stackedWidget->setCurrentIndex(0); //Näyttää "Nosto" sivun

    virtualKeyboard->show();
    ui->nextButton->hide();
    ui->prevButton->hide();
}

void debitwindow::showPage2()
{
    ui->stackedWidget->setCurrentIndex(1); // Näyttää saldon/luottorajan

    virtualKeyboard->close();
    ui->nextButton->show();
    ui->prevButton->show();
}

void debitwindow::showPage3()
{
    ui->stackedWidget->setCurrentIndex(3); // Näyttää tilitapahtumat

    virtualKeyboard->close();
    ui->nextButton->hide();
    ui->prevButton->hide();
}

void debitwindow::logOut()
{
    inactivityTimer->stop();
    qDebug() << "logoutBtn clicked.";
    close();
}
