#ifndef REBORN_H
#define REBORN_H

#include <QWidget>

QT_BEGIN_NAMESPACE

//定义复活类
namespace Ui {
class reborn;
}

QT_END_NAMESPACE

class reborn : public QWidget
{
    Q_OBJECT

    private:
        Ui::reborn *ui;

    public:
        explicit reborn(QWidget *parent = nullptr);
        ~reborn();
};

#endif
