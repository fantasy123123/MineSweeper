#include "minesweeper.h"
#include "ui_minesweeper.h"

#include <QRandomGenerator>
#include<QDebug>
#include<QPushButton>
#include<QPainter>
#include<QLabel>
#include<QImage>

//游戏
MainGame::MainGame(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainGame)
{
    ui->setupUi(this);
    //关于选项
	pAbout = new AboutDialog(this);
    //定义难度与参数
	pCustom = new CustomDialog(this);
    //成功界面
	pSuccess = new SuccessDialog(this);
    //游戏记录
	pRecord = new RecordDialog(this);
    //游戏说明
    pInstruction=new InstructionDialog(this);
    //反馈
    pFeedback=new FeedBackDialog(this);
    //音乐
    pMusic=new MainWindow(this);
    //复活广告
    pReborn=new reborn(this);
    //随机事件一
    pRandomEventOne=new randomEventOne(this);
    //随机事件二
    pRandomEventTwo=new randomEventTwo(this);
    //随机事件三
    pRandomEventThree=new randomEventThree(this);
    //初始时音乐界面隐藏
    pMusic->hide();
    //初始时复活广告界面隐藏
    pReborn->hide();
    //初始时随机事件提示界面隐藏
    pRandomEventOne->hide();
    pRandomEventTwo->hide();
    pRandomEventThree->hide();
}

MainGame::~MainGame()
{
    delete ui;
	delete pAbout;
	delete pCustom;
	delete pSuccess;
	delete pRecord;
    delete pInstruction;
    delete pFeedback;
    delete pMusic;
    delete pReborn;
    delete pRandomEventOne;
    delete pRandomEventTwo;
    delete pRandomEventThree;
}


void MainGame::init()
{
    //随机数种子
	srand((unsigned)time(NULL));
    //加载图片
	loadImage();
    //加载音频
	loadAudio();
    //初始化颜色
	initColor();
    //设置定时器
	setInterval();
    //绑定事件侦听
	connectTimer();
	connectAction();
    //计时
	startTimer();
    //初始难度为初级难度
	setEasyLevel();
    //重置复活机会
    isHaveGetReborned=false;
}

void MainGame::loadImage()
{
    //加载各种游戏图片
	images.block.load(":/Images/block.png");
    images.cover.load(":/Images/cover.png");
    images.error.load(":/Images/error.png");
    images.mine.load(":/Images/mine.png");
    images.mineError.load(":/Images/mine_error.png");
    images.flag.load(":/Images/flag.png");
    images.music.load(":/Images/music.png");
    images.tip.load(":/Images/tip.png");

    for (int i = 0; i < NUMBER_COUNT; i++)
    {
		images.number[i].load(QString(":/Images/number_%1.png").arg(i + 1));
    }
}

void MainGame::loadAudio()
{
    //加载各种游戏音频
    audio.click.setMedia(QUrl("qrc:/Audio/click.mp3"));
    audio.lose.setMedia(QUrl("qrc:/Audio/lose.mp3"));
    audio.win.setMedia(QUrl("qrc:/Audio/win.mp3"));
}

//设置游戏难度为初级
void MainGame::setEasyLevel()
{
	level = EASY;
    //设置行数列数与地雷数与界面尺寸
	tableRows = (int)EasyLevel::ROWS;
	tableCols = (int)EasyLevel::COLS;
	mineInitCount = (int)EasyLevel::MINE_INIT_COUNT;
    resizeWindow();
	restart();
}

//设置游戏难度为中级
void MainGame::setNormalLevel()
{
	level = NORMAL;
    //设置行数列数与地雷数与界面尺寸
	tableRows = (int)NormalLevel::ROWS;
	tableCols = (int)NormalLevel::COLS;
	mineInitCount = (int)NormalLevel::MINE_INIT_COUNT;
    resizeWindow();
	restart();
}

//设置游戏难度为高级
void MainGame::setHighLevel()
{
	level = HIGH;
    //设置行数列数与地雷数与界面尺寸
	tableRows = (int)HighLevel::ROWS;
	tableCols = (int)HighLevel::COLS;
	mineInitCount = (int)HighLevel::MINE_INIT_COUNT;
    resizeWindow();
	restart();
}

