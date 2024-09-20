#ifndef __CUSTOM_H__
#define __CUSTOM_H__

#include <QDialog>

QT_BEGIN_NAMESPACE

//自定义游戏难度类
namespace Ui
{
	class CustomDialog;
}

QT_END_NAMESPACE

class CustomDialog : public QDialog
{
	Q_OBJECT

	private:
		Ui::CustomDialog* ui;

        //是否需要自定义格子数以及地雷数等
		bool isNeedSet;

	private:
        //设置对话标志
		void setDialogFlags();

		void connectSignals();

	public:
		CustomDialog(QWidget* parent = nullptr);
		~CustomDialog();

	public:
        //打开自定义界面
		void openDialog();

        //输入自定义数据
		void inputDone();

	public:
        //是否需要自定义数据
		bool getIsNeedSet();

        //自定义行数
		int getInputRows();

        //自定义列数
		int getInputCols();

        //自定义地雷数量
		int getInputMineCount();
};
#endif
