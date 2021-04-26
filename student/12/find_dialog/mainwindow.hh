#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

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
    bool is_file();

private slots:

    void on_fileLineEdit_editingFinished();

    void on_findPushButton_clicked();

    void on_keyLineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    QString file_input_;
    QString word_input_;
    bool is_match_case_ = true;
    std::string word_in_std_;
};
#endif // MAINWINDOW_HH