//设置自定义游戏参数
void MainGame::setCustomLevel()
{
    //打开设置游戏参数对话框
	pCustom->openDialog();

    //如果确认自定义设置
	if (pCustom->getIsNeedSet())
    {
		level = CUSTOM;
        //设置行数列数与地雷数与界面尺寸
		tableRows = pCustom->getInputRows();
		tableCols = pCustom->getInputCols();
		mineInitCount = pCustom->getInputMineCount();
        resizeWindow();
		restart();
	}
}

//根据游戏难度或参数重新设置视窗大小
void MainGame::resizeWindow()
{
    //根据行数与列数获取应设置的视窗大小
	tableWidth = tableRows * BLOCK_SIZE;
	tableHeight = tableCols * BLOCK_SIZE;
    screenWidth = MARGIN_X * 2 + tableWidth;
    screenHeight = MARGIN_X + MARGIN_Y + tableHeight;

    //重新设置视窗大小
    setFixedSize(screenWidth, screenHeight);
}

//游戏中点击格子后进行判定
void MainGame::mainInterval()
{
    //如果正在游戏
    if (status == PLAYING)
    {
		if (isMinimized())
		{
            //暂停
			setPause();
		}
        //判定游戏是否胜利
		gameoverWin();
        //自动展示空格子
		autoUncover();
    }
    //更新界面
	this->update();
}

//统计花费时间
void MainGame::clockCallback()
{
	if (status == PLAYING) { timeDuring += 1; }
}

//定时器
void MainGame::setInterval()
{
    //时间每秒增加一次
    timers.interval.setInterval(1000 / GAME_FPS);
    timers.clock.setInterval(CLOCK_INTERVAL);
}

//当正在游戏时，时间增加以及点击判定事件触发
void MainGame::connectTimer()
{
    connect(&timers.interval, &QTimer::timeout, this, &MainGame::mainInterval);
    connect(&timers.clock, &QTimer::timeout, this, &MainGame::clockCallback);
}

//点击事件
void MainGame::connectAction()
{
    //初级游戏难度
    connect(ui->actionEasy, &QAction::triggered, this, &MainGame::setEasyLevel);

    //中级游戏难度
    connect(ui->actionNormal, &QAction::triggered, this, &MainGame::setNormalLevel);

    //高级游戏难度
    connect(ui->actionHigh, &QAction::triggered, this, &MainGame::setHighLevel);

    //自定义游戏难度
    connect(ui->actionCustom, &QAction::triggered, this, &MainGame::setCustomLevel);

    //暂停
	connect(ui->actionPause, &QAction::triggered, this, &MainGame::setPause);

    //重新开始
	connect(ui->actionRestart, &QAction::triggered, this, &MainGame::restart);

    //排行榜
	connect(ui->actionRecord, &QAction::triggered, pRecord, &RecordDialog::openDialog);

    //关于
	connect(ui->actionAbout, &QAction::triggered, pAbout, &AboutDialog::exec);

    //说明
    connect(ui->actionInstruction, &QAction::triggered, pInstruction, &InstructionDialog::exec);

    //反馈
    connect(ui->actionFeedback, &QAction::triggered, pFeedback, &FeedBackDialog::exec);
}

//开始计时
void MainGame::startTimer()
{
    timers.interval.start();
    timers.clock.start();
}

