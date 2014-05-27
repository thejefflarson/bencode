%{
#include "bencode.h"
#include "lexer.h"
#define YYSTYPE be_node_t;
%}

/* for bison 2.3, which is default on os x, guh */
%pure-parser
%locations

%name-prefix="bencode_"
%token DICT
%token LIST
%token END
%token STRING
%token INT
%token NUMBER

%type <be_node_t *> member;

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
  integer { $$ = calloc(1, sizeof(be_node_t)); }
| STRING  { $$ = calloc(1, sizeof(be_node_t)); }
| dict    { $$ = calloc(1, sizeof(be_node_t)); }
| list    { $$ = calloc(1, sizeof(be_node_t)); }
;

%%

yytokentype
bencode_lex(YYSTYPE *yylval, YYLTYPE *llocp){
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

        str += ep - str;

        if(str[0] == ':') {
          if(num + parsed > length)
            return ERROR;

          char *val = strndup(ep + 1, num);

          if(val == NULL)
            return ERROR;

          yylval = val;
          return STRING;
        } else if(str[0] == 'e') {
          yylval = num;
          return NUMBER;
        }

        return ERROR;
      }
  }
}
