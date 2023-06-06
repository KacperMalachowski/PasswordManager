#include <QFileDialog>
#include <QMessageBox>
#include "filepassworddialog.h"
#include "mainwindow.h"
#include "entrydialog.h"
#include "simplecrypt.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList headers;
    headers << "Name" << "Login" << "Password" << "URL";

    ui->tablePasswords->setColumnCount(4);
    ui->tablePasswords->setHorizontalHeaderLabels(headers);
    ui->tablePasswords->verticalHeader()->setSectionsMovable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_leSearch_textChanged(const QString &arg1)
{
    QTableWidget* table = ui->tablePasswords;

    for (int rowIdx = 0; rowIdx < table->rowCount(); ++rowIdx) {
        bool match = false;
        for (int colIdx = 0; colIdx < table->columnCount(); ++colIdx) {
            QTableWidgetItem* item = table->item(rowIdx, colIdx);

            if (item->text().contains(arg1)) {
                match = true;
                break;
            }

        }
        table->setRowHidden(rowIdx, !match);
    }
}


void MainWindow::on_btnAdd_clicked()
{
    EntryDialog* dialog = new EntryDialog();
    dialog->exec();
    if (dialog->edited) {
        QTableWidget* table = ui->tablePasswords;
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(dialog->getName()));
        table->setItem(row, 1, new QTableWidgetItem(dialog->getUsername()));
        if (!showPasswords) {
            QTableWidgetItem* item = new QTableWidgetItem();
            QString pass = dialog->getPassword();
            item->setWhatsThis(pass);
            item->setText("***");
            table->setItem(row, 2, item);
        } else {
            table->setItem(row, 2, new QTableWidgetItem(dialog->getPassword()));
        }
        table->setItem(row, 3, new QTableWidgetItem(dialog->getURL()));
    }
}


void MainWindow::on_tablePasswords_itemSelectionChanged()
{
    ui->btnEditEntry->setEnabled(!ui->btnEditEntry->isEnabled());
    ui->btnAdd->setEnabled(!ui->btnAdd->isEnabled());
    ui->btnDelete->setEnabled(!ui->btnDelete->isEnabled());
}


void MainWindow::on_btnEditEntry_clicked()
{
    QTableWidget* table = ui->tablePasswords;
    int selectedRow = table->selectedItems()[0]->row();
    EntryDialog* dialog = new EntryDialog();
    dialog->setName(table->item(selectedRow, 0)->text());
    dialog->setUsername(table->item(selectedRow, 1)->text());
    dialog->setPassword(table->item(selectedRow, 2)->text());
    dialog->setURL(table->item(selectedRow, 3)->text());
    dialog->exec();
    if (dialog->edited) {
        table->setItem(selectedRow, 0, new QTableWidgetItem(dialog->getName()));
        table->setItem(selectedRow, 1, new QTableWidgetItem(dialog->getUsername()));
        if (!showPasswords) {
            QTableWidgetItem* item = new QTableWidgetItem();
            QString pass = dialog->getPassword();
            item->setWhatsThis(pass);
            item->setText("***");
            table->setItem(selectedRow, 2, item);
        } else {
            table->setItem(selectedRow, 2, new QTableWidgetItem(dialog->getPassword()));
        }
        table->setItem(selectedRow, 3, new QTableWidgetItem(dialog->getURL()));
    }
}


void MainWindow::on_btnDelete_clicked()
{
    QTableWidget* table = ui->tablePasswords;
    int selectedRow = table->selectedItems()[0]->row();
    table->removeRow(selectedRow);
}


void MainWindow::on_btnClear_clicked()
{
    QTableWidget* table = ui->tablePasswords;
    for (int i = 0; i < table->rowCount(); ++i) {
        table->removeRow(i);
    }
}


void MainWindow::on_btnSwitchPawdVis_clicked()
{
    QTableWidget* table = ui->tablePasswords;
    if (showPasswords) {
        ui->btnSwitchPawdVis->setText("Show Passwords");
        showPasswords = false;
        for (int i = 0; i < table->rowCount(); ++i) {
            QTableWidgetItem* item = table->item(i, 2);
            QString pass = item->text();
            item->setText("***");
            item->setWhatsThis(pass);
            table->setItem(i, 2, item);
        }
    } else {
        ui->btnSwitchPawdVis->setText("Hide Passwords");
        showPasswords = true;
        for (int i = 0; i < table->rowCount(); ++i) {
            QTableWidgetItem* item = table->item(i, 2);
            item->setText(item->whatsThis());
            table->setItem(i, 2, item);
        }
    }
}


void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Password File"), "", tr("PassMan (*.pssm);;All Files (*)"));

    if (filename.isEmpty()) {
        return;
    }

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    FilePasswordDialog* fpd = new FilePasswordDialog();

    fpd->exec();

    QString pass = fpd->getPass();

    QString data;
    QTextStream in(&file);

    data.append(in.readAll());

    QStringList lines = data.split("\n");

    SimpleCrypt* decrypt = new SimpleCrypt(2200);
    QString filePassDecrypted = decrypt->decryptToString(lines[0]);

    if (filePassDecrypted != pass) {
        QMessageBox::information(this, tr("Unable to open file"), tr("passwords mismatch"));
        return;
    }

    SimpleCrypt* fileDecryptor = new SimpleCrypt(pass.toUInt());

    QTableWidget* table = ui->tablePasswords;
    for (int i = 1; i < lines.count() -1; ++i) {
        QStringList values = fileDecryptor->decryptToString(lines[i]).split("|");
        if (values.count() != 4) {
            QMessageBox::information(this, tr("Unable to read file"), tr("data seams corrupted"));
            return;
        }
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(values[0]));
        table->setItem(row, 1, new QTableWidgetItem(values[1]));
        if (!showPasswords) {
            QTableWidgetItem* item = new QTableWidgetItem();
            QString passEntry = values[2];
            item->setWhatsThis(passEntry);
            item->setText("***");
            table->setItem(row, 2, item);
        } else {
            table->setItem(row, 2, new QTableWidgetItem(values[2]));
        }
        table->setItem(row, 3, new QTableWidgetItem(values[3]));
    }
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Open Password File"), "", tr("PassMan (*.pssm);;All Files (*)"));

    if (filename.isEmpty()) {
        return;
    }

    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    FilePasswordDialog* fpd = new FilePasswordDialog();

    fpd->exec();

    QString pass = fpd->getPass();


    SimpleCrypt* encrypt = new SimpleCrypt(2200);
    QString filePassEncrypted = encrypt->encryptToString(pass);

    SimpleCrypt* fileEncrypt = new SimpleCrypt(pass.toUInt());
    QString output = "";
    QTableWidget* table = ui->tablePasswords;
    for (int i = 0; i < table->rowCount(); ++i) {
        QString tmp;
        tmp.append(table->item(i, 0)->text()).append("|");
        tmp.append(table->item(i, 1)->text()).append("|");
        if (!showPasswords) {
            tmp.append(table->item(i, 2)->whatsThis().append("|"));
        } else {
            tmp.append(table->item(i, 2)->text()).append("|");
        }
        tmp.append(table->item(i, 3)->text());
        output.append(fileEncrypt->encryptToString(tmp));
        output.append("\n");
    }

    QTextStream out(&file);
    out << filePassEncrypted << "\n" << output;

    file.close();
}

