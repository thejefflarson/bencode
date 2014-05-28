#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "bencode.h"

extern int bencode_parse(be_node_t *node, const char *buf, size_t length);

// Make this a proper scanner that feeds into bison
be_node_t *
be_decode(){
  be_node_t *node = calloc(1, sizeof(be_node_t));
  if(node == NULL) return node;
  bencode_parse("", 1);
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