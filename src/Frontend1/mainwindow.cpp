#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Backend/calculator.h"
#define length 256


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_pi, SIGNAL(clicked()), this, SLOT(pi_num()));
    connect(ui->pushButton_exp, SIGNAL(clicked()), this, SLOT(exp_num()));


    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(binary_operators()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(binary_operators()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(on_pushButton_divide()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(on_pushButton_mult()));
    connect(ui->pushButton_power, SIGNAL(clicked()), this, SLOT(binary_operators()));



    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(functions()));


    connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(on_pushButton_clear()));
    connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(get_result()));
    //graphic
    connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(on_pushButton_graph()));
    //credit
    connect(ui->go_to_credit, SIGNAL(clicked()), this, SLOT(on_go_to_credit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_numbers(){
    QPushButton *button = (QPushButton *)sender();
    QString string_all;
    string_all = (ui->lineEdit->text() + button->text());
    ui->lineEdit->setText(string_all);
}

void MainWindow::on_pushButton_mult()
{
    QPushButton *button = (QPushButton *)sender();
    QString string_all;
    string_all = (ui->lineEdit->text() + "*");
    ui->lineEdit->setText(string_all);
}

void MainWindow::on_pushButton_divide()
{
    QPushButton *button = (QPushButton *)sender();
    QString string_all;
    string_all = (ui->lineEdit->text() + "/");
    ui->lineEdit->setText(string_all);
}

void MainWindow::pi_num(){
    QPushButton *button = (QPushButton *)sender();
    QString string_all;
    string_all = (ui->lineEdit->text() + "pi");
    ui->lineEdit->setText(string_all);
}

void MainWindow::exp_num(){
    QPushButton *button = (QPushButton *)sender();
    QString string_all;
    string_all = (ui->lineEdit->text() + "2,7182818");
    ui->lineEdit->setText(string_all);
}

void MainWindow::binary_operators()
{
    QPushButton *button = (QPushButton *)sender();
    QString string_all;
    if (button->text() == '+' || button->text() == '-' || button->text() == '*' || button->text() == '/' || button->text() == '^') {
        string_all = (ui->lineEdit->text() + button->text());
        ui->lineEdit->setText(string_all);
    } else if (button->text() == "+/-") {
        QChar unary = '-';
        string_all = (ui->lineEdit->text() + unary);
        ui->lineEdit->setText(string_all);
    }
}

void MainWindow::operators()
{
    QPushButton *button = (QPushButton *)sender();
    QString string_all;
    string_all = (ui->lineEdit->text() + button->text());
    ui->lineEdit->setText(string_all);
}

void MainWindow::functions()
{
    QPushButton *button = (QPushButton *)sender();
    QString string_all;
    string_all = (ui->lineEdit->text() + button->text());
    ui->lineEdit->setText(string_all);
}

void MainWindow::on_pushButton_clear() {
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_graph(){
    QString qstr = ui->lineEdit->text();
    // Если строка пустая, выходим из функции
    if (qstr.isEmpty()) {
        return;
    }

    char str[256];
    QByteArray bytes = qstr.toLocal8Bit();
    strcpy(str, bytes.data());
    if(!validator(str)){
        // получаем максимальные и минимальные значения осей
        double x_min = ui->doubleSpinBox_x_min->value();
        double x_max = ui->doubleSpinBox_x_max->value();
        double y_min = ui->doubleSpinBox_y_min->value();
        double y_max = ui->doubleSpinBox_y_max->value();
        // шаг
        double h = 0.1;
        QVector<double> x, y;  // Массивы координат точек

        // собираем все точки
        for (double X = x_min; X <= x_max; X += h) {
            x.push_back(X);
            double y_val = calculate_string(str, X);
            y.push_back(y_val);
        }

        // добавляем один график в widget
        ui->graph_frame->addGraph();

        // говорим, что отрисовать нужно график по нашим двум массивам x и y
        ui->graph_frame->graph(0)->setData(x, y);

        // устанавливаем область, которая будет показываться на графике
        ui->graph_frame->xAxis->setRange(x_min, x_max);
        ui->graph_frame->yAxis->setRange(y_min, y_max);

        // задаем возможность зумировать график
        ui->graph_frame->setInteraction(QCP::iRangeZoom, true);

        // задаем цвет точки и толщину линии
        ui->graph_frame->graph(0)->setPen(QColor(61, 82, 62, 255));
        QPen graphPen = ui->graph_frame->graph(0)->pen();
        graphPen.setWidth(2);
        ui->graph_frame->graph(0)->setPen(graphPen);

        // перерисуем график на нашем graph_frame
        ui->graph_frame->replot();
    }
}


void MainWindow::on_go_to_credit()
{
    window = new CreditCalculator(this);
    window->show();
}


void MainWindow::get_result()
{
    QString qstr = ui->lineEdit->text();
    char str[length]="";
    char equal[2]="";
    equal[0] = '=';
    double x_num = 0;
    QByteArray bytes = qstr.toLocal8Bit();
    strcpy(str, bytes.data());
    strncat(str, equal, 1);

    if(validator(str) == 0){
        double res = 0;
        res = calculate_string(str, x_num);
        QString new_label = QString::number(res, 'f', 6);
        ui->lineEdit->setText(new_label);
    } else {
        ui->lineEdit->clear();
    }
}

