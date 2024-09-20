#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QDialog>

QT_BEGIN_NAMESPACE

//定义反馈类
namespace Ui {
    class FeedBackDialog;
}

QT_END_NAMESPACE

class FeedBackDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::FeedBackDialog *ui;

    private:
        //设置对话标志
        void setDialogFlags();

    public:
        explicit FeedBackDialog(QWidget *parent = nullptr);
        ~FeedBackDialog();
};

#endif
