#ifndef SRC_DATA_H_
#define SRC_DATA_H_

// type
#define OPERATOR 1
#define NUMBER 2

#define TOKEN_COUNT 19
#define OPERATOR_BEGIN 2
#define OPERATOR_END 8
#define FUNC_BEGIN 9
#define X TOKEN_COUNT - 1
#define LEFT_BRACKET 0
#define RIGHT_BRACKET 1
#define PLUS 2
#define MINUS 3
#define MULT 4
#define DIV 5
#define POWER 6
#define MOD 7
#define UN_MINUS 8

#define SIN 0
#define COS 1
#define TAN 2
#define ASIN 3
#define ACOS 4
#define ATAN 5
#define SQRT 6
#define LN 7
#define LOG 8

struct Operator {
  char *token;
  char oper;
  int priority;
};

struct data_queue {
  char index;
  double num;
  char type;
};

extern struct Operator const operators[TOKEN_COUNT];

typedef struct Stack {
  char index;
  double num;
  struct Stack *next;
} Stack;

typedef struct Queue {
  struct data_queue data;
  struct Queue *next;
} Queue;

#endif  // SRC_DATA_H_