//重新开始游戏
void MainGame::restart()
{
    //重新触发音频
    audio.click.stop();
    audio.click.play();

    //重新设置格子
    for (int i = 0; i < tableRows; i++)
    {
        for (int j = 0; j < tableCols; j++)
        {
            //将格子全部盖上
			blocks[i][j].type = NONE;
			blocks[i][j].number = 0;
			blocks[i][j].isCovered = true;
			blocks[i][j].isMarked = false;
			blocks[i][j].isTouched = false;
			blocks[i][j].isError = false;
            blocks[i][j].randomEventOne=false;
            blocks[i][j].randomEventTwo=false;
        }
    }

    //重新设置游戏状态
    status = PLAYING;
    //重新设置地雷数量
    flagCount = mineInitCount;
    //重新计时
	timeDuring = 0;
    //重新设置是否透视
    isCracked = false;
    //重新设置是否透视过
	isHaveCracked = false;
    //添加地雷
    addMine();
    //添加数字
    addNumber();
    //重置复活机会
    isHaveGetReborned=false;
    //绘制随机事件一
    for(int i=0;i<1;i++)
    {
        //生成随机格子坐标
        int randomX=std::rand()%100/(double)101*tableRows;
        int randomY=std::rand()%100/(double)101*tableCols;

        //如果该格子不是地雷格
        if(blocks[randomX][randomY].type!=MINE)
        {
            blocks[randomX][randomY].randomEventOne=true;
        }
        qDebug()<<randomX+1<<randomY+1;
    }
    for(int i=0;i<1;i++)
    {
        //生成随机格子坐标
        int randomX=std::rand()%100/(double)101*tableRows;
        int randomY=std::rand()%100/(double)101*tableCols;

        //如果该格子不是地雷格
        if(blocks[randomX][randomY].type!=MINE)
        {
            blocks[randomX][randomY].randomEventOne=true;
        }
        qDebug()<<randomX+1<<randomY+1;
    }

    //绘制随机事件二
    for(int i=0;i<1;i++)
    {
        //生成随机格子坐标
        int randomX=std::rand()%100/(double)101*tableRows;
        int randomY=std::rand()%100/(double)101*tableCols;

        //如果该格子不是地雷格且不是随机事件一格
        if(blocks[randomX][randomY].type!=MINE&&
           blocks[randomX][randomY].randomEventOne==false)
        {
            blocks[randomX][randomY].randomEventTwo=true;
        }
        qDebug()<<randomX+1<<randomY+1;
    }
    for(int i=0;i<1;i++)
    {
        //生成随机格子坐标
        int randomX=std::rand()%100/(double)101*tableRows;
        int randomY=std::rand()%100/(double)101*tableCols;

        //如果该格子不是地雷格且不是随机事件一格
        if(blocks[randomX][randomY].type!=MINE&&
           blocks[randomX][randomY].randomEventOne==false)
        {
            blocks[randomX][randomY].randomEventTwo=true;
        }
        qDebug()<<randomX+1<<randomY+1;
    }
}

//初始化颜色
void MainGame::initColor()
{
	colors.white.setRgb(WHITE);
	colors.black.setRgb(BLACK);
	colors.gray.setRgb(GRAY);
}

//添加地雷
void MainGame::addMine()
{
    //先清除上一局的地雷数组
	mineList.clear();

    //设置最大地雷数量
	for (int i = 0; i < ROWS_MAX * COLS_MAX; i++)
	{
		numberList.append(i);
	}

    //根据随机数种子以及游戏参数，通过qSwap进行交换以随机产生地雷位置
	for (int i = 0; i < tableRows * tableCols; i++)
	{
		qSwap(numberList[i], numberList[rand() % (tableRows * tableCols)]);
	}

    //设置地雷
	for (int i = 0; i < mineInitCount; i++)
	{
		int x = numberList[i] % tableRows;
		int y = numberList[i] / tableRows;

		blocks[x][y].type = MINE;
		mineList.append(QPoint(x, y));
	}

    //清除地雷数组
	numberList.clear();
}

//给地雷格周围的格子添加数字
void MainGame::addNumber()
{
    //获取地雷格坐标
    for (int i = 0; i < mineInitCount; i++)
    {
        //通过地雷格获取地雷格周围的格子坐标
        for (int sideX = -1; sideX <= 1; sideX++)
        {
            for (int sideY = -1; sideY <= 1; sideY++)
            {
                //添加数字的格子的坐标（地雷格周围的一周）
				int x = mineList[i].x() + sideX;
				int y = mineList[i].y() + sideY;

                //判断数字格周围是否还有其他的地雷格
				if (x >= 0 && x < tableRows && y >= 0 && y < tableCols && blocks[x][y].type != MINE)
                {
					blocks[x][y].type = NUMBER;
					blocks[x][y].number += 1;
                }
            }
        }
    }
}

