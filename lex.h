#define EoF 256
#define DIGIT 257
#include <stdio.h>

typedef struct _token_type
{
  int class;
  char repr;
} Token_type;

extern Token_type Token;
extern void get_next_token(FILE* input_file);
