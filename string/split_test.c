#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "../test/minunit.h"
#include "split.h"

#define MAXLEN 4
#define MAXELEM 4

#define setup() do { \
  dest = malloc(MAXLEN * sizeof(char *)); \
  for (size_t i = 0; i < MAXELEM; ++i) dest[i] = malloc(MAXLEN); \
} while(0)


#define cleanup() do { \
  for (size_t it = 0; it < MAXELEM; ++it) free(dest[it]); \
  free(dest); \
} while (0)

char *test_unlimited_strnsplit_single_elem(void)
{
  char **dest;
  setup();
  size_t n = strnsplit(dest, "foo", ",", SSIZE_MAX, SSIZE_MAX);
  mu_test("Extracted one element", n == 1, cleanup);
  mu_test("Element is \"foo\"", strcmp(dest[0], "foo") == 0, cleanup);
  cleanup();
  return NULL;
}

char *test_unlimited_strnsplit_two_elems(void)
{
  char **dest;
  setup();
  size_t n = strnsplit(dest, "foo,bar", ",", SSIZE_MAX, SSIZE_MAX);
  mu_test("Extracted two elements", n == 2, cleanup);
  mu_test("1st Element is \"foo\"", strcmp(dest[0], "foo") == 0, cleanup);
  mu_test("2nd Element is \"bar\"", strcmp(dest[1], "bar") == 0, cleanup);
  cleanup();
  return NULL;
}

char *test_unlimited_strnsplit_ignore_trailing_delimiter(void)
{
  char **dest;
  setup();
  size_t n = strnsplit(dest, "foo,bar,", ",", SSIZE_MAX, SSIZE_MAX);
  mu_test("Extracted two elements", n == 2, cleanup);
  mu_test("1st Element is \"foo\"", strcmp(dest[0], "foo") == 0, cleanup);
  mu_test("2nd Element is \"bar\"", strcmp(dest[1], "bar") == 0, cleanup);
  cleanup();
  return NULL;
}

char *test_unlimited_strnsplit_two_elems_long_delimiter(void)
{
  char **dest;
  setup();
  size_t n = strnsplit(dest, "foobazbar", "baz", SSIZE_MAX, SSIZE_MAX);
  mu_test("Extracted two elements", n == 2, cleanup);
  mu_test("1st Element is \"foo\"", strcmp(dest[0], "foo") == 0, cleanup);
  mu_test("2nd Element is \"bar\"", strcmp(dest[1], "bar") == 0, cleanup);
  cleanup();
  return NULL;
}

char *test_strnsplit_too_many_elems(void)
{
  char **dest;
  setup();
  size_t n = strnsplit(dest, "foo,bar,baz,bim,bom,box", ",", 4, 4);
  mu_test("Extracted four elements", n == 4, cleanup);
  mu_test("1st Element is \"foo\"", strcmp(dest[0], "foo") == 0, cleanup);
  mu_test("2nd Element is \"bar\"", strcmp(dest[1], "bar") == 0, cleanup);
  mu_test("3rd Element is \"baz\"", strcmp(dest[2], "baz") == 0, cleanup);
  mu_test("4th Element is \"bim\"", strcmp(dest[3], "bim") == 0, cleanup);
  cleanup();
  return NULL;
}

char *test_strnsplit_too_long_elems(void)
{ 
  char **dest;
  setup();
  size_t n = strnsplit(dest, "foobar,bazbim", ",", 4, 4);
  mu_test_equal("Extracted", 2, n, cleanup);
  mu_test("1st Element is \"foo\"", strcmp(dest[0], "foo") == 0, cleanup);
  mu_test("2nd Element is \"baz\"", strcmp(dest[1], "baz") == 0, cleanup);
  cleanup();
  return NULL;
}

