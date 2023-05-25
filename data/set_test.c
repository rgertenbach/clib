#include <stdbool.h>
#include <stdlib.h>
#include "set.h"
#include "../test/minunit.h"

// Tests accessing the Data structure's internals.
#define cleanup() do { \
  set_destroy(set); \
  free(set); \
} while (0)


bool
match(void const *a, void const *b)
{
  return *(int *)a == *(int *)b;
}

char *
test_init_works(void)
{
  struct Set set;
  set_init(&set, match, NULL);
  return NULL;
}

void all_tests(void)
{
  mu_run_test(test_init_works);
}

int main(int argc, char **argv)
{
  if (argc > 1) {
    fprintf(stderr, "Too many arguments supplied\n");
    exit(1);
  }
  printf("%s\n", argv[0]);
  mu_main(all_tests);
}
