%{
  #include <stdio.h>
  #include <errno.h>
  #include "bencode.h"
  #include "parser.tab.h"
%}

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

{NUMBER} { return NUMBER; }

{STRING} {
  char *end_ptr;
  long long num = strtoll(yytext, &end_ptr, 10);
  // set error or return from function
  // if(errno == EINVAL || errno == ERANGE) yyerror();

  for(long long i = 0; i < num; i++) input(yyscanner);

  return STRING;
}

{INT}  { return INT;  }
{DICT} { return DICT; }
{END}  { return END;  }
{LIST} { return LIST; }
. { } // silence warnings because we're doing something weird in number and string

%%
