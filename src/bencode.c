#include <stdlib.h>
#include "bencode.h"

struct state {
  long long parsed;
  long long size;
  char *buf;
  char *curr;
};

static void
seek(struct state *st, int amount){
  st->curr   += amount;
  st->parsed += amount;
}

static int
integer(be_node *node, struct state *st){
  char *end_ptr;

  seek(st, 1); // swallow 'i'
  long long num = strtoll(st->curr, &end_ptr, 10);
  if(errno == EINVAL || errno == ERANGE)
    return 1;

  seek(st, end_ptr - st->curr);
  if(st->curr[0] != 'e')
    return 1;

  seek(st, 1); // swallow 'e'
  node->type = BE_INT;
  node->val.i = num;

  return 0;
}

static int
list(be_node *node, struct state *st){
  while(st->curr[0] != 'e' && st->parsed < st->size) {

  }
  if(st->parsed < st->size){
    return 1;
  } else {
    return 0;
  }
}

int
member(be_node *node, struct state *st){
  int err = 0;
  switch(st->curr[0]) {
    case 'i':
      err = integer(node, st);
      break;
    case 'l':
      err = list(node, st);
      break;
    case 'd':
      err = dict(node, st);
      break;
    case 'e':
      // member shouldn't get this
      err = 1;
      break;
    default:
      // we've hit a string
      err = string(node, st);
  }
  return err;
}


be_node *
be_decode(const char *str, unsigned int size){
  struct state st;
  st.parsed = st.size = size;
  st.buf    = st.cur  = str;
  be_node *node = calloc(1, sizeof(be_node));
  return member(node, &st);
}

char *
be_encode(be_node *node){

}

void
be_free(be_node *node) {
  be_node *next = node;
  while(node != NULL){
    next = node->next;
    free(node);
    node = next;
  }
}