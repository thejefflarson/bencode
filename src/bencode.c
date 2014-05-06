#include <stdlib.h>
#include "bencode.h"



be_node *
be_decode(const char *str, unsigned int size){

  while(st.parsed < st.size) {
    switch(st->curr[0]) {
      case 'i':
        break;
      case 'l':
        break;
      case 'd':
        break;
      case 'e':
        break;
      default:
        err = string(node, st);
    }
  }
  return root;
}

char *
be_encode(be_node *node){

}

void
be_free(be_node *node) {

}