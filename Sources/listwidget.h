#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QMainWindow>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE

//定义音乐界面的歌单类
namespace Ui {
    class ListWidget;
}

QT_END_NAMESPACE

class ListWidget : public QMainWindow
{
    Q_OBJECT

    public:
        explicit ListWidget(QWidget *parent = nullptr);
        ~ListWidget();

        //将歌曲添加到默认歌单
        void additem(QString str);

    private:
        Ui::ListWidget *ui;
};

#endif
