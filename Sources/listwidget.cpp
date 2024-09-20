#include "listwidget.h"
#include "ui_listwidget.h"

ListWidget::ListWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ListWidget)
{
    ui->setupUi(this);
    //设置窗口标志
    this->setWindowFlag(Qt::FramelessWindowHint);
}

ListWidget::~ListWidget()
{
    delete ui;
}

void ListWidget::additem(QString str)
{
    //添加歌单
    ui->listWidget->addItem(str);
}
