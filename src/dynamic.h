#ifndef SRC_DYNAMIC_H_
#define SRC_DYNAMIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void push_stack_index(Stack **stack, char index);
void push_stack(Stack **stack, Stack record);
char pop_stack_index(Stack **stack);
char get_stack_index(Stack **stack);
int pop_stack_num(Stack **stack, double *num);
Stack pop_stack(Stack **stack);
void clear_stack(Stack **stack);

void push_queue(Queue **queue, struct data_queue data);
void push_q(Queue **queue, char type, char index, double num);
void push_q_oper(Queue **queue, char index);
struct data_queue pop_queue(Queue **queue);
void clear_queue(Queue **queue);
struct data_queue get_queue_by_index(Queue **queue, unsigned int index);
unsigned int get_queue_count(Queue **queue);

#endif  // SRC_DYNAMIC_H_
