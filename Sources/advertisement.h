#ifndef ADVERTISEMENT_H
#define ADVERTISEMENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE

//定义广告类
namespace Ui {
class advertisement;
}

QT_END_NAMESPACE

class advertisement : public QWidget
{
    Q_OBJECT

public:
    explicit advertisement(QWidget *parent = nullptr);
    ~advertisement();

private:
    Ui::advertisement *ui;
};

#endif
