#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../test/minunit.h"
#include "flags.h"

#define cleanup() do { \
  flags_flag_pool_destroy(flags); \
} while (0)

#define abs(a) (((a) < 0) ? -(a) : (a))

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

#define nflags 4
#define argc (nflags + 1)
#define bool_cleanup() do { \
  cleanup(); \
  for (size_t i = 0; i < argc; ++i) free(argv[i]); \
  free(argv); \
} while (0)

char *test_bool(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, nflags);

  flags_add_bool(flags, "--def-false-then-true", false, "help");
  flags_add_bool(flags, "--def-true-then-false", true, "help");
  flags_add_bool(flags, "--def-false-then-true2", false, "help");
  flags_add_bool(flags, "--def-false-then-false", false, "help");

  bool b1 = flags_get_bool(flags, "--def-false-then-true");
  bool b2 = flags_get_bool(flags, "--def-true-then-false");
  bool b3 = flags_get_bool(flags, "--def-false-then-true2");
  bool b4 = flags_get_bool(flags, "--def-false-then-false");

  mu_test("b1 is false", !b1, cleanup);
  mu_test("b2 is true",  b2, cleanup);
  mu_test("b3 is false", !b3, cleanup);
  mu_test("b4 is false", !b4, cleanup);

  char **argv = malloc(argc * sizeof(char *));
  for (size_t i = 0; i < argc; ++i) {
    argv[i] = malloc(FLAGS_MAX_NAME_LEN);
  }

  strcpy(argv[0], "argv[0]");
  strcpy(argv[1], "--def-false-then-true");
  strcpy(argv[2], "--no-def-true-then-false");
  strcpy(argv[3], "--no-no-def-false-then-true2");
  strcpy(argv[4], "--no-no-no-def-false-then-false");

  flags_parse_flags(flags, argc, argv);

  bool v1 = flags_get_bool(flags, "--def-false-then-true");
  mu_test("--def-false-then-true is true'", v1, bool_cleanup);

  bool v2 = flags_get_bool(flags, "--def-true-then-false");
  mu_test("--def-true-then-false is false'", !v2, bool_cleanup);

  bool v3 = flags_get_bool(flags, "--def-false-then-true2");
  mu_test("-no-no-def-false-then-true2", v3, bool_cleanup);

  bool v4 = flags_get_bool(flags, "--def-false-then-false");
  mu_test("--no-no-no-def-false-then-false", !v4, bool_cleanup);

  bool_cleanup();

  return NULL;
}

char *test_float(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 2);

  flags_add_float(flags, "--name -n", 12.1, "help");
  float val = flags_get_float(flags, "-n");
  mu_test("Default is '12.1'", mu_approx_equal(val, 12.1, 0.01), cleanup);

  char **argv = malloc(3 * sizeof(char *));
  for (size_t i = 0; i < 3; ++i) {
    argv[i] = malloc(20);
  }
  strcpy(argv[0], "argv[0]");
  strcpy(argv[1], "--name");
  strcpy(argv[2], "52.1");

  flags_parse_flags(flags, 3, argv);

  val = flags_get_float(flags, "-n");
  mu_test("Override is '52.1'", mu_approx_equal(val, 52.1, 0.01), cleanup);

  cleanup();
  return NULL;
}

char *test_double(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 2);

  flags_add_double(flags, "--name -n", 12.1, "help");
  double val = flags_get_double(flags, "-n");
  mu_test("Default is '12.1'", mu_approx_equal(val, 12.1, 0.01), cleanup);

  char **argv = malloc(3 * sizeof(char *));
  for (size_t i = 0; i < 3; ++i) {
    argv[i] = malloc(20);
  }
  strcpy(argv[0], "argv[0]");
  strcpy(argv[1], "--name");
  strcpy(argv[2], "52.1");

  flags_parse_flags(flags, 3, argv);

  val = flags_get_double(flags, "--name");
  mu_test("Override is '52.1'", mu_approx_equal(val, 52.1, 0.01), cleanup);

  cleanup();
  return NULL;
}

char *test_long_double(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 2);

  flags_add_long_double(flags, "--name -n", 12.1, "help");
  long double val = flags_get_long_double(flags, "-n");
  mu_test("Default is '12.1'", mu_approx_equal(val, 12.1, 0.01), cleanup);

  char **argv = malloc(3 * sizeof(char *));
  for (size_t i = 0; i < 3; ++i) {
    argv[i] = malloc(20);
  }
  strcpy(argv[0], "argv[0]");
  strcpy(argv[1], "--name");
  strcpy(argv[2], "52.1");

  flags_parse_flags(flags, 3, argv);

  val = flags_get_long_double(flags, "--name");
  mu_test("Override is '52.1'", mu_approx_equal(val, 52.1, 0.01), cleanup);

  cleanup();
  return NULL;
}

