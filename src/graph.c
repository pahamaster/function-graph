#include "graph.h"

int print_graph(char *str) {
  int res = 0;
  int **matrix;
  matrix_init(&matrix);

  Queue *parsing_q = NULL;
  Queue *polish_q = NULL;
  res = parsing(&parsing_q, str);

  if (!res) {
    res = get_polish(&polish_q, &parsing_q);
    if (!res) {
      res = fill_matr(matrix, &polish_q);
       if (!res) print_screen(matrix);
    } else {
      printf("error polish\n");
    }
  }  else {
    printf("error parsing\n");
  }

  clear_queue(&parsing_q);
  clear_queue(&polish_q);
  free(matrix);
  return res;
}

int fill_matr(int **matr, Queue **polish_q) {
  int res = 0;
  double step_x = WIDTH_RAD / WIDTH;
  // double step_y = HEIGHT_RAD / HEIGHT;

  for (int x = 0; x < WIDTH && !res; x++) {
    double x_rad;
    double y_rad = 0;
    x_rad = x * step_x;
    // y_rad = func(x_rad, func) + 1;
    res = func(&y_rad, x_rad, polish_q);
    y_rad += 1;
    if (!res) {
      int y = round(y_rad * HEIGHT / HEIGHT_RAD);
      if (y >= 0 && y < HEIGHT) matr[y][x] = 1;
    }
    // printf("x=%.5lf y=%.5lf  x=%d y=%ld\n", x_rad, y_rad, x, y);
  }
  return res;
}

int func(double *dest, double x, Queue **polish_q) {
  int res = 0;
  res = calculate(dest, polish_q, x);
  if (res) printf("error calculate\n");
  return res;
}

// int func(double *dest, double x) {
//   *dest = sin(cos(2*x));
//   return 0;
// }

void matrix_init(int ***matr) {
  *matr = malloc(sizeof(int) * HEIGHT * WIDTH + HEIGHT * sizeof(int*));
  int *ptr = (int*)(*matr + HEIGHT);

  for (int i = 0; i < HEIGHT; i++)
    (*matr)[i] = (int*)(ptr + i * WIDTH);

  for (int i = 0; i < HEIGHT; i++)
    for (int j = 0; j < WIDTH; j++)
      (*matr)[i][j] = 0;
}

void print_screen(int **matr) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      printf(matr[i][j] == 0 ? "." : "*");
    }
    printf("\n");
  }
}
