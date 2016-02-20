#include <stdlib.h>
#include "lex.h"
#include "error.h"
#include "parser.h"
#include <stdio.h>

static Expression* new_expression(void){
  return (Expression *) malloc (sizeof(Expression));
}

static void free_expression(Expression *expr) {free((void*) expr);}
static int Parse_operator(Operator *oper_p);
static int Parse_expression(Expression **expr_p, FILE* source_file);


static int Parse_operator(Operator *oper){
    if(Token.class == '+'){
      *oper = '+'; return 1;
    }
    if(Token.class == '*'){
      *oper = '*'; return 1;
    }

    return 0;
}

static int Parse_expression(Expression **expr_p, FILE* source_file){
  Expression *expr = *expr_p = new_expression();

  if(Token.class == DIGIT){
    expr->type = 'D'; expr->value = Token.repr - '0';
  }else if(Token.class == '('){
    expr->type = 'P';
    get_next_token(source_file);

    if(!Parse_expression(&expr->left, source_file)){
      Error("Missing expression");
    }

    if(!Parse_operator(&expr->oper)){
      Error("Missing operator");
    }

    get_next_token(source_file);

    if(!Parse_expression(&expr->right, source_file)){
      Error("Missing expression");
    }

    if(Token.class != ')'){
      Error("Missing )");
    }
  }else{
    free_expression(expr);
    return 0;
  }

  get_next_token(source_file);
  return 1;
}

FILE* open_source_file(char* filename){
    FILE* file = fopen(filename, "r");
    return file;
}

int Parse_program(AST_node **icode_p, char* source_file_name){
  Expression *expr;

  FILE* source_file = open_source_file(source_file_name);

  get_next_token(source_file);
  if(Parse_expression(&expr, source_file)){
    if(Token.class == EoF){
      Error("Garbage after end of program");
    }
    *icode_p = expr;

    return 1;
  }

  fclose(source_file);

  return 0;
}
