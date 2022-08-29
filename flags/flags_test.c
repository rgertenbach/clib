#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../test/minunit.h"
#include "flags.h"

#define cleanup() do { \
  flags_flag_pool_destroy(flags); \
} while (0)


char *test_string(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 2);

  flags_add_string(flags, "--name -n", "default", "help");
  char *val = flags_get_string(flags, "-n");
  mu_test("Default is 'default'", !strcmp(val, "default"), cleanup);

  char **argv = malloc(3 * sizeof(char *));
  for (size_t i = 0; i < 3; ++i) {
    argv[i] = malloc(20);
  }
  strcpy(argv[0], "argv[0]");
  strcpy(argv[1], "--name");
  strcpy(argv[2], "override");

  flags_parse_flags(flags, 3, argv);

  val = flags_get_string(flags, "-n");
  mu_test("Override is 'override'", !strcmp(val, "overide"), cleanup);

  cleanup();
  return NULL;
}

char *test_int64(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 2);

  flags_add_int64(flags, "--name -n", 12, "help");
  int64_t val = flags_get_int64(flags, "-n");
  mu_test("Default is 'default'", val == 12, cleanup);

  char **argv = malloc(3 * sizeof(char *));
  for (size_t i = 0; i < 3; ++i) {
    argv[i] = malloc(20);
  }
  strcpy(argv[0], "argv[0]");
  strcpy(argv[1], "--name");
  strcpy(argv[2], "52");

  flags_parse_flags(flags, 3, argv);

  val = flags_get_int64(flags, "-n");
  mu_test("Override is 'override'", val == 52, cleanup);

  cleanup();
  return NULL;
}

void all_tests(void)
{
  test_string();
  test_int64();
}

int main(void)
{
  mu_main(all_tests);
}
