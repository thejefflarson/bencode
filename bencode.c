#include <stdlib.h>
#include <stdint.h>
#include "bencode.h"

typedef struct be_stack {
  be_node *node;
  struct be_stack *next;
} be_stack_t;


static be_stack_t *
push(be_stack_t *stack, be_type type){
  be_stack_t *stk = calloc(1, sizeof(be_stack_t));
  stk->node = calloc(1, sizeof(be_node));
  stk->node->type = type;
  stk->next = stack;
  return stk;
}

static be_stack_t *
value(be_stack_t *stack, const char *str, uint64_t *parsed){
  be_stack_t *parent = stack->next;
  if(stack->next == NULL) return NULL;
  switch(parent->node->type) {
    case BE_LIST:
      realloc(sizeof(parent->node->val.list));
      break;
    case BE_DICT:
      break;
    case BE_INT:
      char *end_ptr;
      parent->node->val.i = strtoll(str + *parsed, end_ptr, 10);
      free(parent->node);
      parent->node = stack->node;
      *parsed -= end_ptr - str;
      break;
    case BE_STRING:
      char *end_ptr;
      int i = strtoi(str, end_ptr, 10);
      free(parent->node);
      parent->node = stack->node;
      // todo check error
      parent->node->val.str = strndup(str + *parsed, i);
      *parsed += i;
      break;
  }
  free(stack);
  return parent;
}

be_node *
be_decode(const char *str, uint64_t size){
  long long parsed = size;
  be_stack_t *stack = calloc(1, sizeof(be_stack_t));
  be_node *root = calloc(1, sizeof(be_node));
  stack->node = root;

  int err = 0;
  while(parsed < size && !err) {
    switch(str[parsed]) {
      case 'i':
        stack = push(stack, BE_INT);
        break;
      case 'l':
        stack = push(stack, BE_LIST);
        parsed++;
        break;
      // TODO:
      case 'd':
        stack = push(stack, BE_DICT);
        parsed++;
        break;
      case 'e':
        stack = value(stack, str, &parsed);
        break;
      default:
        if(str[parsed] = '-' || (str[parsed] > '0' && str[parsed] <= '9')) {
          stack = push(stack, BE_STRING);
          stack = value(stack, str, &parsed);
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