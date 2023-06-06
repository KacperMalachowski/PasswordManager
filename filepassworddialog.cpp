#include "filepassworddialog.h"
#include "ui_filepassworddialog.h"

FilePasswordDialog::FilePasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilePasswordDialog)
{
    ui->setupUi(this);
}

FilePasswordDialog::~FilePasswordDialog()
{
    delete ui;
}

QString FilePasswordDialog::getPass()
{
    return ui->spinBox->text();
}

void FilePasswordDialog::on_btnOk_clicked()
{
    close();
}

