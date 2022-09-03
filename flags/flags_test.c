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
  mu_test("Override is 'override'", !strcmp(val, "override"), cleanup);

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

char *test_int32(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 2);

  flags_add_int32(flags, "--name -n", 12, "help");
  int32_t val = flags_get_int32(flags, "-n");
  mu_test("Default is 'default'", val == 12, cleanup);

  char **argv = malloc(3 * sizeof(char *));
  for (size_t i = 0; i < 3; ++i) {
    argv[i] = malloc(20);
  }
  strcpy(argv[0], "argv[0]");
  strcpy(argv[1], "--name");
  strcpy(argv[2], "52");

  flags_parse_flags(flags, 3, argv);

  val = flags_get_int32(flags, "-n");
  mu_test("Override is 'override'", val == 52, cleanup);

  cleanup();
  return NULL;
}

char *test_int16(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 2);

  flags_add_int16(flags, "--name -n", 12, "help");
  int16_t val = flags_get_int16(flags, "-n");
  mu_test("Default is 'default'", val == 12, cleanup);

  char **argv = malloc(3 * sizeof(char *));
  for (size_t i = 0; i < 3; ++i) {
    argv[i] = malloc(20);
  }
  strcpy(argv[0], "argv[0]");
  strcpy(argv[1], "--name");
  strcpy(argv[2], "52");

  flags_parse_flags(flags, 3, argv);

  val = flags_get_int16(flags, "-n");
  mu_test("Override is 'override'", val == 52, cleanup);

  cleanup();
  return NULL;
}

char *test_int8(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 2);

  flags_add_int8(flags, "--name -n", 12, "help");
  int8_t val = flags_get_int8(flags, "-n");
  mu_test("Default is 'default'", val == 12, cleanup);

  char **argv = malloc(3 * sizeof(char *));
  for (size_t i = 0; i < 3; ++i) {
    argv[i] = malloc(20);
  }
  strcpy(argv[0], "argv[0]");
  strcpy(argv[1], "--name");
  strcpy(argv[2], "52");

  flags_parse_flags(flags, 3, argv);

  val = flags_get_int8(flags, "-n");
  mu_test("Override is 'override'", val == 52, cleanup);

  cleanup();
  return NULL;
}

#define argc 5
#define bool_cleanup() do { \
  cleanup(); \
  for (size_t i = 0; i < argc; ++i) free(argv[i]); \
  free(argv); \
} while (0)

char *test_bool(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 5);

  flags_add_bool(flags, "--def-false-then-true", false, "help");
  flags_add_bool(flags, "--def-true-then-false", true, "help");
  flags_add_bool(flags, "--no-def2-false-then-true", false, "help");
  flags_add_bool(flags, "--no-def3-true-then-false", true, "help");

  bool b1 = flags_get_bool(flags, "--def-false-then-true");
  bool b2 = flags_get_bool(flags, "--def-true-then-false");
  bool b3 = flags_get_bool(flags, "--no-def2-false-then-true");
  bool b4 = flags_get_bool(flags, "--no-def3-true-then-false");

  mu_test("b1 is false", !b1, cleanup);
  mu_test("b2 is true",  b2, cleanup);
  mu_test("b3 is false", !b3, cleanup);
  mu_test("b4 is true", b4, cleanup);

  char **argv = malloc(argc * sizeof(char *));
  for (size_t i = 0; i < argc; ++i) {
    argv[i] = malloc(FLAGS_MAX_NAME_LEN);
  }

  strcpy(argv[0], "argv[0]");
  strcpy(argv[1], "--def-false-then-true");
  strcpy(argv[2], "--no-def-true-then-false");
  strcpy(argv[3], "--no-def2-false-then-true");
  strcpy(argv[4], "--no-def3-true-then-false");

  flags_parse_flags(flags, argc, argv);

  bool v1 = flags_get_bool(flags, "--def-false-then-true");
  mu_test("--def-false-then-true is true'", v1, bool_cleanup);

  bool v2 = flags_get_bool(flags, "--def-true-then-false");
  mu_test("--def-true-then-false is false'", !v2, bool_cleanup);

  bool v3 = flags_get_bool(flags, "--no-def2-false-then-true");
  mu_test("--no-def2-true-then-false is true'", v3, bool_cleanup);

  bool v4 = flags_get_bool(flags, "--no-def3-true-then-false");
  mu_test("--no-def3-true-then-false is true'", v4, bool_cleanup);

  bool_cleanup();

  return NULL;
}

void all_tests(void)
{
  mu_run_test(test_string);
  mu_run_test(test_int64);
  mu_run_test(test_int32);
  mu_run_test(test_int16);
  mu_run_test(test_int8);
  mu_run_test(test_bool);
}

int main(void)
{
  mu_main(all_tests);
}
