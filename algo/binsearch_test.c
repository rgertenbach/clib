#include <stdio.h>

#include "../test/minunit.h"
#include "binsearch.h"


#include <stdio.h>
int
comp(void const * const a, void const * const b)
{
  return *(int *)a - *(int *)b;
}

char *
test_empty(void)
{
  int data[] = {};
  int one = 1;
  mu_test_equal("", NULL, binsearch(data, 0, sizeof(int), &one, comp), MU_NO_CLEANUP);
  return NULL;
}

char *
test_one_element(void)
{
  int data[] = {1};
  int one = 1;
  int two = 20;
  mu_test_equal("", data, binsearch(data, 1, sizeof(int), &one, comp), MU_NO_CLEANUP);
  mu_test_equal("", NULL, binsearch(data, 1, sizeof(int), &two, comp), MU_NO_CLEANUP);
  return NULL;
}

char *
test_two_elements(void)
{
  int data[] = {1, 20};
  int one = 1;
  int two = 20;
  int three = 300;
  mu_test_equal("", data, binsearch(data, 2, sizeof(int), &one, comp), MU_NO_CLEANUP);
  mu_test_equal("", data + 1, binsearch(data, 2, sizeof(int), &two, comp), MU_NO_CLEANUP);
  mu_test_equal("", NULL, binsearch(data, 2, sizeof(int), &three, comp), MU_NO_CLEANUP);
  return NULL;
}

char *
test_three_elements(void)
{
  int data[] = {1, 20, 300};
  int one = 1;
  int two = 20;
  int three = 300;
  mu_test_equal("", data, binsearch(data, 3, sizeof(int), &one, comp), MU_NO_CLEANUP);
  mu_test_equal("", data + 1, binsearch(data, 3, sizeof(int), &two, comp), MU_NO_CLEANUP);
  mu_test_equal("", data + 2, binsearch(data, 3, sizeof(int), &three, comp), MU_NO_CLEANUP);
  return NULL;
}

char *
test_many_elements(void)
{
  int data[] = {1, 20, 300, 4000, 50000};
  int zero = 0;
  int one = 1;
  int two = 20;
  int twop5 = 25;
  int three = 300;
  int four = 4000;
  int five = 50000;
  int six = 600000;
  mu_test_equal("", NULL, binsearch(data, 5, sizeof(int), &zero, comp), MU_NO_CLEANUP);
  mu_test_equal("", data, binsearch(data, 5, sizeof(int), &one, comp), MU_NO_CLEANUP);
  mu_test_equal("", data + 1, binsearch(data, 5, sizeof(int), &two, comp), MU_NO_CLEANUP);
  mu_test_equal("", NULL, binsearch(data, 5, sizeof(int), &twop5, comp), MU_NO_CLEANUP);
  mu_test_equal("", data + 2, binsearch(data, 5, sizeof(int), &three, comp), MU_NO_CLEANUP);
  mu_test_equal("", data + 3, binsearch(data, 5, sizeof(int), &four, comp), MU_NO_CLEANUP);
  mu_test_equal("", data + 4, binsearch(data, 5, sizeof(int), &five, comp), MU_NO_CLEANUP);
  mu_test_equal("", NULL, binsearch(data, 5, sizeof(int), &six, comp), MU_NO_CLEANUP);
  return NULL;
}

void
run_tests(void)
{
  mu_run_test(test_empty);
  mu_run_test(test_one_element);
  mu_run_test(test_two_elements);
  mu_run_test(test_three_elements);
  mu_run_test(test_many_elements);
}

int
main(void)
{
  mu_main(run_tests);
  return 0;
}
