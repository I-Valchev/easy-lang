#include "lex.h"
#include <stdio.h>

static int Is_layout_char(int ch){
  switch(ch){
    case ' ': case '\t': case '\n': return 1;
    default: return 0;
  }
}

Token_type Token;

void get_next_token(FILE* fp){
  char ch;
  do{
    ch = fgetc(fp);

    /*if(ch == EOF){
      Token.class = EoF; Token.repr = '#';
      fclose(fp);
      return;
    }*/
  }while(Is_layout_char(ch) && ch != EOF);

  if('0' <= ch && ch <= '9') {Token.class = DIGIT;}
  else {Token.class = ch;}
  Token.repr = ch;
}
