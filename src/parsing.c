#include "parsing.h"

int parsing(Queue **queue, char *input) {
  int res = 0;
  unsigned int pos = 0;
  double num = 0;
  int index = -1;
  // char *str = delete_spaces(input);

  // printf("%s %lu\n", str, strlen(str));
  // char *p = input;
  // for ( ; *p; ++p) *p = tolower(*p);
  while (pos < strlen(input) && !res) {
    while (input[pos] == ' ' || input[pos] == '\t' || 
      input[pos] == '\n' || input[pos] == '\r') pos++;
    // printf("{pos=%d}", pos);
    int type = find_next(input, &pos, &index, &num);
    if (type != -1)
      push_q(queue, type, index, num);
    else
      res = 1;

    // if (type == NUMBER) printf("%.0lf", num);
    // else printf("%s", operators[index].token);
    // printf("{pos=%d} ", pos);
  }

  // while (pos < strlen(str) && !res) {
  //   int type = find_next(str, &pos, &index, &num);
  //   if (type != -1)
  //     push_q(queue, type, index, num);
  //   else
  //     res = 1;

  //   // if (type == NUMBER) printf("%.0lf ", num);
  //   // else printf("%s ", operators[index].token);
  //   // printf("{pos=%d}", pos);
  // }
  // printf("{parsing}\n");
  // free(str);
  return res;
}

// char* delete_spaces(char *str) {
//   int u = 0;
//   char *res;
//   res = (char*) calloc(strlen(str) + 1, 1);
//   for (unsigned int i = 0; i < strlen(str); i++) {
//     if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
//       (res)[u] = (str)[i];
//       u++;
//     }
//   }
//   return res;
// }

int find_next(char *str, unsigned int *pos, int *index, double *num) {
  int res = -1;  // -1 Error, 0 End String, 1 Token, 2 Number

  if (str[*pos] == 0) {
    res = 0;
  } else {
    res = find_token(str, pos, index);
    if (res == 0) {
      res = find_oper(str, pos, index);
      if (res == -1) res = find_num(str, pos, num);
    }
  }
  return res;
}

int find_token(char *str, unsigned int *pos, int *index) {
  int res = 0;
  unsigned int pos_end = *pos;

  while (str[pos_end] >= 'a' && str[pos_end] <= 'z') pos_end++;
  if (pos_end > *pos) {
    res = -1;
    char *tmp;
    tmp = (char*)calloc(pos_end - *pos + 1, 1);
    for (unsigned int i = 0; i < pos_end - *pos; i++)
      tmp[i] = str[*pos + i];
    // printf("{tmp=%s}", tmp);
    if (!strcmp(tmp, operators[MOD].token)) {
      *index = MOD;
      res = OPERATOR;
    }
    for (int i = FUNC_BEGIN - 1; i < TOKEN_COUNT && res == -1; i++) {
      if (!strcmp(tmp, operators[i].token)) {
        *index = i;
        res = OPERATOR;
      }
    }
    *pos = pos_end;
    free(tmp);
  }
  return res;
}

int find_num(char *str, unsigned int *pos, double *num) {
  int res = -1;
  char *ptr_start = (char*)(str + *pos);
  char *ptr_end;
  // printf("%p %p %d\n", str, ptr_start, *pos);
  *num = strtod(ptr_start, &ptr_end);
  // printf("%p\n", ptr_end);

  if (ptr_start != ptr_end) {
    res = NUMBER;
    *pos = ptr_end - str;
  }
  // printf("%d\n", *pos);

  return res;
}

int find_oper(char *str, unsigned int *pos, int *index) {
  int res = -1;
  for (int i = 0; i < OPERATOR_END && res == -1; i++) {
    if (str[*pos] == operators[i].oper) {
      *index = i;
      res = OPERATOR;
      (*pos)++;
    }
  }
  return res;
}
