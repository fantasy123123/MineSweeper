#include "musicwindow.h"
#include "ui_musicwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QMediaPlaylist>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QList>
#include <QMimeDatabase>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化界面
    initplayer();
}

MainWindow::~MainWindow()
{    
    delete ui;
}

//初始化界面
void MainWindow::initplayer()
{
    //打开接受拖动事件
    this->setAcceptDrops(true);

    //暂时取消重置歌单的功能
   this->ui->toolButton->hide();

    //如果没有选择文件，无法播放
    ui->pushButton_4->setEnabled(false);

    //播放音乐相关
    voi = new QMediaPlayer(this);
    voi->setVolume(volume);
    voilist = new QMediaPlaylist;

    //创建播放菜单
    this->list = new  ListWidget (this);

    //默认循环播放列表中的歌曲
    voilist->setPlaybackMode(QMediaPlaylist::Loop);
}

//实现播放按钮的转换
void MainWindow::voiplay()
{
    //播放音乐
    voi->play();
    //将按钮相关信息转换成暂停
    this->ui->pushButton_4->setToolTip("暂停");
    //更换成播放按钮图片
    this->ui->pushButton_4->setIcon(QIcon(":/Images/play.png"));
}

//实现播放按钮的转换
void MainWindow::voistop()
{
    //暂停音乐
    voi->pause();
    //将按钮相关信息转换成播放
    this->ui->pushButton_4->setToolTip("播放");
    //更换成暂停按钮图片
    this->ui->pushButton_4->setIcon(QIcon(":/Images/pause.png"));
}

//识别音乐是否正在播放
void MainWindow::on_pushButton_4_clicked()
{
    //如果音乐在播放
    if(voi->state() == QMediaPlayer::PlayingState)
    {
        //暂停音乐
        this->voistop();
    }
    //如果音乐没有在播放
    else
    {
        //播放音乐
        this->voiplay();
    }

}

//选取要播放的音乐文件并将文件名添加到歌单窗口
void MainWindow::on_pushButton_clicked()
{
    //筛选文件，只能选择mp3、wav、mpga格式的文件
    QList<QUrl> path =  QFileDialog::getOpenFileUrls(this,tr("请选择要播放的音乐"),QUrl( "C:/"),"music(*.mp3 *.wav *.mpga)");

    //解析文件信息的临时播放器
    QMediaPlayer tmpPlayer;

    //逐一解析文件信息
    foreach(QUrl i,path )
    {
        //添加到播放列表
        voilist->addMedia(i);

        //将歌名添加到歌单窗口
        tmpPlayer.setMedia(i);

        //将歌名添加到默认播放列表
        if(tmpPlayer.isMetaDataAvailable())
        {
            //将歌名添加到默认播放列表
            list->additem(tmpPlayer.metaData(QStringLiteral("Title")).toString() );
        }     
    }

    //播放音乐
    if(!path.isEmpty())
    {
        //正在播放或暂停状态添加新文件取消从头播放，改为继续当前的播放
        if(voi->state() != QMediaPlayer::PlayingState && voi->state() != QMediaPlayer::PausedState)
        {
            //播放过程中向voilist会导致从头开始播放
            voi->setPlaylist(voilist);
            //改为继续当前的播放
            this->voiplay();
            //恢复按钮的功能
            ui->pushButton_4->setEnabled(true);
        }
    }

    //如果没有选取音乐
    else
    {
       //提示
       QMessageBox::warning(this,tr("温馨提示"),tr("你没有选择音乐文件\n请重新选择"));
    }
}

//实现拖动多个文件的响应
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    //如果文件有url
    if(event->mimeData()->hasUrls())
    {
        //接收文件
        event->acceptProposedAction();
        //拖动添加新文件时隐藏歌单窗口
        list->hide();
    }
    //如果文件没有url
    else
    {
        //忽略此次事件
        event->ignore();
        //展示歌单窗口
        list->show();
    }
}

//从拖动的文件中提取urls进行播放
void MainWindow::dropEvent(QDropEvent *event)
{
    //拖动接收的文件信息
    const QMimeData *mimedata = event->mimeData();

    //如果信息中有url
    if(mimedata->hasUrls())
    {
       //获取全部文件的url
       QList <QUrl> path = mimedata->urls();

       //解析文件信息的临时播放器
       QMediaPlayer tmpPlayer;
       QMimeDatabase db;

       //添加到播放列表
       foreach(QUrl i,path )
       {
           //提取文件信息
           QMimeType mime = db.mimeTypeForFile(i.toLocalFile());
           //筛选音频文件的格式
           //格式是mp3\mpeg\wav就添加到播放列表
           if(mime.name()=="audio/mpeg" || mime.name()=="audio/wav")
           {
               //添加到播放列表
               voilist->addMedia(i);

               //将歌名添加到歌单窗口
               tmpPlayer.setMedia(i);

               //将歌名添加到默认播放列表
               if(tmpPlayer.isMetaDataAvailable())
               {
                   //将歌名添加到默认播放列表
                   list->additem(tmpPlayer.metaData(QStringLiteral("Title")).toString() );
               }
           }

           //其它格式就不添加
           else
           {
               //提示
               QMessageBox::warning(this,tr("温馨提示"),tr("文件格式错误！"));
           }
       }

       //将新加入的第一个文件作为即将播放的音频
       if(voi->state() != QMediaPlayer::PlayingState && voi->state() != QMediaPlayer::PausedState)
       {
           //将播放列表添加音乐
           voi->setPlaylist(voilist);
           //添加音乐
           this->voiplay();
           //恢复按钮的功能
           ui->pushButton_4->setEnabled(true);
       }
    }
    //如果没有选取文件
    else
    {
       //提示
       QMessageBox::warning(this,tr("温馨提示"),tr("你没有选择音乐文件\n请重新选择"));
    }
}

//点击按钮后显示或者关闭播放列表
void MainWindow::on_pushButton_2_clicked()
{
    //将播放列表展示在播放器下方
    list->setGeometry(this->geometry().x(),this->geometry().y() + this->height(),this->width(),300);

    //如果播放列表处于隐藏状态
    if(list->isHidden())
    {
        //展示列表
        list->show();
        //更新信息
        this->ui->pushButton_2->setToolTip("隐藏歌单");

        //将焦点聚焦到音乐主界面（否则没有”查看歌单“的提示）
        this->activateWindow();
    }
    //如果播放列表处于隐藏状态
    else
    {
        //隐藏列表
        list->hide();
        //更新信息
        this->ui->pushButton_2->setToolTip("查看歌单");
    }
}

//鼠标滚轮上下滚动调节音量
void MainWindow::wheelEvent(QWheelEvent *event)
{
    //滚轮向上调大音量
    if(event->delta() > 0 && volume < 100)
    {
        //音量增大
        volume +=  5;
        voi->setVolume(volume);
    }

    //滚轮向下调小音量
    else if(event->delta() < 0 && volume >0 )
    {
        //音量减小
        volume -= 5;
        voi->setVolume(volume);
    }
}
