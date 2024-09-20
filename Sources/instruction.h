#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QDialog>

QT_BEGIN_NAMESPACE

//定义说明类
namespace Ui {
class InstructionDialog;
}

QT_END_NAMESPACE

class InstructionDialog : public QDialog
{

    Q_OBJECT

    private:
        Ui::InstructionDialog *ui;

    private:
        //设置对话标志
        void setDialogFlags();

    public:
        explicit InstructionDialog(QWidget *parent = nullptr);
        ~InstructionDialog();
};
#endif
