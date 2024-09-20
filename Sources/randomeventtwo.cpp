#include "randomeventtwo.h"
#include "ui_randomeventtwo.h"

randomEventTwo::randomEventTwo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::randomEventTwo)
{
    ui->setupUi(this);
}

randomEventTwo::~randomEventTwo()
{
    delete ui;
}
