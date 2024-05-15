
#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "calculate.h"
#include <math.h>

int report_mode = 0;
int valgrind_mode = 0;

#define S21_EXP 1e-7

START_TEST(normal_test) {
  struct my_struct {
    char *str;
    double expected;
    double x;
  };

  struct my_struct const test[] = {
    {"(x + 3) mod asin(3.1*x)", fmod(3.14 + 3, asin(3.1*3.14)), 3.14},
    {"(x + 3) mod -acos(3.1*x)", fmod(3.14 + 3, -acos(3.1*3.14)), 3.14},
    {"-1 / (3-1-2)", -1 / (3.0-1-2), 0},
    {"ln(-2*4)", log(-2.0*4), 0},
    {"sqrt(-2)", sqrt(-2.0), 0},

    {"sin(5)", -0.958924274663, 0},
    {"-sin(cos(2*3.14))^5+(-x+7)*2", 9.5781202754132465, 2},
    {"((2+4)/-x + 5*(6-7)) / x", 1, -2},
    {"15/(x-(1+1))*3 - (2+(1+1))*15/(x-(200+1))*-3- sqrt(2+(1+1)) * (15/(x-(1+1))*3)",
      -9.9278350515463918, 7},
    {"15/(x-(1+1))*3 - (2+(1+1))*15/(x-(200+1))*-3- sqrt(2+(1+1)) * (15/(x-(1+1))*3)",
      15.0/(7.0-(1.0+1.0))*3.0 - (2.0+(1.0+1.0))*15.0/(7.0-(200.0+1.0))*-3.0- sqrt(2.0+(1.0+1.0)) * (15.0/(7.0-(1.0+1.0))*3.0), 7},
    {"15/(x-(1+1))*+3 - -(2+(1+1))*15/(x-(200+1))*-3- sqrt(2+(2+-1)) * -(15/(x-(1+1))*3)",
      15.0/(7.0-(1.0+1.0))*+3.0 - -(2.0+(1.0+1.0))*15.0/(7.0-(200.0+1.0))*-3.0- sqrt(2.0+(2.0+-1.0)) * -(15.0/(7.0-(1.0+1.0))*3.0), 7},
    {"(sqrt(x+4)/x + 5*(6-7)) / -x", (sqrt(3 + 4) / 3 + 5 * (6 - 7)) / -3, 3},
    {"(sqrt(x+4)/x + ln(5*(-6+8))) / -x", -1.7636649821928174, 2},
    {"-sin(tan(2*x))+(-2+7)*2", 10.003185312566, 3.14},
    {"(2+3)*1-(4-1)", 2, 3.14},
    {"(x-5)^x", pow(2 - 5, 2), 2},
    {"(-x-5)^x", pow(-2 - 5, 2), 2},
    {"(5-x)^x", pow(5-3, 3), 3},
    {"(x+5)^x", pow((2.3 + 5), 2.3), 2.3},
    {"(-x+5)^x", pow((-2.3 + 5), 2.3), 2.3},
    {"x-5", 2 - 5, 2},
    {"10*x/(1+x)^3", 5 / (pow(1.5, 3)), .5},
    {"-x-5", -8, 3},
    {"1-x-5", -7, 3},
    {"1-x+-5", -7, 3},
    {"-(5+-x)^2", (5 - 2) * (5 - 2), 2},
    {"+(5-x)^2", (5 - 2) * (5 - 2), 2},
    {"(5+6)^2 + 3*4^2 + 2^-3*4", 169.5, 0},
    {"sin(tan(2*x))-(-2+7)*2", sin(tan(2*3.14))-(-2+7)*2, 3.14},
    {"-1.1+sin(3*-.5)+3", 0.902505013396, 0},
    {"(2+3)-(4-1)", 2, 3.14},
    {"(2+3)+(4-1)", 8, 3.14},
    {"-(2+3)-(4-1)", -(2+3)-(4-1), 3.14},
    {"+(2+3)+(4-1)", +(2+3)+(4-1), 3.14},
    {"+(-2+3)+(+4-1)", +(-2+3)+(+4-1), 3.14},
    {"+(-2+-3)-(-4-1)", +(-2+-3)-(-4-1), 3.14},
    {"+5", 5, 3.14},
    {"-4", -4, 3.14},
    {"x mod 4", fmod(3.14, 4), 3.14},
    {"sin(tan(2*x))-(-x mod 7)*2", sin(tan(2*3.14))-(fmod(-3.14, 7))*2, 3.14},
    {"(x + 3) mod 4", fmod(3.14 + 3, 4), 3.14},
    {"(x + 3) mod (3.1*x)", fmod(3.14+3, 3.1*3.14), 3.14},
    {"(x + 3) mod sin(3.1*x)", fmod(3.14 + 3, sin(3.1*3.14)), 3.14},
    {"(x + 3) mod -sin(3.1*x)", fmod(3.14 + 3, -sin(3.1*3.14)), 3.14},
    {"-(x + 3) mod +sin(3.1*x)", fmod(-3.14 - 3, sin(3.1*3.14)), 3.14},
    {"-(x + 3) mod +atan(3.1*x)", fmod(-3.14 - 3, atan(3.1*3.14)), 3.14},
    {"+log(5-2*-4)++asin(.2)", +log10(5-2*-4)+asin(.2), 0},
    {"+log(-(5-2)*-4)-acos(.2)", +log10(-(5-2)*-4)-acos(.2), 0},
    {"(5-2*-4)", 5-2 * -4, 0},
    {"(5*+4)", 5 * 4, 0},
    {"sin (-x)", sin(-1), 1},

    {"2-+2", 2 - 2, 0},
    {"2+-2", 2 - 2, 0},
    {"+2+-2", 2 - 2, 0},
    {"-2+-2", -2 - 2, 0},
    {"-2+2", -2 + 2, 0},
    {"-2-2", -2 - 2, 0},
    {"-2--(2+3)", -2+(2+3), 0},
    {"-2++(2+3)", -2+(2+3), 0},
    {"-2+-(2+3)", -2-(2+3), 0},
    {"-2-+(2+3)", -2-(2+3), 0},
    {"-(2-3)-+(2+3)", -(2-3)-(2+3), 0},
    {"-(2-3)+-(2+3)", -(2-3)-(2+3), 0},
    {"-(2-3)++(2+3)", -(2-3)+(2+3), 0},
    {"-(2-3)--(2+3)", -(2-3)+(2+3), 0},
    {"+(+5-3)--3", +(+5-3)+3, 3.14},
    {"2--sin (-x)", 2+sin(-1), 1},
    {"x+(2+3)+-sin (-x)*4", -1+(2+3)-sin(1)*4, -1},
    // {"sin x", sin(1), 1},
    {"x--5", 6, 1},
    {"x+-5", -4, 1},

    {NULL},
  };
  Queue *q_polish = NULL;
  int i;
  for (i = 0; test[i].str; i++) {
    if (report_mode)
      printf("%s \n", test[i].str);
    int e = polish(&q_polish, test[i].str);
    if (!e) {
      double a = 0;
      e = calculate(&a, &q_polish, test[i].x);

      if (!e) {

        if (isnan(test[i].expected)) {
          ck_assert_double_nan(a);
        } else if (isinf(test[i].expected)) {
          ck_assert_double_infinite(a);
        } else {
          ck_assert_double_eq_tol(a, test[i].expected, S21_EXP);
        }
      }
    }
    if (e) printf("Error %d\n", e);
    ck_assert_int_eq(e, 0);
    clear_queue(&q_polish);
  }
  printf("Count of tests %d\n", i);
}
END_TEST

