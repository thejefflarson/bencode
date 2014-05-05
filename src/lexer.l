%{
  #include <stdio.h>
  #include <error.h>
  #include "dht_encoding.h"
%}

%option outfile="lexer.c" header-file="lexer.h"
%option warn
%option reentrant nodefault
%option bison-bridge

INT   "i"
LIST  "l"
DICT  "d"
END   "e"

STRING -?[1-9][0-9]*:
NUMBER -?[1-9][0-9]*

%%

{NUMBER} {
  long long num = strtoll(yytext, yytext + 256, 10);
  if(perror(errno == EINVAL || ERANGE)) yyerror();
  yylval->int = num;
  return NUMBER;
}

{STRING} {
  long long num = strtoll(yytext, yytext + 256, 10);
  // set error or return from function
  if(errno == EINVAL || ERANGE) yyerror();
  strndup(yylval->str, num, yytext);
  yyless(yyleng - num);
  return STRING;
}

{INT}  { return INT;  }
{DICT} { return DICT; }
{END}  { return END;  }
{LIST} { return LIST; }
. { } // silence warnings because we're doing something weird in number and string
%%

int main(){

}