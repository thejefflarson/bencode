#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "bencode.h"

typedef struct be_stack {
  be_node_t *node;
  struct be_stack *next;
} be_stack_t;


static be_stack_t *
push(be_stack_t *stack, be_type type){
  printf("push %i\n", type);
  be_stack_t *stk = calloc(1, sizeof(be_stack_t));
  be_node_t *node = calloc(1, sizeof(be_node_t));
  stk->node = node;
  stk->node->type = type;
  stk->next = stack;
  return stk;
}

static be_stack_t *
pop(be_stack_t *stack) {
  printf("pop %i\n", stack->node->type);
  be_stack_t *parent = stack->next;
  free(stack);
  free(stack->node);
  parent->next = NULL;
  return parent;
}

static be_stack_t *
value(be_stack_t *stack, const char *str, uint64_t *parsed){
  be_stack_t *parent = stack->next;

  // TODO: free stack
  if(stack->next == NULL)
    return NULL;

  switch(stack->node->type) {
    case BE_LIST: {
      be_list_node_t *tail = parent->node->val.list;
      while(tail && tail->next)
        tail = tail->next;
      tail = calloc(1, sizeof(be_list_node_t));
      tail->next = NULL;
      parent->node = tail->node;
      parent->next = NULL;
      break;
    }
    case BE_DICT:
      break;
    case BE_INT: {
      char *end_ptr;
      parent->node->type = BE_INT;
      parent->node->val.i = strtoll(str + *parsed, &end_ptr, 10);
      *parsed += end_ptr - str;
      break;
    }
    case BE_STR: {
      char *end_ptr;
      long i = strtol(str, &end_ptr, 10);
      *parsed += end_ptr - str;

      // TODO free stack node when we get to these errors
      if(errno == EINVAL || errno == ERANGE)
        return NULL;
      if(str[*parsed] != ':')
        return NULL;

      (*parsed)++;
      parent->node->type = BE_STR;
      parent->node->val.str = strndup(str + *parsed, i);
      *parsed += i;
      // TODO: check return
      break;
    }
  }
  pop(stack);
  return parent;
}

// TODO: error checking
be_node_t *
be_decode(const char *str, uint64_t size){
  uint64_t parsed = 0;
  be_stack_t *stack = calloc(1, sizeof(be_stack_t));
  stack->node = calloc(1, sizeof(be_node_t));
  while(parsed < size) {
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
        }
        break;
    }
  }
  be_node_t *node = stack->node;
  free(stack);
  return node;
}

char *
be_encode(be_node_t *node){
  return "";
}

void
be_free(be_node_t *node) {
  if(node->type == BE_STR)
    free(node->val.str);
  free(node);
}