#include <stdio.h>
#include <stdlib.h>

#define ok(test, message) do {\
  int __test_count = __COUNTER__ + 1;\
  if(test) {\
    printf("ok %i - %s, %s: %i\n", __test_count, message, __FILE__, __LINE__);\
  } else {\
    printf("not ok %i - %s, %s: %i\n", __test_count, message, __FILE__, __LINE__);\
    exit(1);\
  }\
} while(0)

#define start_test printf("1..%i\n", __COUNTER__);

static void
test_decode(){
  int res = 1;
  ok(res == 0, "can decode");
}

int
main(){
  start_test
  test_decode();
  return 0;
}
