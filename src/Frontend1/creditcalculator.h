#ifndef CREDITCALCULATOR_H
#define CREDITCALCULATOR_H

#include <QDialog>

//подключение си
#ifdef __cplusplus
extern "C" {
#endif

#include "../Backend/calculator.h"

#ifdef __cplusplus
}
#endif

namespace Ui {
class CreditCalculator;
}

class CreditCalculator : public QDialog
{
    Q_OBJECT

public:
    explicit CreditCalculator(QWidget *parent = nullptr);
    ~CreditCalculator();

private slots:

    void on_calculate_clicked();

private:
    Ui::CreditCalculator *ui;
};

#endif // CREDITCALCULATOR_H
