%{
#include "bencode.h"
#define YYSTYPE char const *
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
    case 'l':
      return LIST;
    case 'd':
      return DICT;
    case 'e':
      return END;
    default:
      if(str[parsed] == '-' || (str[parsed] > '0' && str[parsed] <= '9')) {
        char *ep;
        long long num = strtoll(str, ep, 10);

        if(errno == EINVAL)
          return ERROR;
        if(errno == ERANGE)
          return ERROR;


        if(ep[0] == ':') {
          if(num + parsed > length)
            return ERROR;

          char *val = strndup(ep + 1, num);

          if(val == NULL)
            return ERROR;

          yylval = val;
          return STRING;
        } else if(ep[0] == 'e') {
          yylval = num;
          return NUMBER;
        }

        return ERROR;
      }
  }
}
