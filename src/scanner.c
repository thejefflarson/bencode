#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "scanner.h"

int
bencode_lex(YYSTYPE *yylval, YYLTYPE *llocp, const char *buf, long length){
  switch(buf[llocp->first_column]) {
    case 'i':
      llocp->last_column++;
      return INT;
    case 'l':
      llocp->last_column++;
      return LIST;
    case 'd':
      llocp->last_column++;
      return DICT;
    case 'e':
      llocp->last_column++;
      return END;
    default:
      if(buf[llocp->first_column] == '-' ||
          (buf[llocp->first_column] > '0' &&
           buf[llocp->first_column] <= '9')) {

        char *ep;
        long long num = strtoll(buf + llocp->first_column, &ep, 10);

        // no number
        if(errno == EINVAL)
          return 0;

        // bad range
        if(errno == ERANGE)
          return 0;

        // check overflow
        if((ep - &buf[llocp->first_column]) > length)
          return 0;

        llocp->last_column += ep - &buf[llocp->first_column];

        if(buf[llocp->last_column] == ':') {
          // check overflow
          if((num + llocp->last_column) > length)
            return 0;

          char *val = strndup(ep + 1, num);
          llocp->last_column += num + 1;

          if(val == NULL)
            return 0;


          (*yylval)->val.str = val;
          return STRING;
        } else if(buf[llocp->last_column] == 'e') {
          (*yylval)->val.i = num;
          return NUMBER;
        }

        return 0;
      }
  }
  return 0;
}
