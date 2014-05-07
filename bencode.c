#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bencode.h"

typedef struct be_stack {
  be_node_t *node;
  struct be_stack *next;
} be_stack_t;


static be_stack_t *
push(be_stack_t *stack, be_type type){
  be_stack_t *stk = calloc(1, sizeof(be_stack_t));
  be_node_t *node = calloc(1, sizeof(be_stack_t));
  stk->node = node;
  stk->node->type = type;
  stack->next = stk;
  return stack;
}

static be_stack_t *
value(be_stack_t *stack, const char *str, uint64_t *parsed){
  be_stack_t *parent = stack->next;
  if(stack->next == NULL) return NULL;
  switch(parent->node->type) {
    case BE_LIST: {
      be_node_t **tmp;
      parent->node->length += 1;
      tmp = realloc(parent->node->val.list, parent->node->length);
      if(tmp == NULL) return NULL;
      parent->node->val.list = tmp;
      parent->node->val.list[parent->node->length - 1] = stack->node;
      free(stack);
      parent->next = NULL;
      break;
    }
    case BE_DICT:
      break;
    case BE_INT: {
      char *end_ptr;
      parent->node->type = BE_INT;
      parent->node->val.i = strtoll(str + *parsed, &end_ptr, 10);
      free(stack->node);
      parent->next = NULL;
      *parsed += end_ptr - str;
      break;
    }
    case BE_STR: {
      char *end_ptr;
      long i = strtol(str, &end_ptr, 10);
      if(parsed[i] != ':') return NULL;
      // todo check error
      parent->node->type = BE_STR;
      parent->node->val.str = strndup(str + *parsed, i);
      free(stack);
      parent->next = NULL;
      *parsed += i;
      break;
    }
  }
  free(stack);
  return parent;
}

be_node_t *
be_decode(const char *str, uint64_t size){
  uint64_t parsed = 0;
  be_stack_t *stack = calloc(1, sizeof(be_stack_t));
  int err = 0;
  while(parsed < size && !err) {
    switch(str[parsed]) {
      case 'i':
        stack = push(stack, BE_INT);
        parsed++;
        stack = value(stack, str, &parsed);
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
        if(str[parsed] == '-' || (str[parsed] > '0' && str[parsed] <= '9')) {
          stack = push(stack, BE_STR);
          stack = value(stack, str, &parsed);
        } else {
          err = 1;
        }
        break;
    }
  }
  return stack->node;
}

char *
be_encode(be_node_t *node){
  return "";
}

void
be_free(be_node_t *node) {

}