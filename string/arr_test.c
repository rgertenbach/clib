#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../test/minunit.h"
#include "arr.h"

char *test_strfind(void)
{
  char *arr[] = {"Text1", "Text2", "Text3"};
  mu_test(
      "Text1 is at 0", 
      strfind("Text1", (char const * const * const) arr, 3) == 0,
      MU_NO_CLEANUP);
  mu_test(
      "Text2 is at 1", 
      strfind("Text2", (char const * const * const) arr, 3) == 1,
      MU_NO_CLEANUP);
  mu_test(
      "Text3 is at 0", 
      strfind("Text3", (char const * const * const) arr, 3) == 2,
      MU_NO_CLEANUP);
  mu_test(
      "Text4 is at -1", 
      strfind("Text4", (char const * const * const) arr, 3) == -1,
      MU_NO_CLEANUP);
  return NULL;
}

char *test_strin(void)
{
  char *arr[] = {"Text1", "Text2", "Text3"};
  mu_test(
      "Text1 is in", 
      strin("Text1", (char const * const * const) arr, 3),
      MU_NO_CLEANUP);
  mu_test(
      "Text2 is in", 
      strin("Text2", (char const * const * const) arr, 3),
      MU_NO_CLEANUP);
  mu_test(
      "Text3 is in", 
      strin("Text3", (char const * const * const) arr, 3),
      MU_NO_CLEANUP);
  mu_test(
      "Text4 is not in", 
      !strin("Text4", (char const * const * const) arr, 3),
      MU_NO_CLEANUP);
  return NULL;
}

void all_tests(void)
{
  mu_run_test(test_strfind);
  mu_run_test(test_strin);
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
