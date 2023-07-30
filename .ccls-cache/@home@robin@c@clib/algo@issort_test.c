#include <stdio.h>

#include "../test/minunit.h"
#include "issort.h"

int
comp(void const * const a, void const * const b)
{
  int const * const x = a;
  int const * const y = b;
  if (*x < *y) return -1;
  if (*x > *y) return 1;
  return 0;
}

char *
test_sort1(void)
{
  int data[] = {5, 4, 3, 2, 1};
  issort(data, 5, sizeof(int), comp);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[1], MU_NO_CLEANUP);
  mu_test_equal("", 3, data[2], MU_NO_CLEANUP);
  mu_test_equal("", 4, data[3], MU_NO_CLEANUP);
  mu_test_equal("", 5, data[4], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort2(void)
{
  int data[] = {3, 5, 1, 4, 2};
  issort(data, 5, sizeof(int), comp);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[1], MU_NO_CLEANUP);
  mu_test_equal("", 3, data[2], MU_NO_CLEANUP);
  mu_test_equal("", 4, data[3], MU_NO_CLEANUP);
  mu_test_equal("", 5, data[4], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort3(void)
{
  int data[] = {1, 2, 3, 4, 5};
  issort(data, 5, sizeof(int), comp);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[1], MU_NO_CLEANUP);
  mu_test_equal("", 3, data[2], MU_NO_CLEANUP);
  mu_test_equal("", 4, data[3], MU_NO_CLEANUP);
  mu_test_equal("", 5, data[4], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_duplicates(void)
{
  int data[] = {1, 2, 2, 4, 5};
  issort(data, 5, sizeof(int), comp);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[1], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[2], MU_NO_CLEANUP);
  mu_test_equal("", 4, data[3], MU_NO_CLEANUP);
  mu_test_equal("", 5, data[4], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_small(void)
{
  int data[] = {2, 1};
  issort(data, 2, sizeof(int), comp);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[1], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_very_small(void)
{
  int data[] = {1};
  issort(data, 1, sizeof(int), comp);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_empty(void)
{
  int data[] = {};
  issort(data, 0, sizeof(int), comp);
  return NULL;
}

void
run_tests(void)
{
  mu_run_test(test_sort1);
  mu_run_test(test_sort2);
  mu_run_test(test_sort3);
  mu_run_test(test_sort_small);
  mu_run_test(test_sort_very_small);
  mu_run_test(test_sort_empty);
}

int
main(void)
{
  mu_main(run_tests);
  return 0;
}