//游戏记录
void MainGame::setRecord()
{
	pRecord->getRecord(pSuccess->getInputName(), timeDuring, level);
}

//暂停游戏（要求不处于透视状态）
void MainGame::setPause()
{
    if (status == PLAYING && !isCracked)
    {
        status = PAUSE;
    }
}

//判定游戏胜利
void MainGame::gameoverWin()
{
    for (int x = 0; x < tableRows; x++)
    {
        for (int y = 0; y < tableCols; y++)
        {
            //游戏胜利条件：地雷格没有被点击翻开
			if (blocks[x][y].type != MINE && blocks[x][y].isCovered)
            {
				return;
            }
        }
    }
    //游戏胜利音频
	audio.win.stop();
	audio.win.play();
	status = WIN;

    //记录游戏，要求没有透视过
	if (level != CUSTOM && !isHaveCracked)
	{
        //打开对话框记录游戏
		pSuccess->openDialog();
		if (pSuccess->getIsNeedSave()) { setRecord(); }
	}
}

//判定游戏失败
void MainGame::gameoverLose(int x, int y)
{
    //游戏失败音频
    audio.lose.stop();
    audio.lose.play();

    for (int x = 0; x < tableRows; x++)
    {
        for (int y = 0; y < tableCols; y++)
        {
            //失败条件：点到地雷格，地雷格没有做标记
			if (blocks[x][y].type == MINE && !blocks[x][y].isMarked)
            {
				blocks[x][y].isCovered = false;
            }
            //或者给非地雷格做了标记
			else if (blocks[x][y].type != MINE && blocks[x][y].isMarked)
            {
				blocks[x][y].isError = true;
            }
        }
    }
	blocks[x][y].isTouched = true;
    status = OVER;
}

//自动翻开格子
void MainGame::autoUncover()
{
    for (int x = 0; x < tableRows; x++)
    {
        for (int y = 0; y < tableCols; y++)
        {
            //将翻开的空格子存入数组
			if (blocks[x][y].type == NONE && !blocks[x][y].isCovered)
            {
				noneList.append(QPoint(x, y));
            }
        }
    }

    //通过空格子坐标，获取空格子的周围一圈格子的坐标
	for (int i = 0; i < noneList.size(); i++)
    {
        for (int sideX = -1; sideX <= 1; sideX++)
        {
            for (int sideY = -1; sideY <= 1; sideY++)
            {
                //获取周围的格子
				int x = noneList[i].x() + sideX;
				int y = noneList[i].y() + sideY;

				if (x >= 0 && x < tableRows && y >= 0 && y < tableCols && !blocks[x][y].isMarked)
                {
                    //翻开没有标记的格子
					blocks[x][y].isCovered = false;
                }
            }
        }
    }
	noneList.clear();
}


//音乐播放
void MainGame::setMusic(){
    //音乐界面开启
     pMusic->show();
}

