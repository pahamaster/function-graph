#ifndef SRC_POLISH_H_
#define SRC_POLISH_H_

#include <stdio.h>
#include "dynamic.h"
#include "parsing.h"

int get_polish(Queue **dest, Queue **src);
int polish(Queue **dest, char *str);
void after_operator(Queue **dest, Stack **stack, int index);
int after_right_bracket(Queue **dest, Stack **stack);
int finish_read_stack(Queue **dest, Stack **stack);
void after_num(Queue **dest, Stack **stack);

#endif  // SRC_POLISH_H_
