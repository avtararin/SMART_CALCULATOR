#include "calc_test.h"

    START_TEST(calc_0) {
        char str[100] = "1+1";
        ck_assert_double_eq(2, calculate_string(str, 0));
    }
    END_TEST

    START_TEST(calc_1) {
        char *str = malloc(sizeof(char) * strlen("1+2*3-4^2-64+(4-7)") + 1);
        strcpy(str, "1+2*3-4^2-64+(4-7)");
        ck_assert_double_eq(-76, calculate_string(str, 0));
        free(str);
    }
    END_TEST


    START_TEST(calc_2) {
        char *str = malloc(sizeof(char) * strlen("2+34-x*sin(pi/2)") + 1);
        strcpy(str, "2+34-x*sin(pi/2)");
        ck_assert_double_eq(34, calculate_string(str, 2));
        free(str);
    }
    END_TEST

    START_TEST(calc_3) {
        char *str = malloc(sizeof(char) * strlen("sin(pi)+cos(pi)+tan(pi)-asin(1/2)+acos(sqrt(3)/2)-atan(0)") + 1);
        strcpy(str, "sin(pi)+cos(pi)+tan(pi)-asin(1/2)+acos(sqrt(3)/2)+atan(0)");
        ck_assert_double_eq(-1, calculate_string(str, 0));
        free(str);
    }
    END_TEST


    START_TEST(calc_5) {
        char *str = malloc(sizeof(char) * strlen("10%2") + 1);
        strcpy(str, "10%2");
        ck_assert_double_eq(0, calculate_string(str, 0));
        free(str);
    }
END_TEST

START_TEST(calc_6) {
    char *str = malloc(sizeof(char) * strlen("log(100)") + 1);
    strcpy(str, "log(100)");
    ck_assert_double_eq(2, calculate_string(str, 0));
    free(str);
}
END_TEST

START_TEST(calc_7) {
    char *str = malloc(sizeof(char) * strlen("1+2*3-4^2-64+(4-7)") + 1);
    strcpy(str, "1+2*3-4^2-64+(4-7)");
    ck_assert_int_eq(0, validator(str));
    free(str);
}
END_TEST

START_TEST(calc_8) {
    char *str = malloc(sizeof(char) * strlen("sin(pi)+cos(pi)+tan(pi)-asin(1/2)+acos(sqrt(3)/2)-atan(0)") + 1);
    strcpy(str, "sin(pi)+cos(pi)+tan(pi)-asin(1/2)+acos(sqrt(3)/2)-atan(0)");
    ck_assert_int_eq(0, validator(str));
    free(str);
}
END_TEST

START_TEST(calc_9) {
    double znach = monthly_annuity_payment(300000, 15, 5);
    ck_assert_double_eq(7136.98, znach);
}
END_TEST

START_TEST(calc_10) {
    ck_assert_double_eq(128218.80, overpayment_on_loan(300000, 15, 5));
}
END_TEST

START_TEST(calc_11) {
    ck_assert_double_eq(428218.80  , total_loan_payment(300000, 15, 5));
}
END_TEST

START_TEST(calc_12) {
    ck_assert_double_eq(114375.00    , differential_overpayment(300000, 15, 5));
}
END_TEST

START_TEST(calc_13) {
    ck_assert_double_eq(414375.00   , differential_payment(300000, 15, 5));
}
END_TEST

START_TEST(calc_14) {
    double mas[2];
    monthly_differential_payment(300000, 15, 5, mas);
    ck_assert_double_eq(8750.00, mas[0]);
}
END_TEST

START_TEST(calc_15) {
    double mas[2];
    monthly_differential_payment(300000, 15, 5, mas);
    ck_assert_double_eq(5062, mas[1]);
}
END_TEST




Suite* suite_calc(void) {
    Suite* s = suite_create("suite_calc");
    TCase* tc = tcase_create("case_cacl");
    tcase_add_test(tc, calc_0);
    tcase_add_test(tc, calc_1);
    tcase_add_test(tc, calc_2);
    tcase_add_test(tc, calc_3);
    tcase_add_test(tc, calc_5);
    tcase_add_test(tc, calc_6);
    tcase_add_test(tc, calc_7);
    tcase_add_test(tc, calc_8);
    tcase_add_test(tc, calc_9);
    tcase_add_test(tc, calc_10);
    tcase_add_test(tc, calc_11);
    tcase_add_test(tc, calc_12);
    tcase_add_test(tc, calc_13);
    tcase_add_test(tc, calc_14);
    tcase_add_test(tc, calc_15);
    suite_add_tcase(s, tc); 
    return s;
}
