#include "cord.h"
#include "ui_cord.h"

CorD::CorD(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CorD)
{
    ui->setupUi(this);
}

CorD::~CorD()
{
    delete ui;
}
