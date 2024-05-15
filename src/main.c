#include <stdio.h>
#include "graph.h"
#include <string.h>

int main() {
  char str[40];
  printf("Enter a mathematical expression: ");
  fgets(str, 39, stdin);
  print_graph(str);
  return 0;
}
