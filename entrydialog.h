#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include <QDialog>

namespace Ui {
class EntryDialog;
}

class EntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EntryDialog(QWidget *parent = nullptr);
    ~EntryDialog();
    QString getName();
    QString getUsername();
    QString getPassword();
    QString getURL();
    void setName(QString txt);
    void setUsername(QString txt);
    void setPassword(QString txt);
    void setURL(QString txt);
    bool edited;


private slots:
    void on_btnCancel_clicked();

    void on_btnAdd_clicked();

    void on_btnGeneratePass_clicked();

private:
    Ui::EntryDialog *ui;
};

#endif // ENTRYDIALOG_H
