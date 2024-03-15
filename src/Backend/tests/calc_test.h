#ifndef SRC_CALC_TEST_H_
#define SRC_CALC_TEST_H_

#include <check.h>
#include <stdbool.h>
#include <stdio.h>

#include "../calculator.h"

Suite *suite_calc(void);

void run_test(void);
void run_testcase(Suite *testcase);


#endif  //  SRC_CALC_TEST_H_