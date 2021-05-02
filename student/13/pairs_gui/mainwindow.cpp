#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <iostream>


using namespace std;

string ALPHABETS = "AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ";
int TIME = 1000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , timer(new QTimer(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::on_timer_timeout);
}


MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::calculate_factors()
{

    for(int i = 1; i * i <= number_of_cards_; ++i)
    {
        if(number_of_cards_ % i == 0)
        {
            rows_ = i;
        }
    }
    columns_ = number_of_cards_ / rows_;
    return;

}

bool MainWindow::is_valid_card_number(){

    if (number_of_cards_ % 2 != 0){
        ui->textBrowser->setText("Card number must be divisible by 2");
        return false;
    }
    if (number_of_cards_ > 26){
        ui->textBrowser->setText("Card number must be 26 or lower");
        return false;
    }
    return true;
}

void MainWindow::on_start_button_clicked()
{
    game_loop();
}

void MainWindow::set_up_board(){

    string mystr = ALPHABETS.substr(0, number_of_cards_);
    random_shuffle(mystr.begin(),mystr.end());
    int alphabet_index = 0;

    for (int i=0; i<rows_; i++){
        for(int j=0; j<columns_; j++){
            QPushButton* push_button = new QPushButton(this);
        }
    }

}

void MainWindow::game_loop(){

    if (not is_valid_card_number()){
        return;
    }

    calculate_factors();


    timer->start(TIME);
    ui->textBrowser->setText("Game started");
}

void MainWindow::on_card_number_editingFinished()
{
    number_of_cards_ = ui->card_number->text().toInt();
}

void MainWindow::on_timer_timeout()
{
    int current_mins = ui->lcd_number_min->intValue();
    int current_secs = ui->lcd_number_sec->intValue();

    if (current_secs == 59){
        update_display(current_mins+1,0);
    }
    else{
        update_display(current_mins, current_secs+1);
    }
}

void MainWindow::update_display(int mins, int secs)
{
    ui->lcd_number_min->display(mins);
    ui->lcd_number_sec->display(secs);
}
