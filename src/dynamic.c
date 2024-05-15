#include "dynamic.h"

void push_queue(Queue **queue, struct data_queue data) {
  Queue *new_queue;
  new_queue = (Queue*) malloc(sizeof(Queue));
  new_queue->data = data;
  new_queue->next = *queue;
  *queue = new_queue;
}

void push_q(Queue **queue, char type, char index, double num) {
  Queue *new_queue;
  new_queue = (Queue*) malloc(sizeof(Queue));
  new_queue->data.num = num;
  new_queue->data.index = index;
  new_queue->data.type = type;
  new_queue->next = *queue;
  *queue = new_queue;
}

void push_q_oper(Queue **queue, char index) {
  Queue *new_queue;
  new_queue = (Queue*) malloc(sizeof(Queue));
  new_queue->data.index = index;
  new_queue->data.type = OPERATOR;
  new_queue->next = *queue;
  *queue = new_queue;
}

struct data_queue pop_queue(Queue **queue) {
  Queue *current = *queue;
  struct data_queue data;
  data.type = -1;
  if (*queue != NULL) {
    if (current->next == NULL) {
      data = current->data;
      free(current);
      *queue = NULL;
    } else {
      Queue *prev;
      while (current->next != NULL) {
        prev = current;
        current = current->next;
      }
      data = current->data;
      free(current);
      prev->next = NULL;
    }
  }
  return data;
}

struct data_queue get_queue_by_index(Queue **queue, unsigned int index) {
  struct data_queue data = {0, -1, 0};
  Queue *current = *queue;
  unsigned int i = 0;
  while (i++ < index && current != NULL) {
    current = current->next;
  }
  if (current != NULL) data = current->data;
  return data;
}

unsigned int get_queue_count(Queue **queue) {
  Queue *current = *queue;
  unsigned int count = 0;
  while (current != NULL) {
    current = current->next;
    count++;
  }
  return count;
}

void push_stack_index(Stack **stack, char index) {
  Stack *new_stack;
  new_stack = (Stack*) malloc(sizeof(Stack));
  new_stack->index = index;
  new_stack->next = *stack;
  *stack = new_stack;
}

void push_stack(Stack **stack, Stack record) {
  Stack *new_stack;
  new_stack = (Stack*) malloc(sizeof(Stack));
  // new_stack->index = index;
  *new_stack = record;
  new_stack->next = *stack;
  *stack = new_stack;
}

char pop_stack_index(Stack **stack) {
  Stack *current;
  char index = -1;
  if (*stack != NULL) {
    current = (*stack)->next;
    index = (**stack).index;
    free(*stack);
    *stack = current;
  }
  return index;
}

int pop_stack_num(Stack **stack, double *num) {
  int res = 0;
  Stack *current;
  if (*stack != NULL) {
    current = (*stack)->next;
    *num = (**stack).num;
    free(*stack);
    *stack = current;
  } else {
    res = 1;
  }
  return res;
}

Stack pop_stack(Stack **stack) {
  Stack record;
  record.index = -1;
  Stack *current;
  if (*stack != NULL) {
    current = (*stack)->next;
    record = **stack;
    free(*stack);
    *stack = current;
  }
  return record;
}

char get_stack_index(Stack **stack) {
  char index = -1;
  if (*stack != NULL)
    index = (**stack).index;
  return index;
}

void clear_stack(Stack **stack) {
  Stack *current = *stack;
  while (current != NULL) {
    Stack *temp = current;
    current = (*current).next;
    free(temp);
  }
  *stack = NULL;
  // printf("Stack cleared\n");
}

void clear_queue(Queue **queue) {
  Queue *current = *queue;
  while (current != NULL) {
    Queue *temp = current;

    // struct data_queue data = (*current).data;
    // if (data.type == NUMBER)
    //   printf("%.0lf ", data.num);
    // else if (data.type == OPERATOR)
    //   printf("%s ", operators[(int)data.index].token);

    current = (*current).next;
    free(temp);
  }
  *queue = NULL;
  // printf("\nQueue cleared\n");
}
