#ifndef RANDOMEVENTONE_H
#define RANDOMEVENTONE_H

#include <QWidget>

QT_BEGIN_NAMESPACE

//定义随机事件一类
namespace Ui {
class randomEventOne;
}

QT_END_NAMESPACE

class randomEventOne : public QWidget
{
    Q_OBJECT

    private:
        Ui::randomEventOne *ui;

    public:
        explicit randomEventOne(QWidget *parent = nullptr);
        ~randomEventOne();
};

#endif