char *test_unlimited_strnsplit_no_delimiter(void)
{
  char **dest;
  setup();
  size_t n = strnsplit(dest, "flox", "", SSIZE_MAX, SSIZE_MAX);
  mu_test("Extracted 4 elements", n == 4, cleanup);
  mu_test("1st Element is \"f\"", strcmp(dest[0], "f") == 0, cleanup);
  mu_test("2nd Element is \"l\"", strcmp(dest[1], "l") == 0, cleanup);
  mu_test("3rd Element is \"o\"", strcmp(dest[2], "o") == 0, cleanup);
  mu_test("4th Element is \"x\"", strcmp(dest[3], "x") == 0, cleanup);
  cleanup();
  return NULL;
}

char *test_strsplit_single_elem(void)
{
  char **dest;
  setup();
  size_t n = strsplit(dest, "foo", ",");
  mu_test("Extracted one element", n == 1, cleanup);
  mu_test("Element is \"foo\"", strcmp(dest[0], "foo") == 0, cleanup);
  cleanup();
  return NULL;
}

char *test_strsplit_two_elems(void)
{
  char **dest;
  setup();
  size_t n = strsplit(dest, "foo,bar", ",");
  mu_test("Extracted two elements", n == 2, cleanup);
  mu_test("1st Element is \"foo\"", strcmp(dest[0], "foo") == 0, cleanup);
  mu_test("2nd Element is \"bar\"", strcmp(dest[1], "bar") == 0, cleanup);
  cleanup();
  return NULL;
}

char *test_strsplit_ignore_trailing_delimiter(void)
{
  char **dest;
  setup();
  size_t n = strsplit(dest, "foo,bar,", ",");
  mu_test("Extracted two elements", n == 2, cleanup);
  mu_test("1st Element is \"foo\"", strcmp(dest[0], "foo") == 0, cleanup);
  mu_test("2nd Element is \"bar\"", strcmp(dest[1], "bar") == 0, cleanup);
  cleanup();
  return NULL;
}

char *test_strsplit_two_elems_long_delimiter(void)
{
  char **dest;
  setup();
  size_t n = strsplit(dest, "foobazbar", "baz");
  mu_test("Extracted two elements", n == 2, cleanup);
  mu_test("1st Element is \"foo\"", strcmp(dest[0], "foo") == 0, cleanup);
  mu_test("2nd Element is \"bar\"", strcmp(dest[1], "bar") == 0, cleanup);
  cleanup();
  return NULL;
}

char *test_strsplit_no_delimiter(void)
{
  char **dest;
  setup();
  size_t n = strnsplit(dest, "flox", "", SSIZE_MAX, SSIZE_MAX);
  mu_test("Extracted 4 elements", n == 4, cleanup);
  mu_test("1st Element is \"f\"", strcmp(dest[0], "f") == 0, cleanup);
  mu_test("2nd Element is \"l\"", strcmp(dest[1], "l") == 0, cleanup);
  mu_test("3rd Element is \"o\"", strcmp(dest[2], "o") == 0, cleanup);
  mu_test("4th Element is \"x\"", strcmp(dest[3], "x") == 0, cleanup);
  cleanup();
  return NULL;
}

void all_tests(void)
{
  mu_run_test(test_unlimited_strnsplit_single_elem);
  mu_run_test(test_unlimited_strnsplit_two_elems);
  mu_run_test(test_unlimited_strnsplit_ignore_trailing_delimiter);
  mu_run_test(test_unlimited_strnsplit_two_elems_long_delimiter);

  mu_run_test(test_strnsplit_too_many_elems);
  mu_run_test(test_strnsplit_too_long_elems);
  mu_run_test(test_unlimited_strnsplit_no_delimiter);

  // In case strsplit is not just a wrapper around strnsplit.
  mu_run_test(test_strsplit_single_elem);
  mu_run_test(test_strsplit_two_elems);
  mu_run_test(test_strsplit_ignore_trailing_delimiter);
  mu_run_test(test_strsplit_two_elems_long_delimiter);
  mu_run_test(test_strsplit_no_delimiter);
}

int main(int argc, char **argv)
{
  (void) argv;
  if (argc > 1) {
    fprintf(stderr, "Too many arguments supplied\n");
    exit(1);
  }
  printf("%s\n", argv[0]);
  mu_main(all_tests);
}