char *test_string_list(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 2);

  flags_add_string_list(flags, "--name -n", "Text1,Text2", "help");
  char **value = flags_get_string_list(flags, "--name");
  struct FlagsFlag *flag = flags_get(flags, "--name");
  mu_test("Flag has 2 elements", flags_list_size(flag) == 2, cleanup);
  mu_test("First element is Text1", !strcmp(value[0], "Text1"), cleanup);
  mu_test("Second element is Text2", !strcmp(value[1], "Text2"), cleanup);

  char **argv = malloc(3 * sizeof(char *));
  for (size_t i = 0; i < 3; ++i) {
    argv[i] = malloc(40);
  }
  strcpy(argv[0], "argv[0]");
  strcpy(argv[1], "--name");
  strcpy(argv[2], "NewText1,NewText2,NewText3");

  flags_parse_flags(flags, 3, argv);

  value = flags_get_string_list(flags, "--name");
  mu_test("Flag has 3 elements", flags_list_size(flag) == 3, cleanup);
  mu_test("First element is NewText1", !strcmp(value[0], "NewText1"), cleanup);
  mu_test("Second element is NewText2", !strcmp(value[1], "NewText2"), cleanup);
  mu_test("Third element is NewText3", !strcmp(value[2], "NewText3"), cleanup);

  cleanup();
  return NULL;
}

#define cleanup_help() do { \
  free(help); \
  cleanup(); \
} while (0)


char *test_generate_help(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 2);

  flags_add_string(flags, "--name -n", "default", "help");
  flags_add_string(flags, "-o --other-flag", "default_value", "help2");
  char *help = malloc(1e5);
  char *expected = "Flags:\n--name, -n\n\thelp\n-o, --other-flag\n\thelp2\n";
  flags_generate_help(help, flags);
  mu_test("Help matches", !strcmp(help, expected), cleanup_help);

  cleanup_help();    
  return NULL;
}

char *test_set_help_names(void)
{
  struct FlagsFlagPool *flags = malloc(sizeof(struct FlagsFlagPool));
  flags_flag_pool_init(flags, 2);

  mu_test(
      "In the beginning there are default help flags", 
      flags->n_help_names == 2,
      cleanup);
  mu_test(
      "In the beginning there are default help flags", 
      !strcmp(flags->help_names[0], "-h"),
      cleanup);
  mu_test(
      "In the beginning there are default help flags", 
      !strcmp(flags->help_names[1], "--help"),
      cleanup);

  flags_set_help(flags, NULL);
  mu_test("After NULL we have no help names", flags->n_help_names == 0, cleanup);
  mu_test("After NULL we have NULL help names", flags->help_names == NULL, cleanup);

  // Again to check override behavior.
  flags_set_help(flags, NULL);
  mu_test("After NULL we have no help names", flags->n_help_names == 0, cleanup);
  mu_test("After NULL we have NULL help names", flags->help_names == NULL, cleanup);

  flags_set_help(flags, "--flag1");
  mu_test("After flag1 we have one help name", flags->n_help_names == 1, cleanup);
  mu_test("After flag1 the flag name is --flag1", !strcmp(flags->help_names[0], "--flag1"), cleanup);

  flags_set_help(flags, "-g --flag2");
  mu_test(
      "After -g --flag2 we have two help names", 
      flags->n_help_names == 2,
      cleanup);
  mu_test(
      "After -g --flag2 the first flag name is -g", 
      !strcmp(flags->help_names[0], "-g"), 
      cleanup);
  mu_test(
      "After -g --flag2 the second flag name is --flag2", 
      !strcmp(flags->help_names[1], "--flag2"),
      cleanup);

  cleanup();
  return NULL;
}

#undef nflags
#undef argc
#undef bool_cleanup

void all_tests(void)
{
  mu_run_test(test_string);
  mu_run_test(test_int64);
  mu_run_test(test_int32);
  mu_run_test(test_int16);
  mu_run_test(test_int8);
  mu_run_test(test_bool);
  mu_run_test(test_float);
  mu_run_test(test_double);
  mu_run_test(test_long_double);
  mu_run_test(test_string_list);
  mu_run_test(test_generate_help);
  mu_run_test(test_set_help_names);
}

int main(void)
{
  mu_main(all_tests);
}
