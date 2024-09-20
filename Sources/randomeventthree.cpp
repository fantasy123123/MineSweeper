#include "randomeventthree.h"
#include "ui_randomeventthree.h"

randomEventThree::randomEventThree(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::randomEventThree)
{
    ui->setupUi(this);
}

randomEventThree::~randomEventThree()
{
    delete ui;
}
