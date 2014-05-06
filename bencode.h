#ifndef BENCODE_H_
#define BENCODE_H_

typedef enum {
  BE_STR,
  BE_INT,
  BE_LIST,
  BE_DICT
} be_type;

typedef struct {
  char *key;
  struct be_node *val;
} be_dict_value;

typedef struct be_node {
  be_type type;
  union {
    long long i;
    char* str;
    struct be_node *list;
    be_dict_value *dict;
  } val;
} be_node;

be_node *
be_decode(char *str, int size);

char *
be_encode(be_node *node);

void
be_free(be_node *node);

#endif
