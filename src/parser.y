%{
#include "bencode.h"
%}

%union {
  int num;
  char *str;
  be_dict_t *dict;
  be_list_node_t *list;
}

%token DICT
%token LIST
%token END
%token STRING
%token INT
%token NUMBER

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
