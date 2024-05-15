#ifndef SRC_PARSING_H_
#define SRC_PARSING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "data.h"
#include "dynamic.h"

// #include <ctype.h>

int parsing(Queue **queue, char *input);
int find_next(char *str, unsigned int *pos, int *index, double *num);
int find_num(char *str, unsigned int *pos, double *num);
int find_token(char *str, unsigned int *pos, int *index);
int find_oper(char *str, unsigned int *pos, int *index);
char* delete_spaces(char *str);

#endif  // SRC_PARSING_H_
