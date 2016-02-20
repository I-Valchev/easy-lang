  typedef int Operator;

  typedef struct _expression{
    char type;
    int value;
    struct _expression *left, *right;
    Operator oper;
  } Expression;

  typedef Expression AST_node;

  extern int Parse_program(AST_node **, char* source_file_name);
