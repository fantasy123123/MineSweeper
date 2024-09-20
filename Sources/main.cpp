#include "minesweeper.h"
#include <QElapsedTimer>
#include "advertisement.h"

void Delay_MSec()
{
    //定义一个新的事件循环
    QEventLoop loop;
    //创建单次定时器，槽函数为事件循环的退出函数
    QTimer::singleShot(5000, &loop, SLOT(quit()));
    //事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
    loop.exec();
}


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainGame game;

    //展示广告
    advertisement* ad;
    ad=new advertisement();
    ad->show();

    //广告停留五秒
    Delay_MSec();

    //隐藏广告，开始游戏
    ad->hide();
    delete ad;

	game.init();
	game.show();

    return app.exec();
}

