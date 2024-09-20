#include "about.h"
#include "ui_about.h"

AboutDialog::AboutDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    //设置ui
	ui->setupUi(this);
    //设置对话标志
	setDialogFlags();
}

AboutDialog::~AboutDialog()
{
	delete ui;
}

//设置对话标志
void AboutDialog::setDialogFlags()
{
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}
