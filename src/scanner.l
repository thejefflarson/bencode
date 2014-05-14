%{
  #include "bencode.h"
%}

%option warn nodefault
%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

INT  "i"
END  "e"
DICT "d"
LIST "l"

NUMBER -?[1-9][0-9]*
STRING -?[1-9][0-9]*:

%%

{NUMBER} { return NUMBER; }
{STRING} { return STRING; }
{DICT}   { return DICT; }
{LIST}   { return LIST; }
{END}    { return END;  }

%%

int yyerror(const char *msg) {
  fprintf(stderr,"Error:%s\n",msg); return 0;
}