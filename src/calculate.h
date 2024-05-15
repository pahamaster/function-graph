#ifndef SRC_CALCULATE_H_
#define SRC_CALCULATE_H_

#include <stdio.h>
#include <math.h>
// #include "dynamic.h"
#include "polish.h"
#include "parsing.h"


int calculate(double *dest, Queue **src, double x);
int function(Stack **stack, int index);
int s21_operator(Stack **stack, int index);
int finish(Stack **stack, double *dest);
int un_minus(Stack **stack);

#endif  // SRC_CALCULATE_H_
