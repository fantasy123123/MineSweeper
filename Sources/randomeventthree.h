#ifndef RANDOMEVENTTHREE_H
#define RANDOMEVENTTHREE_H

#include <QWidget>

QT_BEGIN_NAMESPACE

//定义随机事件三
namespace Ui {
class randomEventThree;
}

QT_END_NAMESPACE

class randomEventThree : public QWidget
{
    Q_OBJECT

    private:
        Ui::randomEventThree *ui;

    public:
        explicit randomEventThree(QWidget *parent = nullptr);
        ~randomEventThree();

};

#endif