//鼠标点击事件
void MainGame::mousePressEvent(QMouseEvent* event)
{
    //获取点击的鼠标按键
    int clicked = event->button();

    //如果点击了鼠标且目前不处于透视状态
    if (clicked && !isCracked)
    {
        if (status == PLAYING)
        {
            //获取鼠标位置（相对于视窗）
            mouse = event->pos();

            //如果点击音乐图标
            if(mouse.x()>=screenWidth/2.25&&
               mouse.x()<=screenWidth/2.25+BLOCK_SIZE&&
               mouse.y()>=INFO_UPPER/1.5&&
               mouse.y()<= INFO_UPPER/1.5+BLOCK_SIZE&&
               clicked == Qt::LeftButton)
            {
                //音乐界面开启
                setMusic();
            }

            //一局仅可获得一次复活机会
            if(mouse.x()>=screenWidth/1.85&&
               mouse.x()<=screenWidth/1.85+BLOCK_SIZE&&
               mouse.y()>=INFO_UPPER/1.5&&
               mouse.y()<= INFO_UPPER/1.5+BLOCK_SIZE&&
               isHaveGetReborned==false&&
               clicked == Qt::LeftButton)
            {
                //复活机会无
                isHaveGetReborned=true;
                //广告弹窗
                pReborn->show();
                //绘制随机事件三
                for(int i=0;i<1;i++)
                {
                    //生成随机格子坐标
                    int randomX=std::rand()%100/(double)101*tableRows;
                    int randomY=std::rand()%100/(double)101*tableCols;

                    //如果该格子不是地雷格且不是随机事件一二格
                    if(blocks[randomX][randomY].type!=MINE&&
                       blocks[randomX][randomY].randomEventOne!=true&&
                       blocks[randomX][randomY].randomEventTwo!=true)
                    {
                        blocks[randomX][randomY].randomEventThree=true;
                    }
                    qDebug()<<randomX+1<<randomY+1;
                }
            }

            //位置不在游戏区域内，返回
			if (mouse.x() < MARGIN_X || mouse.x() > screenWidth - MARGIN_X) { return; }
			if (mouse.y() < MARGIN_Y || mouse.y() > screenHeight - MARGIN_X) { return; }

            //获取鼠标点击的格子的坐标
			int x = ((mouse.x() - MARGIN_X) / BLOCK_SIZE);
			int y = ((mouse.y() - MARGIN_Y) / BLOCK_SIZE);

            //点击了鼠标左键，点击的格子没有被翻开且没有被标记
			if (clicked == Qt::LeftButton && blocks[x][y].isCovered && !blocks[x][y].isMarked)
			{
                //如果格子不是地雷格，继续游戏
				if (blocks[x][y].type != MINE)
				{
					audio.click.stop();
                    audio.click.play();

                    //如果格子是随机事件一格子
                    if(blocks[x][y].randomEventOne==true)
                    {
                        for (int x = 0; x < tableRows; x++)
                        {
                            for (int y = 0; y < tableCols; y++)
                            {
                                //覆盖所有格子
                                pRandomEventOne->show();
                                blocks[x][y].isMarked=false;
                                blocks[x][y].isCovered=true;
                            }
                        }
                        //随机事件失效
                        blocks[x][y].randomEventOne=false;
                    }

                    //如果格子是随机事件二格子
                    if(blocks[x][y].randomEventTwo==true)
                    {
                        pRandomEventTwo->show();
                    }

                    //如果格子是随机事件三格子
                    if(blocks[x][y].randomEventThree==true)
                    {
                        pRandomEventThree->show();
                        //获得复活机会
                        isReborned=true;
                    }
                }

                //如果格子是地雷格
                else
                {
                    //如果没有复活机会，游戏结束
                    if(isReborned==false)
                        gameoverLose(x, y);
                    else
                    {
                        //如果有复活机会，游戏继续
                        isReborned=false;
                        blocks[x][y].isMarked=true;
                        flagCount -= 1;
                    }
                }

				blocks[x][y].isCovered = false;
			}

            //点击已翻开的数字格，周围格子变色提示
            else if(clicked==Qt::LeftButton&&!blocks[x][y].isCovered)
            {
                if(blocks[x][y].type == NUMBER)
                {
                    //依次获取周围的格子
                    for (int sideX = -1; sideX <= 1; sideX++)
                    {
                        for (int sideY = -1; sideY <= 1; sideY++)
                        {
                            int X = x + sideX;
                            int Y = y + sideY;

                            //如果格子没有被翻开且没有被标记
                            if (X >= 0 &&
                                X < tableRows &&
                                Y >= 0 &&
                                Y < tableCols &&
                                !blocks[X][Y].isMarked&&
                                blocks[X][Y].isCovered)
                            {
                                static QRect blockRect;
                                //设置格子块位置以及尺寸
                                blockRect.setX(X);
                                blockRect.setY(Y);
                                blockRect.setWidth(BLOCK_SIZE);
                                blockRect.setHeight(BLOCK_SIZE);
                                //输出格子坐标
                                qDebug()<<"("<<X+1<<","<<Y+1<<")";

                            }
                        }
                    }
                }
            }

            //点击了鼠标右键，点击的格子没有被翻开
			else if (clicked == Qt::RightButton && blocks[x][y].isCovered)
			{
				audio.click.stop();
				audio.click.play();

                //格子没有被标记，则打上标记
                if (!blocks[x][y].isMarked&&flagCount>0)
                {
                    blocks[x][y].isMarked = true;
                    flagCount -= 1;
                }
                //格子被标记了，则取消标记
                else if (blocks[x][y].isMarked)
				{
					blocks[x][y].isMarked = false;
					flagCount += 1;
				}
            }
        }

        //如果处于游戏暂停状态，则继续游戏
        else if (status == PAUSE)
        {
            audio.click.stop();
            audio.click.play();
            status = PLAYING;
        }
        //以上皆不是，则重新开始游戏
		else { restart(); }
    }
}

