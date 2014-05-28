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

%type <node.val> member;

%%

bencode:
  member { node = $1; }
;

list:
  LIST list_value END
;

list_value:
  member { $$ = $1; }
| member list_value { $$ = be_node_new(BE_DICT); }
;

dict:
  DICT dict_value END
;

dict_value:
  STRING member { $$ = $1; }
| STRING member dict_value { $$ = be_node_new(BE_DICT); }
;

integer:
  INT NUMBER END { $$ = $1; }
;

member:
  integer { $$ = be_node_new(BE_INT);  }
| STRING  { $$ = be_node_new(BE_STR);  }
| dict    { $$ = be_node_new(BE_DICT); }
| list    { $$ = be_node_new(BE_LIST); }
;

%%
void
bencode_error(YYLTYPE *llocp, const char *buf, long length, const char *msg){
  length = 0;
  printf("error parsing %s at character %i: %s", buf, llocp->first_column, msg);
}
