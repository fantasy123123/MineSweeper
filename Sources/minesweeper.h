#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include <QApplication>
#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QMediaPlayer>
#include <QStyle>
#include <QScreen>

#include "randomeventthree.h"
#include "randomeventtwo.h"
#include "randomeventone.h"
#include "reborn.h"
#include "feedback.h"
#include "instruction.h"
#include "about.h"
#include "custom.h"
#include "record.h"
#include "success.h"
#include "musicwindow.h"

QT_BEGIN_NAMESPACE

//定义游戏
namespace Ui
{
    class MainGame;
}

QT_END_NAMESPACE

//定义玩家状态
enum Status { PLAYING, PAUSE, OVER, WIN, EXIT };

//定义格子状态
enum BlockType { NONE, NUMBER, MINE };

//定义图片常数
enum ImageConstant
{
	NUMBER_COUNT = 8
};

//定义颜色常数
enum ColorConstant
{
	WHITE = 0xFFFFFFFF,
	BLACK = 0xFF353535,
	GRAY = 0xFF606060
};

//简单模式
enum class EasyLevel
{
	ROWS = 10,
	COLS = 10,
	MINE_INIT_COUNT = 10
};

//中级模式
enum class NormalLevel
{
	ROWS = 15,
	COLS = 15,
	MINE_INIT_COUNT = 30
};

//高级模式
enum class HighLevel
{
	ROWS = 30,
	COLS = 20,
	MINE_INIT_COUNT = 100
};

//记录格子的容器
typedef QVector <QPoint> PointList;

//记录数量的容器
typedef QVector <int> NumberList;

//格子类
struct Block
{
    //格子状态（即格子内的“东西”是什么）
	BlockType type;

    //数字格的数字
    int number;

    //是否被翻开
    bool isCovered;

    //是否被标记
    bool isMarked;

    //非地雷格是否被错误标记
    bool isError;

    //是否动过格子
    bool isTouched;

    //随机事件一
    bool randomEventOne;

    //随机事件二
    bool randomEventTwo;

    //随机事件三
    bool randomEventThree;
};

//格子的图片类
struct Images
{
    //格子块
    QPixmap block;

    //盖上/翻开
    QPixmap cover;

    //错误地给非地雷格子打上了标记
    QPixmap error;

    //地雷
    QPixmap mine;

    //错误地点开了地雷格
    QPixmap mineError;

    //标记
    QPixmap flag;

    //音乐
    QPixmap music;

    //感叹号
    QPixmap tip;

    //数字格的数字
	QPixmap number[NUMBER_COUNT];
};

//记录时间
struct Timers
{
    QTimer interval;
    QTimer clock;
};

//颜色
struct Colors
{
	QColor white;
    QColor gray;
    QColor black;
};

//音频
struct Audio
{
    QMediaPlayer click;
    QMediaPlayer lose;
    QMediaPlayer win;
};

//游戏
class MainGame : public QMainWindow
{
    Q_OBJECT

	private:
        //游戏FPS、定时器时长
		static const int GAME_FPS = 10;
		static const int CLOCK_INTERVAL = 1000;

	private:
        //横排最大格子数量
		static const int ROWS_MAX = 40;
        //竖排最大格子数量
		static const int COLS_MAX = 25;
        //地雷最大数量
		static const int MINE_COUNT_MAX = 1000;

	private:
        //格子尺寸
		static const int BLOCK_SIZE = 32;

        //视窗边框
		static const int MARGIN_X = 12;
		static const int MARGIN_Y = 78;

        //视窗边框宽度
		static const int BORDER = 6;

        //格子边框宽度
		static const int BLOCK_BORDER = 1;

	private:
        //长宽
		static const int INFO_UPPER = 53;
		static const int INFO_WIDTH = 120;

    private:
        //以下为游戏相关的东西
        Ui::MainGame* ui;
        QPoint mouse;
		Images images;
		Timers timers;
		Colors colors;
        Audio audio;

    private:
        //选项相关

        //关于选项
		AboutDialog* pAbout;

        //自定义选项
		CustomDialog* pCustom;

        //成功
		SuccessDialog* pSuccess;

        //游戏记录
		RecordDialog* pRecord;

        //游戏说明
        InstructionDialog* pInstruction;

        //反馈
        FeedBackDialog* pFeedback;

        //音乐
        MainWindow* pMusic;

        //复活广告
        reborn* pReborn;

        //随机事件一
        randomEventOne* pRandomEventOne;

        //随机事件二
        randomEventTwo* pRandomEventTwo;

        //随机事件三
        randomEventThree* pRandomEventThree;

    private:
        //最大横排格子数量以及竖排格子数量
		Block blocks[ROWS_MAX][COLS_MAX];

        //记录地雷位置
		PointList mineList;

        //记录没有地雷的位置
		PointList noneList;

        //记录数量
		NumberList numberList;

    private:
        //窗口长宽
        int screenWidth;
        int screenHeight;

        //游戏区域长宽
        int tableWidth;
        int tableHeight;

        //横排以及竖排格子数量
        int tableRows;
        int tableCols;

        //初始地雷数量
        int mineInitCount;

    private:
        //游戏状态
		Status status;

        //游戏难度
		Level level;

        //棋子数量
        int flagCount;

        //花费时间
		int timeDuring;

        //是否透视
        bool isCracked;

        //是否透视过
		bool isHaveCracked;

        //玩家复活
        bool isReborned;

        //是否获得过复活机会
        bool isHaveGetReborned;

	private:
        //以下为设置难度以及调整视窗大小
        void setEasyLevel();
        void setNormalLevel();
        void setHighLevel();
        void setCustomLevel();
        void resizeWindow();

	private:
        //以下为初始化设置，包括加载音频图画、初始化游戏数据、记录时间以及设置事件侦听等等
        void loadImage();
        void loadAudio();
        void mainInterval();
        void clockCallback();
        void initColor();
        void setInterval();
        void connectTimer();
        void connectAction();
        void startTimer();
        void setMusic();


	private:
        //重新开始
		void restart();

        //添加地雷
        void addMine();

        //给地雷格周围的格子添加数字
        void addNumber();

        //设置参数
        void setRecord();

        //暂停
		void setPause();

        //游戏获胜
        void gameoverWin();

        //游戏失败
        void gameoverLose(int, int);

        //自动显示没有地雷的格子
		void autoUncover();

	private:
        //事件侦听事件
        void mousePressEvent(QMouseEvent*);
        void mouseReleaseEvent(QMouseEvent*);
        void keyPressEvent(QKeyEvent*);
        void keyReleaseEvent(QKeyEvent*);

	private:
        //游戏界面画图
        void displayBackground(QPainter&);
        void displayBlock(QPainter&);
        void displayInfo(QPainter&);
        void paintEvent(QPaintEvent*);

	public:
		MainGame(QWidget* parent = nullptr);
		~MainGame();

	public:
		void init();
};
#endif
