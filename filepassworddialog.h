#ifndef FILEPASSWORDDIALOG_H
#define FILEPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class FilePasswordDialog;
}

class FilePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilePasswordDialog(QWidget *parent = nullptr);
    ~FilePasswordDialog();
    QString getPass();

private slots:
    void on_btnOk_clicked();

private:
    Ui::FilePasswordDialog *ui;
};

#endif // FILEPASSWORDDIALOG_H
