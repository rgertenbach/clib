#include <stdlib.h>

#include "../test/minunit.h"
#include "chmap.h"

// Tests accessing the Data structure's internals.
#define cleanup() do { \
  chmap_destroy(map); \
  free(map); \
} while (0)

struct KV {
  char *key;
  int value;
};

bool
streq(void const * a, void const * b)
{
  char * s1 = ((struct KV *) a)->key;
  char * s2 = ((struct KV *) b)->key;
  while (*s1 != '\0' && *s2 != '\0') if (*(s1++) != *(s2++)) return false;
  return *s1 == '\0' && *s2 == '\0';
}

// Horrible hash function.
size_t
hash(void const * key)
{
  char * s = (char *)key;
  size_t out = 0;
  while (*s != '\0') out = out * *s + *s;
  return out;
}


char *
test_init_works(void)
{
  struct CHMap * map = malloc(sizeof(struct CHMap));
  chmap_init(map, 10, hash, streq, NULL);
  mu_test("Size is 0", map->sz == 0, cleanup);
  cleanup();
  return NULL;
}


void
all_tests(void)
{
  mu_run_test(test_init_works);
}

int
main(int argc, char **argv)
{
  if (argc > 1) {
    fprintf(stderr, "Too many arguments supplied\n");
    exit(1);
  }
  printf("%s\n", argv[0]);
  mu_main(all_tests);
}
