#include "accoutmain.h"
#include "ui_accoutmain.h"

accoutmain::accoutmain(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::accoutmain)
{
    ui->setupUi(this);
}

accoutmain::~accoutmain()
{
    delete ui;
}
