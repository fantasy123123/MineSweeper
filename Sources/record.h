#ifndef __RECORD_H__
#define __RECORD_H__

#include <QDialog>
#include <QLabel>

QT_BEGIN_NAMESPACE

//游戏记录类
namespace Ui
{
	class RecordDialog;
}

QT_END_NAMESPACE

//游戏难度
enum Level { EASY, NORMAL, HIGH, CUSTOM };

//选项框静态前端参数
enum LabelConstant
{
	WIDTH = 160,
	HEIGHT = 20,
	INIT_LEFT = 50,
	INIT_UPPER = 90,
	DISTANCE_LEFT = 200,
	DISTANCE_UPPER = 45
};

//定义记录名称以及花费时间
struct Record
{
	QString name;
	int time;
};

//
class RecordDialog : public QDialog
{
	Q_OBJECT

	private:
        //游戏难度
		static const int LEVEL_COUNT = 3;

        //游戏记录
		static const int RECORD_COUNT = 3;

	private:
		Ui::RecordDialog* ui;

        //展示游戏难度以及游戏记录（展示名称以及花费时间）
		QLabel* pRecordLabels[LEVEL_COUNT][RECORD_COUNT];

	private:

        //记录游戏难度以及游戏记录
		Record record[LEVEL_COUNT][RECORD_COUNT];

        //记录游戏难度
		int recordCount[LEVEL_COUNT];

	private:
        //同难度下，比较游戏时间
		static bool compare(Record&, Record&);

	private:
        //设置对话标志
		void setDialogFlags();

        //初始化
		void initDialog();

	public:
		RecordDialog(QWidget* parent = nullptr);
		~RecordDialog();

	public:

        //打开对话框
		void openDialog();

        //获得游戏难度以及花费时间以及名称
		void getRecord(QString, int, Level);
};
#endif
