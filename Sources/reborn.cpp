#include "reborn.h"
#include "ui_reborn.h"

reborn::reborn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::reborn)
{
    ui->setupUi(this);
}

reborn::~reborn()
{
    delete ui;
}
