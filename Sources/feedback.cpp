#include "feedback.h"
#include "ui_feedback.h"

FeedBackDialog::FeedBackDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FeedBackDialog)
{
    //设置ui
    ui->setupUi(this);
    //设置对话标志
    setDialogFlags();
}

FeedBackDialog::~FeedBackDialog()
{
    delete ui;
}

//设置对话标志
void FeedBackDialog::setDialogFlags()
{
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}
