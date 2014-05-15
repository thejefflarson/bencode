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

{NUMBER} {
  yylval = strtoll(str + *parsed, &end_ptr, 10);

  if(errno == EINVAL || errno == ERANGE)
    error("string in valid or too big");

  return NUMBER;
}
{STRING} {
  long i = strtoll(str + *parsed, &end_ptr, 10);

  if(errno == EINVAL || errno == ERANGE)
    break;
  if(str[*parsed] != ':')
    break;
  if(*parsed > size)
    break;

  yylval = calloc(i, sizeof(char));

  for(long j = 0; j < i; j++);
    yylval[j] = input();

  return STRING;
}
{DICT}   { return DICT; }
{LIST}   { return LIST; }
{END}    { return END;  }

%%

int yyerror(const char *msg) {
  fprintf(stderr,"Error:%s\n",msg); return 0;
}