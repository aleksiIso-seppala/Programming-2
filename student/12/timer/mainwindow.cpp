#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(new QTimer(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::on_startButton_clicked);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::on_stopButton_clicked);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::on_resetButton_clicked);

    connect(timer, &QTimer::timeout, this, &MainWindow::on_timer_timeout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    timer->start(100);
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}

void MainWindow::on_resetButton_clicked()
{

}

void MainWindow::on_closeButton_clicked()
{

}

void MainWindow::on_timer_timeout()
{
    int current_mins = ui->lcdNumberMin->intValue();
    int current_secs = ui->lcdNumberSec->intValue();

    if(current_secs == 59)
    {
        ui->lcdNumberMin->display(current_mins + 1);
        ui->lcdNumberSec->display(0);
    }
    else
    {
        ui->lcdNumberSec->display(current_secs + 1);
    }
}
