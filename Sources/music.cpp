#include "music.h"
#include "ui_music.h"

MusicDialog::MusicDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MusicDialog)
{
    ui->setupUi(this);
    setDialogFlags();
}

MusicDialog::~MusicDialog()
{
    delete ui;
}

void MusicDialog::setDialogFlags()
{
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}
