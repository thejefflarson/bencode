{%

%}

%token INT
%token STRING
%token LIST
%token DICT
%token NUMBER

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