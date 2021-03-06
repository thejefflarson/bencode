#ifndef BENCODE_H_
#define BENCODE_H_

#include <stdint.h>

typedef enum {
  BE_STR,
  BE_INT,
  BE_LIST,
  BE_DICT
} be_type;

struct be_node;

typedef struct be_list_node {
  struct be_node *node;
  struct be_list_node *next;
} be_list_node_t;

typedef struct {
  uint64_t length;
  be_list_node_t **values;
} be_dict_t;

typedef struct {
  char *key;
  struct be_node *val;
} be_dict_value_t;

typedef struct be_node {
  be_type type;
  union {
    long long i;
    char* str;
    be_list_node_t *list;
    be_dict_t *dict;
  } val;
} be_node_t;


be_node_t *
be_node_new();

be_node_t *
be_decode(const char *str, uint64_t size);

char *
be_encode(be_node_t *node);

void
be_free(be_node_t *node);

#endif
