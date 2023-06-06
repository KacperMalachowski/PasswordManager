#include "entrydialog.h"
#include "ui_entrydialog.h"

EntryDialog::EntryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryDialog)
{
    ui->setupUi(this);
}

EntryDialog::~EntryDialog()
{
    delete ui;
}

QString EntryDialog::getName()
{
    return ui->leName->text();
}

QString EntryDialog::getUsername()
{
    return ui->leUsername->text();
}

QString EntryDialog::getPassword()
{
    return ui->lePassword->text();
}

QString EntryDialog::getURL()
{
    return ui->leUrl->text();
}

void EntryDialog::setName(QString txt)
{
    ui->leName->setText(txt);
}

void EntryDialog::setUsername(QString txt)
{
    ui->leUsername->setText(txt);
}

void EntryDialog::setPassword(QString txt)
{
    ui->lePassword->setText(txt);
}

void EntryDialog::setURL(QString txt)
{
    ui->leUrl->setText(txt);
}

void EntryDialog::on_btnCancel_clicked()
{
    edited = false;
    close();
}


void EntryDialog::on_btnAdd_clicked()
{
    edited = true;
    close();
}


void EntryDialog::on_btnGeneratePass_clicked()
{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const int length = 10;

    QString randomString;
    for (int i = 0; i < length; ++i) {
        int index = rand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }

    ui->lePassword->setText(randomString);
}

