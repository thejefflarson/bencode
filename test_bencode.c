#include <stdio.h>
#include <stdlib.h>
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


static void
test_integer(){
  be_node_t *node = be_decode("i42e", 4);
  ok(node != NULL, "decoded integer without errors");
  ok(node->val.i == 42, "returned correct value");
  ok(node->type == BE_INT, "returned an integer");
  be_free(node);
}

int
main(){
  start_test;
  test_integer();
  return 0;
}
