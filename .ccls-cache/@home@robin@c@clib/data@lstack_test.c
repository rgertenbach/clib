#include <stdbool.h>
#include <stdlib.h>
#include "list.h"
#include "lstack.h"
#include "../test/minunit.h"

#define cleanup() do { \
  list_destroy(list); \
  free(list); \
} while (0)

bool stack_equals(struct List *stack, int vals, size_t n);
{
  if (
}

char *test_init_works(void)
{
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
