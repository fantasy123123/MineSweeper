#include "instruction.h"
#include "ui_instruction.h"

InstructionDialog::InstructionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InstructionDialog)
{
    //设置ui
    ui->setupUi(this);
    //设置对话标志
    setDialogFlags();
}

InstructionDialog::~InstructionDialog()
{
    delete ui;
}

//设置对话标志
void InstructionDialog::setDialogFlags()
{
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}