// START_TEST(error_test) {
//   struct my_struct {
//     char *str;
//     double expected;
//     double x;
//   };

//   struct my_struct const test[] = {
//     // {"(x + 3) mod asin(3.1*x)", fmod(3.14 + 3, asin(3.1*3.14)), 3.14},
//     // {"(x + 3) mod -acos(3.1*x)", fmod(3.14 + 3, -acos(3.1*3.14)), 3.14},
//     // {"-1 / (3-1-2)", -1 / (3.0-1-2), 0},
//     // {"ln(-2*4)", log(-2.0*4), 0},
//     // {"sqrt(-2)", sqrt(-2.0), 0},


//     {"(x + 3) -mod 4", fmod(3.14 + 3, 4), 3.14},
//     {"--4", -4, 3.14},
//     {"2-+-2", 169.5, 0},
//     {"2---2", 169.5, 0},
//     {"++", +(-2+-3)-(-4-1), 3.14},
//     {"+", +(-2+-3)-(-4-1), 3.14},
//     {"-", +(-2+-3)-(-4-1), 3.14},
//     {"--", +(-2+-3)-(-4-1), 3.14},
//     {"+++5", 5, 3.14},
//     {"(5*--4)", 5-2 * -4, 0},
//     {"(5*-+4)", 5-2 * -4, 0},
//     {"(5*+-4)", 5-2 * -4, 0},
//     {"(5**4)", 5-2 * -4, 0},
//     {"(5*---4)", 5-2 * -4, 0},
//     {"sin -(x)", 5-2 * -4, 0},
//     {"(+++5)", sin(-1), 1},
//     {"six(x)", sin(-1), 1},
//     {"sin(x5)", sin(-1), 1},
//     {"-2++(++2+3)", -2+(+2+3), 0},
//     {"-2++(--2+3)", -2+(+2+3), 0},
//     {"--2+3", -2+(+2+3), 0},
//     {"(--2+3)", -2+(+2+3), 0},
//     {"(++5)", 5, 1},
//     {"++5", 5, 3.14},
//     {"+(+5-3)---3", 5, 3.14},
//     {"(5+5)+", 5, 3.14},
//     {"(5**5)", 5, 3.14},
//     {"5**5", 5, 3.14},
//     {"(5+5", 5, 3.14},
//     {"2+4)", 5, 3.14},
//     {"(x + 3) mod --sin(3.1*x)", 0, 3.14},

