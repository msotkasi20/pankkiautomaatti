#include "keyboard.h"

keyboard::keyboard(QLineEdit *targetField, QWidget *parent)
    : QWidget(parent), targetField(targetField)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus | Qt::WindowStaysOnTopHint );
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(200,150);

    QGridLayout *layout = new QGridLayout(this);
    QStringList keys = {"1","2","3","4","5","6","7","8","9","C","0","->"};

    int row = 0, col = 0;
    for (const QString &key : keys) {
        QPushButton *button = new QPushButton(key, this);
        button->setFocusPolicy(Qt::NoFocus);
        connect(button, &QPushButton::clicked, this, &keyboard::keyPressed);

        button->setStyleSheet("QPushButton { "
                              "color: white; "  // Tekstin väri
                              "background-color: rgb(47, 117, 168); "  // Taustaväri
                              "border: none; "  // Ei reunoja
                              "font-weight: bold; "  // Fontti boldattuna
                              "} "
                              "QPushButton:hover { "
                              "background-color: rgb(124, 209, 255); "  // Hover-tilassa vaaleampi sininen
                              "} "
                              "QPushButton:pressed { "
                              "background-color: rgb(14, 74, 110); "  // Painettu tila, tummempi sininen
                              "}");


        layout->addWidget(button, row, col);
        col++;
        if (col >2) {col = 0, row++; }
    }
    setLayout(layout);
}

void keyboard::setTargetField(QLineEdit *targetField)
{
    this->targetField = targetField;
}

void keyboard::keyPressed()
{
    QPushButton *button = qobject_cast<QPushButton* >(sender());
    if (!button || !targetField) return;

    if (button->text() == "C") {
        targetField->clear(); // Tyhjennetään tekstikenttä
    } else if (button->text() == "->"){
        QWidget *nextWidget = targetField->nextInFocusChain();
        while (nextWidget && !qobject_cast<QLineEdit *>(nextWidget)){
            nextWidget = nextWidget->nextInFocusChain();
        }
        if (nextWidget) {
            nextWidget->setFocus();
        }

    } else {
        targetField->setText(targetField->text() + button->text()); //Asetetaan tekstikenttään napista painettu numero
    }
}