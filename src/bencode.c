#include <stdlib.h>
#include "bencode.h"

be_node *
be_decode(char *str, long long size){
  // bison
}

char *
be_encode(be_node *node){

}

void
be_free(be_node *node) {
  free(node);
}