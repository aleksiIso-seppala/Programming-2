#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::is_file()
{

    QFile file(file_input_);
    if (not file.exists()){
        return false;
    }
    else{
        file.close();
        return true;
    }

}

void MainWindow::on_findPushButton_clicked()
{
    if (not is_file()){
        ui->textBrowser->setText("File not found");
        return;
    }
    else{
        ui->textBrowser->setText("File found");
    }

    if(word_input_ == ""){
        return;
    }

    QFile file(file_input_);
    QString line;
    bool word_found = false;
    file.open(QIODevice::ReadOnly);
    while (not file.atEnd()){

        QString word_in_file = file.readLine();
        QString word_to_find = word_input_;
//        if (not is_match_case_){
//            QString word_to_find = word_input_.toLower();
//            QString word_in_file = line.toLower();
//        }
        if (word_to_find == word_in_file){
            ui->textBrowser->setText("loyty");
            word_found = true;
            break;
        }

    }
    file.close();
//    if(word_found){
//        ui->textBrowser->setText("Word found");
//    }
//    else{
//        ui->textBrowser->setText("Word not found");
//    }
}

void MainWindow::on_fileLineEdit_editingFinished()
{
    file_input_ = ui->fileLineEdit->text();
}

void MainWindow::on_keyLineEdit_editingFinished()
{
     word_input_ = ui->keyLineEdit->text();
}
