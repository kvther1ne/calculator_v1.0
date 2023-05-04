#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "calc.h"

START_TEST(calc_test_1) {
  double res = 0.0;
  char *str = "1+1";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(2, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_inf) {
  double res = 0.0;
  char *str = "1/0";
  SmartCalculator(str, &res, 0);
  ck_assert_double_infinite(res);
}
END_TEST

START_TEST(calc_test_sin) {
  double res = 0.0;
  char *str = "sin((5+3)*8-1)/1234";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(0.0001356205026765, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_cos) {
  double res = 0.0;
  char *str = "cos(((5+3)*8-1)/1234)^5";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(0.9935022240704376, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_tan) {
  double res = 0.0;
  char *str = "tan(((5+3)*8-1)/1234)";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(0.051097887156247204, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_asin) {
  double res = 0.0;
  char *str = "asin(((5+3)*8-1)/1234)";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(0.05107568878591054, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_asin_nan) {
  double res = 0.0;
  char *str = "asin(-5)";
  SmartCalculator(str, &res, 0);
  ck_assert_double_nan(res);
}
END_TEST

START_TEST(calc_test_acos) {
  double res = 0.0;
  char *str = "acos(1/2)";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(1.0471975511965979, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_acos_nan) {
  double res = 0.0;
  char *str = "acos(20)";
  SmartCalculator(str, &res, 0);
  ck_assert_double_nan(res);
}
END_TEST

START_TEST(calc_test_atan) {
  double res = 0.0;
  char *str = "8/atan(sin(24^5/2)*3)";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(28.695382595477856, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_ln) {
  double res = 0.0;
  char *str = "ln(8/atan(sin(24^5/2)*3))";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(3.3567362246471797, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_ln_inf) {
  double res = 0.0;
  char *str = "ln(0)";
  SmartCalculator(str, &res, 0);
  ck_assert_double_infinite(res);
}
END_TEST

START_TEST(calc_test_log) {
  double res = 0.0;
  char *str = "log(2/3^3/20+45^8*(2+3))";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(13.9246701145387682589283, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_log_inf) {
  double res = 0.0;
  char *str = "log(0)";
  SmartCalculator(str, &res, 0);
  ck_assert_double_infinite(res);
}
END_TEST

START_TEST(calc_test_pow) {
  double res = 0.0;
  char *str = "2^3^2";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(512, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_pow_neg) {
  double res = 0.0;
  char *str = "ln(2^(-3-4*3))";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(-10.397207708399179, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_sqrt) {
  double res = 0.0;
  char *str = "sqrt(3)";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(1.7320508075688772, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_sqrt_nan) {
  double res = 0.0;
  char *str = "sqrt(-3)";
  SmartCalculator(str, &res, 0);
  ck_assert_double_nan(res);
}
END_TEST

START_TEST(calc_test_mod) {
  double res = 0.0;
  char *str = "sqrt(3)mod(2/4*(1+2))";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(0.2320508075688772, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_mod_nan) {
  double res = 0.0;
  char *str = "(sqrt(log(2^5)))mod0";
  SmartCalculator(str, &res, 0);
  ck_assert_double_nan(res);
}
END_TEST

START_TEST(calc_test_mod_2) {
  double res = 0.0;
  char *str = "(10mod3)mod(2)";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(1, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_un_minus) {
  double res = 0.0;
  char *str = "-5-10*sqrt(-10*(-2))+11";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(-38.721359549995796, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_un_plus) {
  double res = 0.0;
  char *str = "-5-10*sqrt(+111-log(222)*(-2))+11";
  SmartCalculator(str, &res, 0);
  ck_assert_ldouble_eq_tol(-101.56054385735565, res, S21_EPS);
}
END_TEST

START_TEST(calc_test_x) {
  double res = 0.0;
  char *str = "sqrt(x)";
  SmartCalculator(str, &res, 5);
  ck_assert_ldouble_eq_tol(2.23606797749979, res, S21_EPS);
}
END_TEST

Suite *calc_suite_create(void) {
  Suite *suite = suite_create("SmartCalc");
  TCase *tcase_core = tcase_create("Core");
  tcase_add_test(tcase_core, calc_test_1);
  tcase_add_test(tcase_core, calc_test_inf);
  tcase_add_test(tcase_core, calc_test_sin);
  tcase_add_test(tcase_core, calc_test_cos);
  tcase_add_test(tcase_core, calc_test_tan);
  tcase_add_test(tcase_core, calc_test_asin);
  tcase_add_test(tcase_core, calc_test_asin_nan);
  tcase_add_test(tcase_core, calc_test_acos);
  tcase_add_test(tcase_core, calc_test_acos_nan);
  tcase_add_test(tcase_core, calc_test_atan);
  tcase_add_test(tcase_core, calc_test_ln);
  tcase_add_test(tcase_core, calc_test_ln_inf);
  tcase_add_test(tcase_core, calc_test_log);
  tcase_add_test(tcase_core, calc_test_log_inf);
  tcase_add_test(tcase_core, calc_test_pow);
  tcase_add_test(tcase_core, calc_test_pow_neg);
  tcase_add_test(tcase_core, calc_test_sqrt);
  tcase_add_test(tcase_core, calc_test_sqrt_nan);
  tcase_add_test(tcase_core, calc_test_mod);
  tcase_add_test(tcase_core, calc_test_mod_nan);
  tcase_add_test(tcase_core, calc_test_mod_2);
  tcase_add_test(tcase_core, calc_test_un_minus);
  tcase_add_test(tcase_core, calc_test_un_plus);
  tcase_add_test(tcase_core, calc_test_x);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  int number_failed;
  Suite *suite = calc_suite_create();
  SRunner *suite_runner = srunner_create(suite);
  srunner_set_fork_status(suite_runner, CK_NOFORK);
  srunner_run_all(suite_runner, CK_NORMAL);
  // получаем количество проваленных тестов
  number_failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
