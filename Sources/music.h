#ifndef MUSIC_H
#define MUSIC_H

#include <QDialog>

namespace Ui {
class MusicDialog;
}

class MusicDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MusicDialog(QWidget *parent = nullptr);
    ~MusicDialog();

private:
    Ui::MusicDialog *ui;

private:
    //设置对话标志
    void setDialogFlags();
};

#endif // MUSIC_H