//     {NULL},
//   };
//   Queue *q_polish = NULL;
//   printf("Expected  Received  Solution String\n");
//   int i;
//   for (i = 0; test[i].str; i++) {
//     int e = polish(&q_polish, test[i].str);
//     if (!e) {
//       double a = 0;
//       e = calculate(&a, &q_polish, test[i].x);
//     }
//     if (report_mode)
//       printf("%s error %d\n", test[i].str, e);
//     ck_assert_int_eq(!e, 0);
//     clear_queue(&q_polish);
//   }
//   printf("Count of tests %d\n", i);
// }
// END_TEST

START_TEST(error_test) {

  char* test[] = {
    "(x + 3) -mod 4",
    "--4",
    "2-+-2",
    "2---2",
    "++",
    "+",
    "-",
    "--",
    "+++5",
    "(5*--4)",
    "(5*-+4)",
    "(5*+-4)",
    "(5**4)",
    "(5*---4)",
    "sin -(x)",
    "(+++5)",
    "six(x)",
    "sin(x5)",
    "-2++(++2+3)",
    "-2++(--2+3)",
    "--2+3",
    "(--2+3)",
    "(++5)",
    "++5",
    "+(+5-3)---3",
    "(5+5)+",
    "(5**5)",
    "5**5",
    "(5+5",
    "2+4)",
    "(x + 3) mod --sin(3.1*x)",
    "sin x",
    "sin -x",
    "sin 1",
    "sin -1",
    "1 sin",
    "1 sin ()",
    "2+2()",
    "(2+2)+()",
    "2 2 mod *3",
    "2 2 + *3",
    NULL,
  };
  Queue *q_polish = NULL;
  printf("Expected  Received  Solution String\n");
  int i;
  for (i = 0; test[i]; i++) {
    int e = polish(&q_polish, test[i]);
    if (!e) {
      double a = 0;
      e = calculate(&a, &q_polish, 0);
    }
    if (report_mode)
      printf("%s error %d\n", test[i], e);
    ck_assert_int_eq(!e, 0);
    clear_queue(&q_polish);
  }
  printf("Count of tests %d\n", i);
}
END_TEST

Suite *test_suite_normal() {
  Suite *s = suite_create("test_suite_normal_test");
  TCase *tc = tcase_create("test_case_normal_test");
  tcase_add_test(tc, normal_test);
  suite_add_tcase(s, tc);
  return s;
}

Suite *test_suite_error() {
  Suite *s = suite_create("test_suite_error_test");
  TCase *tc = tcase_create("test_case_error_test");
  tcase_add_test(tc, error_test);
  suite_add_tcase(s, tc);
  return s;
}

int main(int argc, char **argv) {
  int no_failed = 0;
  if (argc > 1) {
    report_mode = argv[1][0] == '+';
    valgrind_mode = argv[1][0] == 'v';
  }
  Suite *test_suites[] = {test_suite_normal(),             // ok
                         test_suite_error(),             // ok

                          NULL};

  for (Suite **suite = test_suites; *suite != NULL; suite++) {
    SRunner *runner = srunner_create(*suite);
    if (valgrind_mode) srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return no_failed;
}
