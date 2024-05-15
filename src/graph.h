#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#define HEIGHT 25
#define WIDTH 80
#define WIDTH_RAD 4 * M_PI
#define HEIGHT_RAD 2

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calculate.h"

int print_graph(char *str);
int fill_matr(int **matr, Queue **polish_q);
int func(double *dest, double x, Queue **polish_q);
void matrix_init(int ***matr);
void print_screen(int **matr);

#endif  // SRC_GRAPH_H_
