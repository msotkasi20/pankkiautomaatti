#include "keyboard.h"

keyboard::keyboard(QLineEdit *targetField, QWidget *parent)
    : QWidget(parent), targetField(targetField)
{
    setWindowFlags(Qt::Popup);
    setFixedSize(200,150);

    QGridLayout *layout = new QGridLayout(this);
    QStringList keys = {"1","2","3","4","5","6","7","8","9","C","0","->"};

    int row = 0, col = 0;
    for (const QString &key : keys) {
        QPushButton *button = new QPushButton(key, this);
        connect(button, &QPushButton::clicked, this, &keyboard::keyPressed);
        layout->addWidget(button, row, col);
        col++;
        if (col >2) {col = 0, row++; }
    }
    setLayout(layout);
}

void keyboard::keyPressed()
{
    QPushButton *button = qobject_cast<QPushButton* >(sender());
    if (!button || !targetField) return;

    if (button->text() == "C") {
        targetField->clear(); // Tyhjennetään tekstikenttä
    } else {
        targetField->setText(targetField->text() + button->text()); //Asetetaan tekstikenttään napista painettu numero
    }
}


