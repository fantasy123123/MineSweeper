#ifndef RANDOMEVENTTWO_H
#define RANDOMEVENTTWO_H

#include <QWidget>

QT_BEGIN_NAMESPACE

//定义随机事件二类
namespace Ui {
class randomEventTwo;
}

QT_END_NAMESPACE

class randomEventTwo : public QWidget
{
    Q_OBJECT

    private:
        Ui::randomEventTwo *ui;

    public:
        explicit randomEventTwo(QWidget *parent = nullptr);
        ~randomEventTwo();

};

#endif
