#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "creditcalculator.h"

//подключение си
#ifdef __cplusplus
extern "C" {
#endif

#include "../Backend/calculator.h"

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CreditCalculator *window;

private slots:
    void digit_numbers();
    void pi_num();
    void exp_num();
    void binary_operators();
    void operators();
    void functions();
    void on_pushButton_clear();
    void on_pushButton_graph();
    void on_go_to_credit();
    void on_pushButton_mult();
    void on_pushButton_divide();
    void get_result();
};
#endif // MAINWINDOW_H
