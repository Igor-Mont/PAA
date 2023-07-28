#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int tamstr (char * string) {
  char * p = string; 
  int i = 0;
  for (i; p[i] != '\0'; i++) {}
  return i;
}

int main() {
  char string[10];
  scanf("%s", string);
  while(strcmp(string, "FIM")) {
    printf("%d\n", tamstr(string));
    scanf("%s", string);
  }
  return 0;
}