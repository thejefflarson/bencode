#ifndef SCANNER_H_
#define SCANNER_H_

#include "parser.tab.h"

int
bencode_lex(YYSTYPE *yylval, YYLTYPE *llocp, const char *buf, long length);

#endif