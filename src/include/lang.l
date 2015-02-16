Q ^("Time Quantum ")[0-9]+:(" ")[0-9]+
A [a-z]
%%

{Q} return (1);
{A} return (2);
%%

void yyerror()
{
  printf("error\n");
  exit(0);
}

int yywrap() {}
