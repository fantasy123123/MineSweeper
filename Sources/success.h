#ifndef __SUCCESS_H__
#define __SUCCESS_H__

#include <QDialog>

QT_BEGIN_NAMESPACE

//成功后的界面
namespace Ui
{
    class SuccessDialog;
}

QT_END_NAMESPACE

class SuccessDialog : public QDialog
{
    Q_OBJECT

	private:
		Ui::SuccessDialog* ui;

        //是否需要保存记录
		bool isNeedSave;

	private:

        //设置对话标志
		void setDialogFlags();

		void connectSignals();

    public:
		SuccessDialog(QWidget* parent = nullptr);
        ~SuccessDialog();

    public:
        //打开对话框
		void openDialog();

        //初始化
		void inputDone();

	public:
        //获得是否需要保存记录
		bool getIsNeedSave();

        //输入获胜者名称
        QString getInputName();
};
#endif
