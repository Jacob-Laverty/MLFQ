Q ^("Time Quantum ")[0-9]+:(" ")[0-9]+
%%

{Q} return (1);
%%

void yyerror()
{
  printf("error\n");
  exit(0);
}

int yywrap() {}
