#include "../test/minunit.h"
#include "bigint.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define clean_actual()                                                        \
  do {                                                                        \
    biguint_delete(x);                                                        \
  } while (0)

char *
test_biguint_format_binary(void)
{
  struct BigUint * x = biguint_from_uint(234);
  char * actual = malloc(65);
  biguint_format_binary(actual, x);
  mu_test("234 = 0b11101010", strcmp(actual, "11101010") == 0, clean_actual);
  clean_actual();
  return NULL;
}

char *
test_biguint_ilsh(void)
{
  struct BigUint * x = biguint_from_uint(234);
  char * actual = malloc(200);
  biguint_ilsh(x, 2);
  biguint_format_binary(actual, x);
  mu_test("234 << 2 = 0b1110101000", strcmp(actual, "1110101000") == 0,
          clean_actual);
  biguint_ilsh(x, 100);
  biguint_format_binary(actual, x);
  fprintf(stderr, "%s %zu bits decimal: %lu %lu\n", actual, biguint_highest_bit(x), x->bits[1], x->bits[0]);
  mu_test(
      "234 << 102",
      strcmp(actual, "11101010000000000000000000000000000000000000000000000000"
                     "000000000000000000000000000000000000000000000000000000")
          == 0,
      clean_actual);
  clean_actual();
  return NULL;
}

void
all_tests(void)
{
  mu_run_test(test_biguint_format_binary);
  mu_run_test(test_biguint_ilsh);
}

int
main(int argc, char ** argv)
{
  if (argc > 1) {
    fprintf(stderr, "Too many arguments supplied\n");
    exit(1);
  }
  printf("%s\n", argv[0]);
  mu_main(all_tests);
}
