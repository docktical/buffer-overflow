#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int bof(char* str) {
  char buffer[353];
  strcpy(buffer, str);
  return 0;
}

int main() {
  char str[1000];
  FILE* badfile;
  badfile = fopen("./badfile", "r");
  
  fread(str, sizeof(char), 1000, badfile);
  bof(str);

  printf("Returned properly\n");
  return 0;
}