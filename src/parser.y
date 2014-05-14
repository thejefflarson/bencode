%{
  #include "scanner.h"

%}

%union {
  int num;
  char *str;
  be_dict *dict;
  be_list *list;
}

%token DICT
%token LIST
%token END
%token STRING
%token INT

%%

bencode:
  member
;

list:
  list_value
;

list_value:
  member
| list_value
;

dict:
  member
  dict_value
;

dict_value:
  member
| dict_value
;

member:
  number
| string
| dict
| list
;

%%
