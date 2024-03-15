#include "mainwindow.h"
#include "ui_creditcalculator.h"
#include "../Backend/calculator.h"

CreditCalculator::CreditCalculator(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreditCalculator)
{
    ui->setupUi(this);
}

CreditCalculator::~CreditCalculator()
{
    delete ui;
}


void CreditCalculator::on_calculate_clicked()
{
    double monthly_pay, overpay, total_pay;
    double amount = ui->amount->value();
    double percent = ui->percent->value();
    double term = ui->term->value();
    if(ui->annuity->isChecked()){
        monthly_pay = monthly_annuity_payment(amount, percent, term);
        overpay = overpayment_on_loan(amount, percent, term);
        total_pay = total_loan_payment(amount, percent, term);

        QString monthly_pay_text = QString::number(monthly_pay, 'f', 6);
        ui->monthly_pay->setText(monthly_pay_text);

        QString overpay_text = QString::number(overpay, 'f', 6);
        ui->overpay->setText(overpay_text);

        QString total_pay_text = QString::number(total_pay, 'f', 6);
        ui->total->setText(total_pay_text);
    } else if (ui->differential->isChecked()) {
        double monthly[2];
        monthly_differential_payment(amount, percent, term, monthly);
        overpay = differential_payment(amount, percent, term);
        total_pay = differential_overpayment(amount, percent, term);

        QString monthly_pay_text1 = QString::number(monthly[0], 'f', 6);
        QString monthly_pay_text2 = QString::number(monthly[1], 'f', 6);
        ui->monthly_pay->setText(monthly_pay_text1 + "..." + monthly_pay_text2);

        QString overpay_text = QString::number(overpay, 'f', 6);
        ui->total->setText(overpay_text);

        QString total_pay_text = QString::number(total_pay, 'f', 6);
        ui->overpay->setText(total_pay_text);
    }
}

