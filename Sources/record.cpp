#include "record.h"
#include "ui_record.h"

RecordDialog::RecordDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::RecordDialog)
{
	ui->setupUi(this);
    //设置对话标志
	setDialogFlags();
    //初始化
	initDialog();
}

RecordDialog::~RecordDialog()
{
	delete ui;
}

//同难度下，比较花费时间
bool RecordDialog::compare(Record& record1, Record& record2)
{
	return record1.time < record2.time;
}

//设置对话标志
void RecordDialog::setDialogFlags()
{
	setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

//初始化
void RecordDialog::initDialog()
{
    //记录游戏记录的容器
	memset(recordCount, 0, sizeof(recordCount));

    //从简单难度依次到复杂难度，将游戏记录存入数组
	for (int level = EASY; level <= HIGH; level++)
	{
		for (int i = 0; i < RECORD_COUNT; i++)
		{
			static QRect labelRect;

            //设置文字位置
			labelRect.setX(INIT_LEFT + DISTANCE_LEFT * level);
			labelRect.setY(INIT_UPPER + DISTANCE_UPPER * i);
			labelRect.setWidth(WIDTH);
			labelRect.setHeight(HEIGHT);

			pRecordLabels[level][i] = new QLabel(this);
			pRecordLabels[level][i]->setGeometry(labelRect);
		}
	}
}

//打开游戏记录视窗
void RecordDialog::openDialog()
{
   //渲染游戏记录，展示每个难度下的前三名
	for (int level = EASY; level <= HIGH; level++)
	{
		for (int i = 0; i < RECORD_COUNT; i++)
		{
            //设置中间变量存放游戏记录
			QString text = QString("%1s (%2)").arg(record[level][i].time).arg(record[level][i].name);

            //此难度下的第几名是否有游戏记录？
            //若有，则展示。若无，则显示“~”
            pRecordLabels[level][i]->setText((i < recordCount[level]) ? text : "~");
		}
	}
	QDialog::exec();
}

//对游戏记录数组进行排序
void RecordDialog::getRecord(QString name, int time, Level level)
{
    //筛选游戏难度
	if (recordCount[level] < RECORD_COUNT)
	{
		record[level][recordCount[level]].name = name;
		record[level][recordCount[level]].time = time;
		recordCount[level] += 1;
	}
    //筛选花费时间
	else if (time < record[level][RECORD_COUNT - 1].time)
	{
		record[level][RECORD_COUNT - 1].name = name;
		record[level][RECORD_COUNT - 1].time = time;
	}
    //对游戏记录数组进行排序
	std::sort(record[level], record[level] + recordCount[level], compare);
}
