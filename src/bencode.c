#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "bencode.h"



// Make this a proper scanner that feeds into bison
be_node_t *
be_decode(const char *str, uint64_t size){
  uint64_t parsed = 0;
  while(parsed < size) {
    switch(str[parsed]) {
      case 'i':
        return BE_INT;
        break;
      case 'l':
        return BE_LIST;
        parsed++;
        break;
      case 'd':
        return BE_DICT;
        parsed++;
        break;
      case 'e':
        return BE_END;
        break;
      default:
        if(str[parsed] == '-' || (str[parsed] > '0' && str[parsed] <= '9')) {

          return BE_STR;
        }
        break;
    }
  }
  return node;
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