//鼠标离开事件
void MainGame::mouseReleaseEvent(QMouseEvent* event)
{
    //如果目前不处于透视状态
    if (!isCracked)
    {
        if (status == PLAYING)
        {
            //获取鼠标位置（相对于视窗）
            mouse = event->pos();

            //位置不在游戏区域内，返回
            if (mouse.x() < MARGIN_X || mouse.x() > screenWidth - MARGIN_X) { return; }
            if (mouse.y() < MARGIN_Y || mouse.y() > screenHeight - MARGIN_X) { return; }

            //获取鼠标点击的格子的坐标
            int x = ((mouse.x() - MARGIN_X) / BLOCK_SIZE);
            int y = ((mouse.y() - MARGIN_Y) / BLOCK_SIZE);

            //点击已翻开的数字格，周围格子变色提示
            if(!blocks[x][y].isCovered)
            {
                if(blocks[x][y].type == NUMBER)
                {
                    //依次获取周围的格子
                    for (int sideX = -1; sideX <= 1; sideX++)
                    {
                        for (int sideY = -1; sideY <= 1; sideY++)
                        {
                            int X = x + sideX;
                            int Y = y + sideY;

                            //如果格子没有被翻开且没有被标记
                            if (X >= 0 &&
                                X < tableRows &&
                                Y >= 0 &&
                                Y < tableCols &&
                                !blocks[X][Y].isMarked&&
                                blocks[X][Y].isCovered)
                            {
                                static QRect blockRect;
                                //设置格子块位置以及尺寸
                                blockRect.setX(X);
                                blockRect.setY(Y);
                                blockRect.setWidth(BLOCK_SIZE);
                                blockRect.setHeight(BLOCK_SIZE);
                                //输出格子坐标
                                qDebug()<<"("<<X+1<<","<<Y+1<<")";

                            }
                        }
                    }
                }
            }
        }
    }
}

//键盘事件
void MainGame::keyPressEvent(QKeyEvent *event)
{
    //按下Z，开启作弊功能
    if (event->key() == Qt::Key_Z && status == PLAYING)
    {
        //透视
        isCracked = true;
        isHaveCracked = true;
    }

    //点击R，重新开始游戏
	if (event->key() == Qt::Key_R) { restart(); }

    //点击P，暂停游戏
	if (event->key() == Qt::Key_P) { setPause(); }
}

//键盘事件
void MainGame::keyReleaseEvent(QKeyEvent *event)
{
    //抬起Z，关闭作弊功能
    if (event->key() == Qt::Key_Z && status == PLAYING)
    {
        isCracked = false;
    }
}

//绘制背景
void MainGame::displayBackground(QPainter& painter)
{
    //创建矩形区域
	static QRect backgroundRect;

    //填充矩形区域
	painter.fillRect(0, 0, screenWidth, screenHeight, QBrush(colors.white));

    //设置子区域位置以及尺寸
	backgroundRect.setX(MARGIN_X - BORDER);
	backgroundRect.setY(MARGIN_Y - BORDER);
	backgroundRect.setWidth(tableWidth + 2 * BORDER);
	backgroundRect.setHeight(tableHeight + 2 * BORDER);

    //填充子区域
	painter.fillRect(backgroundRect, QBrush(colors.black));

    //设置子区域位置以及尺寸
	backgroundRect.setX(MARGIN_X - BLOCK_BORDER);
	backgroundRect.setY(MARGIN_Y - BLOCK_BORDER);
	backgroundRect.setWidth(tableWidth + 2 * BLOCK_BORDER);
	backgroundRect.setHeight(tableHeight + 2 * BLOCK_BORDER);

    //填充子区域
	painter.fillRect(backgroundRect, QBrush(colors.gray));
}

