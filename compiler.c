#include "parser.h"
#include "backend.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>

int Error(char* text){
  printf("%s", text);
  exit(1);
}

int main(int ARGC, char *ARGV[]){
  AST_node *icode;

  if(!Parse_program(&icode, ARGV[1]))
    Error("No top-level expression");

  Process(icode);

  return 0;
}
