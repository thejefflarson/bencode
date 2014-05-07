#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bencode.h"

#define ok(test, message) do {\
  int __test_count = __COUNTER__ + 1;\
  if(test) {\
    printf("ok %i - %s, %s: %i\n", __test_count, message, __FILE__, __LINE__);\
  } else {\
    printf("not ok %i - %s, %s: %i\n", __test_count, message, __FILE__, __LINE__);\
    exit(1);\
  }\
} while(0)

#define start_test printf("1..%i\n", __COUNTER__)

// static void
// test_integer(){
//   be_node_t *node = be_decode("i42e", 4);
//   ok(node != NULL, "decoded integer without errors");
//   ok(node->val.i == 42, "returned 42");
//   ok(node->type == BE_INT, "returned an integer");
//   be_free(node);
// }

static void
test_string(){
  be_node_t *node = be_decode("7:tolstoy", 9);
  ok(node != NULL, "decoded string without errors");
  ok(node->type == BE_STR, "returned a string");
  ok(strncmp("tolstoy", node->val.str, 7) == 0, "returned tolstoy");
  be_free(node);
}

int
main(){
  start_test;
  // test_integer();
  test_string();
  return 0;
}
