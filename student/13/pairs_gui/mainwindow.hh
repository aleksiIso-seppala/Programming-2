#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer* timer;

    void calculate_factors();
    void game_loop();
    bool is_valid_card_number();
    void set_up_board();

private slots:
    void on_start_button_clicked();

    void on_card_number_editingFinished();

    void on_timer_timeout();
    void update_display(int, int);

private:
    Ui::MainWindow *ui;
    int number_of_cards_ = 0;
    int columns_ = 1;
    int rows_ = 1;
};
#endif // MAINWINDOW_HH
