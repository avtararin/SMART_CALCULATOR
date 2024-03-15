#include "calculator.h"

// Annuity

double monthly_annuity_payment(double amount, double percent, int term) {
  double monthly_rate = percent / 1200;  // Процентная ставка в месяц
  double pow = 1.0;
  for (int i = 0; i < term * 12; i++) {
    pow *= (1 + monthly_rate);
  }
  double payment =
      amount * monthly_rate * pow / (pow - 1);  // Формула аннуитетного платежа
  double value = (int)(payment * 100 + .5);
  return (double)value / 100;
}

double overpayment_on_loan(double amount, double percent, int term) {
  double payment = monthly_annuity_payment(amount, percent, term);
  double total_payment = payment * term * 12;
  double overpayment = total_payment - amount;
  double value = (int)(overpayment * 100 + .5);
  return (double)value / 100;
}

double total_loan_payment(double amount, double percent, int term) {
  double znach = monthly_annuity_payment(amount, percent, term) * term * 12;
  double value = (int)(znach * 100 + .5);
  return (double)value / 100;
}

//

void monthly_differential_payment(double amount, double percent, int term,
                                  double* payments) {
  double monthly_rate = percent / 1200;  // Процентная ставка в месяц
  double total_payment = 0;

  for (int i = 1; i <= term * 12; i++) {
    double payment =
        amount / (term * 12) +
        amount * monthly_rate *
            (1 -
             (i - 1) / (term * 12.0));  // Формула дифференцированного платежа
    total_payment += payment;
    if (i == 1){
      payments[0] = (double)((int)(payment * 100 + .5)/ 100);
    }
    else if (i == term * 12)
      payments[1] = (double)((int)(payment * 100 + .5)/ 100);
  }
}

double differential_payment(double amount, double percent, int term) {
  double monthly_rate = percent / 1200;  // Процентная ставка в месяц
  double total_payment = 0;

  for (int i = 1; i <= term * 12; i++) {
    double payment =
        amount / (term * 12) +
        amount * monthly_rate *
            (1 -
             (i - 1) / (term * 12.0));  // Формула дифференцированного платежа
    total_payment += payment;
  }

  double value = (int)(total_payment* 100 + .5);
  return (double)value / 100;
}

double differential_overpayment(double amount, double percent, int term) {
  double znach = differential_payment(amount, percent, term) - amount;
  double value = (int)(znach * 100 + .5);
  return (double)value / 100;
}