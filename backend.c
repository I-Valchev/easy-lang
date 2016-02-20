#include "parser.h"
#include "backend.h"
#include <stdio.h>

static void Code_gen_expression(Expression *expr){
  switch(expr->type){
    case 'D':
      printf("PUSH %d\n", expr->value);
      break;
    case 'P':
      Code_gen_expression(expr->left);
      Code_gen_expression(expr->right);
      switch(expr->oper){
        case '+': printf("ADD\n"); break;
        case '*': printf("MULT\n"); break;
      }
      break;
  }
}

void Process(AST_node *icode){
  Code_gen_expression(icode); printf("PRINT\n");
}
