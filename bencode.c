#include <stdlib.h>
#include <stdint.h>
#include "bencode.h"

typedef struct stack {
  be_node *node;
  stack_t *next;
} stack_t;




be_node *
be_decode(const char *str, long long size){
  long long parsed = size;
  stack_t *stack = calloc(1, sizeof(stack));
  be_node *root = calloc(1, sizeof(be_node));
  stack->node = root;

  int err = 0;
  be_type state;

  while(parsed < size) {
    switch(str[parsed]) {
      case 'i':
        integer(stack, str, &parsed);
        break;
      case 'l':
        stack = push(stack, BE_LIST);
        parsed++;
        break;
      // TODO:
      // case 'd':
      //   stack = push(stack, BE_DICT);
      //   parsed++;
      //   break;
      case 'e':
        value(stack, state);
        break;
      default:
        if(str[parsed] = '-' || (str[parsed] > '0' && str[parsed] <= '9')) {
          string(stack, str, &parsed);
        } else {
          err = 1;
        }
        break;
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