%{
#include "bencode.h"

int bencode_lex(YYSTYPE *lvalp, YYLTYPE *llocp);
%}

%union {
  int num;
  char *str;
  be_dict_t *dict;
  be_list_node_t *list;
}

%define api.pure full
%option prefix="bencode"
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

int
bencode_lex(YYSTYPE *lvalp, YYLTYPE *llocp){
  switch(str[parsed]) {
    case 'i':
      return INT;
      break;
    case 'l':
      return LIST;
      parsed++;
      break;
    case 'd':
      return DICT;
      break;
    case 'e':
      return END;
      break;
    default:
      if(str[parsed] == '-' || (str[parsed] > '0' && str[parsed] <= '9')) {
        return STRING;
      }
      break;
  }
  return node;
}
