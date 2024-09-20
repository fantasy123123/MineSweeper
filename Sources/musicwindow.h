#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "listwidget.h"
#include <QMouseEvent>

QT_BEGIN_NAMESPACE

//定义音乐播放器类
namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

//音乐播放器主要界面
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

         //界面和逻辑初始化
        void initplayer();

        //实现开始按钮转换
        void voiplay();

        //实现暂停按钮转换
        void voistop();

        //接收拖进来的音乐文件
        void dragEnterEvent(QDragEnterEvent *event);

        //解析拖进来的文件并播放
        void dropEvent(QDropEvent *event);

    protected:
        //鼠标拖动窗体时隐藏歌单，拖动完成后在显示
        //void mouseMoveEvent(QMouseEvent *event);
        //void mousePressEvent(QMouseEvent *event);
        //void mouseReleaseEvent(QMouseEvent *event);
        //鼠标滚轮上下滚动实现音量调节
        void wheelEvent(QWheelEvent *event);

    private slots:
        //点击按钮触发事件，采用此种命名方式无需写槽函数也可触发

        //一个按键实现播放暂停两个操作
        void on_pushButton_4_clicked();

        //打开对话框选取特定的音乐文件并播放
        void on_pushButton_clicked();

        //点击按钮后显示/隐藏播放列表
        void on_pushButton_2_clicked();

    private:
        Ui::MainWindow *ui;

        //播放器指针
        QMediaPlayer *voi;

        //播放菜单指针
        QMediaPlaylist *voilist;

        //歌单窗口
        ListWidget *list;

        //初始音量为70%
        int volume = 70;

};
#endif // MAINWINDOW_H