//绘制格子块
void MainGame::displayBlock(QPainter& painter)
{
    //创建矩形区域
	static QRect blockRect;

    //依次绘制格子块
	for (int x = 0; x < tableRows; x++)
    {
		for (int y = 0; y < tableCols; y++)
        {
            //设置格子块位置以及尺寸
			blockRect.setX(MARGIN_X + x * BLOCK_SIZE);
			blockRect.setY(MARGIN_Y + y * BLOCK_SIZE);
			blockRect.setWidth(BLOCK_SIZE);
			blockRect.setHeight(BLOCK_SIZE);

            //如果处于暂停状态
			if (status == PAUSE)
			{
                //将所有格子暂时绘制成盖上的样子，继续游戏时再显示已翻开的格子
				painter.drawPixmap(blockRect, images.cover);
				continue;
			}

            //如果格子未被点击过（即未翻开）且不处于透视状态
			if (blocks[x][y].isCovered && !isCracked)
            {
                //将格子绘制成盖上的样子
				painter.drawPixmap(blockRect, images.cover);

                //如果非地雷格子被标记
				if (blocks[x][y].isError)
                {
                    //将格子绘制成错误标记的样子
					painter.drawPixmap(blockRect, images.error);
                }

                //如果格子被标记
				else if (blocks[x][y].isMarked)
                {
                    //将格子绘制成标记的样子
					painter.drawPixmap(blockRect, images.flag);
                }
				continue;
            }

            //绘制格子块
			painter.drawPixmap(blockRect, images.block);

            //如果格子是数字格
			if (blocks[x][y].type == NUMBER)
			{
                //绘制成数字格的样子
				painter.drawPixmap(blockRect, images.number[blocks[x][y].number - 1]);
			}

            //如果格子是地雷格
			else if (blocks[x][y].type == MINE)
			{
                //绘制成地雷格的样子
				painter.drawPixmap(blockRect, (blocks[x][y].isTouched) ? images.mineError : images.mine);
			}
        }
    }
}

//绘制信息
void MainGame::displayInfo(QPainter& painter)
{
	static QString text;

    //绘制音乐格子
    static QRect blockRect;
    blockRect.setX(screenWidth/2.25);
    blockRect.setY(INFO_UPPER/1.5);
    blockRect.setWidth(BLOCK_SIZE);
    blockRect.setHeight(BLOCK_SIZE);
    painter.drawPixmap(blockRect, images.music);

    //绘制广告格子
    blockRect.setX(screenWidth/1.85);
    blockRect.setY(INFO_UPPER/1.5);
    blockRect.setWidth(BLOCK_SIZE);
    blockRect.setHeight(BLOCK_SIZE);
    painter.drawPixmap(blockRect, images.tip);

    //根据游戏是否暂停绘制花费时间信息
	switch (status)
    {
        //如果游戏暂停，则在花费时间后面加上“(PAUSE)”
		case PAUSE: text = QString("TIME: %1 (PAUSE)").arg(timeDuring); break;
		default: text = QString("TIME: %1").arg(timeDuring); break;
    }
    //绘制位置以及内容
	painter.drawText(MARGIN_X, INFO_UPPER, text);

    //根据游戏状态绘制状态信息
    switch (status)
    {
        //如果游戏失败，则绘制“BOOM!”
		case OVER: text = "BOOM!"; break;

        //如果游戏成功，则绘制“Success!”
		case WIN: text = "Success!"; break;

        //如果处于游戏状态，则绘制地雷数量（即旗子剩余数量）
		default: text = QString("MINES: %1").arg(flagCount); break;
    }
    //绘制位置以及内容
	painter.drawText(screenWidth - INFO_WIDTH, INFO_UPPER, text);
}

//绘制界面
void MainGame::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
    displayBackground(painter);
    displayBlock(painter);
    displayInfo(painter);
}
