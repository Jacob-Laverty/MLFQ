QUANTUMSTART ^("Time Quantum ")[0-9]+:
PROCESSSTART ^("Process ID: ")
ARRIVALTIME  ^("Arrival time: ")
CPUBURST     ^("CPU burst: ")
IOBURST      ^("I/O burst: ")
IODEVICE     ^("I/O device id: ")
EOL [0-9]+$
%%

{QUANTUMSTART} return (1);
{PROCESSSTART} return (2);
{ARRIVALTIME}  return (3);
{CPUBURST}     return (4);
{IOBURST}      return (5);
{IODEVICE}     return (6);
{EOL}          return (7);

%%

void yyerror()
{
  printf("error\n");
  exit(0);
}

int yywrap() {}
