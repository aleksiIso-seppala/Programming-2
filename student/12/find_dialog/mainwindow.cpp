#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QFile>
#include <fstream>

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

    std::string stdfilename = file_input_.toStdString();
    std::ifstream file(stdfilename);
    QString line;
    bool word_found = false;
    std::string row;
    while (getline(file, row)){
        word_in_std_ = word_input_.toStdString();
        std::locale loc;
        if ( not ui->matchCheckBox->isChecked()){
            for (auto elem : row){
                std::tolower(elem, loc);
            }
            std::for_each(word_in_std_.begin(), word_in_std_.end(), [](char & c){
                c = ::tolower(c);
            });
        }
        std::size_t found = row.find(word_in_std_);
        if (found != std::string::npos)
        {
            word_found = true;
            break;
        }
    }

    file.close();
    if(word_found){
        ui->textBrowser->setText("Word found");
    }
    else{
        ui->textBrowser->setText("Word not found");
    }
}

void MainWindow::on_fileLineEdit_editingFinished()
{
    file_input_ = ui->fileLineEdit->text();
}

void MainWindow::on_keyLineEdit_editingFinished()
{
     word_input_ = ui->keyLineEdit->text();
}

