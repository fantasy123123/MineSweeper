#include "advertisement.h"
#include "ui_advertisement.h"

advertisement::advertisement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::advertisement)
{
    ui->setupUi(this);
}

advertisement::~advertisement()
{
    delete ui;
}
