#include "randomeventone.h"
#include "ui_randomeventone.h"

randomEventOne::randomEventOne(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::randomEventOne)
{
    ui->setupUi(this);
}

randomEventOne::~randomEventOne()
{
    delete ui;
}
