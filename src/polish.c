#include "polish.h"

int polish(Queue **dest, char *str) {
  int res = 0;

  Queue *parsing_q = NULL;
  clear_queue(dest);
  res = parsing(&parsing_q, str);

  if (!res) {
    res = get_polish(dest, &parsing_q);
    // if (res) printf("error polish\n");
  }  // else {
    // printf("error parsing\n");
  // }
  clear_queue(&parsing_q);
  return res;
}

int get_polish(Queue **dest, Queue **src) {
  struct data_queue oper = {0}, last_oper= {0};
  Stack *stack = NULL;
  int res = 0;

  oper = pop_queue(src);
  // if (oper.type == NUMBER)
  //   printf("%.0lf ", oper.num);
  // else if (oper.type == OPERATOR)
  //   printf("%s ", operators[(int)oper.index].token);

  // char last_is_num = 0;
  char is_unar = 1;
  int count_oper = 1;
  char last_is_func = 0;
  // char is_unar = 1;
  // char last_is_oper = 1;
  while (oper.type != -1 && !res) {
    if (oper.type == NUMBER) {
      push_queue(dest, oper);
      after_num(dest, &stack);
      count_oper = 0;
    }
    if (oper.type == OPERATOR) {
      int index = oper.index;
      // if (index >= OPERATOR_BEGIN && index < OPERATOR_END) {
      //   count_oper++;
      // } else {
      //   count_oper = 0;
      // }
      if (index == X) {
        push_queue(dest, oper);
        after_num(dest, &stack);
      }
      if ((index >= FUNC_BEGIN && index < X) || index == LEFT_BRACKET)
        push_stack_index(&stack, index);
      if (index == RIGHT_BRACKET) {
        res = after_right_bracket(dest, &stack);
      }
      if (index >= OPERATOR_BEGIN && index < OPERATOR_END && !res) {
        count_oper++;
        if (count_oper < 3) {
          if (index == MINUS && is_unar) index = UN_MINUS;
          if (!(index == PLUS && is_unar)) {
            after_operator(dest, &stack, index);
          }
          
        } else {
          res = 1;
        }
        // if (index == MINUS && is_unar) index = UN_MINUS;
        // if (!(index == PLUS && is_unar)) {
        //   after_operator(dest, &stack, index);
        // }
        // if ((index == UN_MINUS || index == PLUS) && is_unar) is_unar = 0;
        // else is_unar = 1;
      } else {
        count_oper = 0;
      }
    }  // OPERATOR
    // if (oper.index == LEFT_BRACKET) is_unar = 1;
    // if (oper.index == RIGHT_BRACKET) is_unar = 0;
    // if ((index == UN_MINUS || index == PLUS) && is_unar) is_unar = 0;
    //     else is_unar = 1;
    if (oper.type == OPERATOR && oper.index == LEFT_BRACKET) count_oper = 1;
    is_unar = !(oper.type == NUMBER || 
      (oper.type == OPERATOR && (oper.index >= FUNC_BEGIN && oper.index <= X)))
                && oper.index != RIGHT_BRACKET;
    // last_is_num = oper.type == NUMBER || (oper.type == OPERATOR && oper.index == X);
    // last_oper = oper;
    res = res ||  (last_is_func && ((oper.type == OPERATOR && oper.index != LEFT_BRACKET) || oper.type == NUMBER));
    last_is_func = oper.type == OPERATOR && oper.index >= FUNC_BEGIN && oper.index < X;
    last_oper = oper;
    oper = pop_queue(src);
    if (last_oper.type == OPERATOR && last_oper.index == LEFT_BRACKET &&
        oper.type == OPERATOR && oper.index == RIGHT_BRACKET) res = 1;
    if ((last_oper.type == NUMBER || (last_oper.type == OPERATOR && last_oper.index == X)) &&
         (oper.type == NUMBER || (oper.type == OPERATOR && oper.index == X)))
      res = 1;
    // if (oper.type == NUMBER)
    //   printf("%.0lf ", oper.num);
    // else if (oper.type == OPERATOR)
    //   printf("%s ", operators[(int)oper.index].token);
    
  }
  //  printf("{polish}\n");

  if (!res)
    res = finish_read_stack(dest, &stack);

  clear_stack(&stack);
  if (last_oper.type == OPERATOR && last_oper.index >= OPERATOR_BEGIN && last_oper.index < X)
    res = 1;
  return res ? 2 : 0;
}

int finish_read_stack(Queue **dest, Stack **stack) {
  int res = 0;
  int index_stack = pop_stack_index(stack);
  // printf("index_stack= %d\n", index_stack);
  while (index_stack != -1 && !res) {
    if (index_stack == LEFT_BRACKET)
      res = 1;
    else
      push_q_oper(dest, index_stack);
    index_stack = pop_stack_index(stack);
  }
  // printf("finish r s %d\n", res);
  return res;
}

void after_num(Queue **dest, Stack **stack) {
  int index_stack = get_stack_index(stack);
  if (index_stack == UN_MINUS) {
    pop_stack_index(stack);
    push_q_oper(dest, UN_MINUS);
  }
}

void after_operator(Queue **dest, Stack **stack, int cur_index) {
  int index_stack = get_stack_index(stack);
  // printf("c_i= %d, i_s= %d, ", cur_index, index_stack);

  while (index_stack >= OPERATOR_BEGIN && index_stack <= OPERATOR_END &&
  operators[index_stack].priority >= operators[cur_index].priority) {
    pop_stack_index(stack);
    push_q_oper(dest, index_stack);
    index_stack = get_stack_index(stack);
    // printf("i_s= %d, ", index_stack);
  }

  push_stack_index(stack, cur_index);
  // printf("\n");
}

int after_right_bracket(Queue **dest, Stack **stack) {
  int res = 0;
  int find_left_bracket = 0;

  int index_stack = pop_stack_index(stack);
  while (index_stack != -1 && !find_left_bracket) {
    if (index_stack == LEFT_BRACKET) {
      find_left_bracket = 1;
    } else {
      push_q_oper(dest, index_stack);
      index_stack = pop_stack_index(stack);
    }
  }

  if (!find_left_bracket) {
    res = 1;
  } else {
    index_stack = get_stack_index(stack);
    if (index_stack >= FUNC_BEGIN && index_stack < X) {
      pop_stack_index(stack);
      push_q_oper(dest, index_stack);
    }
  }
  // printf("after r b %d\n", res);
  return res;
}
