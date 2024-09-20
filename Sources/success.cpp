#include "success.h"
#include "ui_success.h"

SuccessDialog::SuccessDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SuccessDialog)
{
    ui->setupUi(this);
    //设置对话标志
	setDialogFlags();
	connectSignals();
}

SuccessDialog::~SuccessDialog()
{
    delete ui;
}

//设置对话标志
void SuccessDialog::setDialogFlags()
{
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

//点击事件：点击按钮确认需要保存游戏记录
void SuccessDialog::connectSignals()
{
	connect(ui->donePushButton, &QPushButton::clicked, this, &SuccessDialog::inputDone);
}

//不需要保存游戏记录
void SuccessDialog::openDialog()
{
	isNeedSave = false;
	QDialog::exec();
}

//需要保存游戏记录
void SuccessDialog::inputDone()
{
	isNeedSave = true;
	QDialog::close();
}

//获取是否需要保存游戏记录
bool SuccessDialog::getIsNeedSave()
{
	return isNeedSave;
}

//获取名称
QString SuccessDialog::getInputName()
{
    return ui->nameLineEdit->text();
}
