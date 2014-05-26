#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "bencode.h"

// Make this a proper scanner that feeds into bison
be_node_t *
be_decode(){
  return yyparse();
}

char *
be_encode(be_node_t *node){
  (void) node;
  return "";
}

void
be_free(be_node_t *node) {
  if(node->type == BE_STR)
    free(node->val.str);
  free(node);
}