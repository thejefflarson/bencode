#ifndef BENCODE_H_
#define BENCODE_H_

typedef enum {
  DHT_BE_STR,
  DHT_BE_INT,
  DHT_BE_LIST,
  DHT_BE_DICT
} be_type;

typedef struct {
  char *key;
  struct dht_be_node *val;
} be_dict;

typedef struct dht_be_node {
  be_type type;
  union {
    long long i;
    char* str;
    dht_be_node **list;
    dht_be_dict *dict;
  } val;
} be_node;

be_node *
be_decode(char *str, long long size);

char *
be_encode(be_node *node);

void
be_free(be_node *node);

#endif