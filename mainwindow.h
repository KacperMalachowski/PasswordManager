#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qtablewidget.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_leSearch_textChanged(const QString &arg1);

    void on_btnAdd_clicked();

    void on_tablePasswords_itemSelectionChanged();

    void on_btnEditEntry_clicked();

    void on_btnDelete_clicked();

    void on_btnClear_clicked();

    void on_btnSwitchPawdVis_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    bool showPasswords = false;
    QString loadedFilePath = "";
};
#endif // MAINWINDOW_H
