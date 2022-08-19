#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minunit.h"

bool pass;

char *test1(void)
{
  mu_test("One must equal itself", 1 == 1, MU_NO_CLEANUP);
  return NULL;
}

char *test2(void)
{
  int expected = 2;
  int actual = pass ? 2 : 1;
  mu_test("2 must equal itself", expected == actual, MU_NO_CLEANUP);
  return NULL;
}

void all_tests(void)
{
  mu_run_test(test1);
  mu_run_test(test2);
}

int main(int argc, char **argv)
{
  if (argc > 2) {
    fprintf(stderr, 
            "Too many arguments passed, pass nothing or \"pass\" / \"fail\"\n");
    abort();
  } 
  if (argc == 1) pass = true;
  else if (strcmp(argv[1], "pass") == 0) pass = true;
  else if (strcmp(argv[1], "fail") == 0) pass = false;
  else {
    fprintf(stderr, "Pass nothing or \"pass\" / \"fail\"\n");
    abort();
  }

  mu_main(all_tests);
}
