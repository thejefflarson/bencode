#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bencode.h"
#include "scanner.h"

#define ok(test, message) do {\
  int __test_count = __COUNTER__ + 1;\
  if(test) {\
    printf("ok %i\n", __test_count);\
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
  ok(node->val.i == 42, "returned 42");
  ok(node->type == BE_INT, "returned an integer");
  be_free(node);
}

// static void
// test_string(){
//   be_node_t *node = be_decode("7:tolstoy", 9);
//   ok(node != NULL, "decoded string without errors");
//   ok(node->type == BE_STR, "returned a string");
//   ok(strncmp("tolstoy", node->val.str, 7) == 0, "returned tolstoy");
//   be_free(node);
// }

// static void
// test_list(){
//   be_node_t *node = be_decode("l7:tolstoyi42ee", 9);
//   ok(node != NULL, "decoded list without errors");
//   printf("%i\n", node->type);
//   ok(node->type == BE_LIST, "returned a list");
//   int i = 0;
//   for(be_list_node_t *tail = node->val.list; tail->next; tail = tail->next, i++);
//   ok(i == 2, "right number of elements");
//   ok(node->val.list->node->type == BE_INT, "first element is a string");
//   ok(strncmp("tolstoy", node->val.list->node->val.str, 7) == 0, "is tolstoy");
//   ok(node->val.list->next->node->type == BE_INT, "second element is an int");
//   ok(node->val.list->next->node->val.i == 42, "is 42");
//   be_free(node);
// }

static void
test_scanner(){
  char *str = "l7:tolstoyi42ee";

  be_node_t node;
  memset(&node, 0, sizeof(be_node_t));
  YYLTYPE pos;
  memset(&pos, 0, sizeof(YYLTYPE));

  ok(bencode_lex(&node, &pos, str, strlen(str)) == LIST, "LIST");
  pos.first_column = pos.last_column;
  ok(bencode_lex(&node, &pos, str, strlen(str)) == STRING, "STRING");
  pos.first_column = pos.last_column;
  ok(bencode_lex(&node, &pos, str, strlen(str)) == INT, "INT");
  pos.first_column = pos.last_column;
  ok(bencode_lex(&node, &pos, str, strlen(str)) == NUMBER, "NUMBER");
  pos.first_column = pos.last_column;
  ok(bencode_lex(&node, &pos, str, strlen(str)) == END, "END");
  pos.first_column = pos.last_column;
  ok(bencode_lex(&node, &pos, str, strlen(str)) == END, "END");
}

int
main(){
  start_test;
  // test_integer();
  // test_string();
  // test_list();
  test_scanner();
  return 0;
}
