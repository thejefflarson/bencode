%{
  #include "bencode.h"
  #include <stdio.h>
  extern int yylex();
  void yyerror(const char *s);
%}

%token INT
%token <char *> STRING
%token LIST
%token DICT
%token <long long> NUMBER
%token END

%union {
  long long num;
  char *string;
}

%%

list:
  LIST list_value END

list_value:
  member
| member list_value
;

dictionary:
  DICT dict_value END
;

dict_value:
  STRING member
| STRING member dict_value
;

integer:
  INT NUMBER END
;

member:
  integer
| STRING
| list
| dictionary
;

%%

 void
 yyerror(const char *s) {
   fprintf (stderr, "%s\n", s);
 }
