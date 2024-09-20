#include "custom.h"
#include "ui_custom.h"

CustomDialog::CustomDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::CustomDialog)
{
    //设置ui
	ui->setupUi(this);
    //设置对话标志
	setDialogFlags();
    //设置事件
	connectSignals();
}

CustomDialog::~CustomDialog()
{
	delete ui;
}

//设置对话标志
void CustomDialog::setDialogFlags()
{
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

//点击事件：点击按钮确认修改参数
void CustomDialog::connectSignals()
{
	connect(ui->doneButton, &QPushButton::clicked, this, &CustomDialog::inputDone);
}

//不需要修改参数
void CustomDialog::openDialog()
{
	isNeedSet = false;
	QDialog::exec();
}

//需要修改参数
void CustomDialog::inputDone()
{
	isNeedSet = true;
	QDialog::close();
}

//获取是否修改参数
bool CustomDialog::getIsNeedSet()
{
	return isNeedSet;
}

//获取自定义行数
int CustomDialog::getInputRows()
{
	return ui->widthSpinBox->value();
}

//获取自定义列数
int CustomDialog::getInputCols()
{
	return ui->heightSpinBox->value();
}

//获取自定义地雷数量
int CustomDialog::getInputMineCount()
{
    //如果地雷数量大于等于格子数量（行数×列数）
	if (ui->mineSpinBox->value() >= ui->widthSpinBox->value() * ui->heightSpinBox->value())
	{
        //将全部格子布满地雷
		return ui->widthSpinBox->value() * ui->heightSpinBox->value();
	}
    //返回输入的地雷数量
	else { return ui->mineSpinBox->value(); }
}
