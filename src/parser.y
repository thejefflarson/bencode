%{
#include <stdio.h>
#include "bencode.h"
#include "scanner.h"

void
bencode_error(YYLTYPE *llocp, const char *buf, long length, const char *msg);
%}

%code provides {
  #include "bencode.h"
  #define YYSTYPE be_node_t
}

/*
  Newer software is better than older, we are going with 3.0, even though
  2.3 is the default on OS X
*/
%require "3.0"
%define api.pure full
%locations
%defines

%name-prefix "bencode_"
%token DICT
%token LIST
%token END
%token STRING
%token INT
%token NUMBER

%parse-param {be_node_t **node} {const char *buf} {long length}
%lex-param   {const char *buf} {long length}

%%

bencode:
  member
;

list:
  LIST list_value END
;

list_value:
  member
| member list_value
;

dict:
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
| dict
| list
;

%%
void
bencode_error(YYLTYPE *llocp, const char *buf, long length, const char *msg){
  length = 0;
  printf("error parsing %s at character %i: %s", buf, llocp->first_column, msg);
}
