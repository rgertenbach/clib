#include <stdio.h>

#include "../test/minunit.h"
#include "rxsort.h"

char *
test_sort1(void)
{
  int data[] = {5, 4, 3, 2, 1};
  rxsort(data, 5, 1, 10);
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
  rxsort(data, 5, 1, 10);
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
  rxsort(data, 5, 1, 10);
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
  rxsort(data, 5, 1, 10);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[1], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[2], MU_NO_CLEANUP);
  mu_test_equal("", 4, data[3], MU_NO_CLEANUP);
  mu_test_equal("", 5, data[4], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_similar_digits(void)
{
  int data[] = {33, 22, 11, 32, 21, 13, 31, 23, 12};
  rxsort(data, 9, 2, 10);
  mu_test_equal("", 11, data[0], MU_NO_CLEANUP);
  mu_test_equal("", 12, data[1], MU_NO_CLEANUP);
  mu_test_equal("", 13, data[2], MU_NO_CLEANUP);
  mu_test_equal("", 21, data[3], MU_NO_CLEANUP);
  mu_test_equal("", 22, data[4], MU_NO_CLEANUP);
  mu_test_equal("", 23, data[5], MU_NO_CLEANUP);
  mu_test_equal("", 31, data[6], MU_NO_CLEANUP);
  mu_test_equal("", 32, data[7], MU_NO_CLEANUP);
  mu_test_equal("", 33, data[8], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_small1(void)
{
  int data[] = {2, 1};
  rxsort(data, 2, 2, 5);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[1], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_small2(void)
{
  int data[] = {1, 2};
  rxsort(data, 2, 1, 10);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[1], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_very_small(void)
{
  int data[] = {1};
  rxsort(data, 1, 2, 10);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_empty(void)
{
  int data[] = {};
  rxsort(data, 0, 3, 10);
  return NULL;
}
void
run_tests(void)
{
  mu_run_test(test_sort1);
  mu_run_test(test_sort2);
  mu_run_test(test_sort2);
  mu_run_test(test_sort2);
  mu_run_test(test_sort3);
  mu_run_test(test_sort_duplicates);
  mu_run_test(test_sort_small1);
  mu_run_test(test_sort_small2);
  mu_run_test(test_sort_very_small);
  mu_run_test(test_sort_empty);
  mu_run_test(test_sort_similar_digits);
}

int
main(void)
{
  mu_main(run_tests);
  return 0;
}
