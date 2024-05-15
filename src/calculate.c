#include "calculate.h"

int calculate(double *dest, Queue **src, double x) {
  int res = 0;
  Stack *stack = NULL;
  struct data_queue oper;

  unsigned int count = get_queue_count(src);
  // printf("count= %d\n", count);
  Stack num1 = {0, 0, NULL};

  for (int i = count - 1; i >= 0 && !res; i--) {
    oper = get_queue_by_index(src, i);
    if (oper.type != -1) {
      // if (oper.type == NUMBER)
      //   printf("%.0lf ", oper.num);
      // else if (oper.type == OPERATOR)
      //   printf("%s ", operators[(int)oper.index].token);

      if (oper.type == OPERATOR) {
        if (oper.index == X) {
          num1.num = x;
          push_stack(&stack, num1);
        }
        if (oper.index == UN_MINUS) {
          res = un_minus(&stack);
        }
        if (oper.index >= OPERATOR_BEGIN && oper.index < UN_MINUS && !res) {
          res = s21_operator(&stack, oper.index);
        }
        if (oper.index >= FUNC_BEGIN && oper.index < X && !res) {
          res = function(&stack, oper.index);
        }
      } else {
        num1.num = oper.num;
        // num1.index = NUMBER;
        push_stack(&stack, num1);
      }
    } else {
      res = 1;
      printf("Error: out of index\n");
    }
  }

  // printf("\n");
  if (!res) res = finish(&stack, dest);

  // clear_queue(src);
  clear_stack(&stack);
  return res ? 3 : 0;
}

int finish(Stack **stack, double *dest) {
  int res = 0;
  double num = -5.2;
  if (!pop_stack_num(stack, dest)) {
    if (!pop_stack_num(stack, &num)) {
      res = 1;
    }
  } else {
    res = 1;
  }
  // printf("dest= %.1lf res=%d num= %.1lf\n", *dest, res, num);
  return res;
}

int un_minus(Stack **stack) {
  int res = 0;
  Stack num1 = pop_stack(stack);
  if (num1.index == -1) {
    res = 1;
  } else {
    num1.num = -num1.num;
    push_stack(stack, num1);
  }
  return res;
}

int s21_operator(Stack **stack, int index) {
  int res = 0;
  Stack num1;  // = {0, 0, NULL};
  Stack num2;  // = {0, 0, NULL};
  num1 = pop_stack(stack);
  num2 = pop_stack(stack);
  // printf("num1.index= %d num2.index= %d\n", num1.index, num2.index);
  if (num1.index != -1 && num2.index != -1) {
    double res_op = 0;
    switch (index) {
      case PLUS:
        res_op = num2.num + num1.num;
      break;
      case MINUS:
        res_op = num2.num - num1.num;
      break;
      case MULT:
        res_op = num2.num * num1.num;
      break;
      case DIV:
        res_op = num2.num / num1.num;
      break;
      case POWER:
        res_op = pow(num2.num, num1.num);
      break;
      case MOD:
        res_op = fmod(num2.num, num1.num);
      break;
    }
    num1.num = res_op;
    push_stack(stack, num1);
  } else {
    res = 1;
  }
  return res;
}

int function(Stack **stack, int index) {
  int res = 0;
  Stack num1 = pop_stack(stack);
  if (num1.index != -1) {
    double res_op = 0;
    switch (index) {
      case FUNC_BEGIN + SIN:
        res_op = sin(num1.num);
      break;
      case FUNC_BEGIN + COS:
        res_op = cos(num1.num);
      break;
      case FUNC_BEGIN + TAN:
        res_op = tan(num1.num);
      break;
      case FUNC_BEGIN + ASIN:
        res_op = asin(num1.num);
      break;
      case FUNC_BEGIN + ACOS:
        res_op = acos(num1.num);
      break;
      case FUNC_BEGIN + ATAN:
        res_op = atan(num1.num);
      break;
      case FUNC_BEGIN + SQRT:
        res_op = sqrt(num1.num);
      break;
      case FUNC_BEGIN + LN:
        res_op = log(num1.num);
      break;
      case FUNC_BEGIN + LOG:
        res_op = log10(num1.num);
      break;
    }
    num1.num = res_op;
    push_stack(stack, num1);
  } else {
    res = 1;
  }
  return res;
}
