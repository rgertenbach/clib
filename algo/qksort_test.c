#include <stdio.h>

#include "../test/minunit.h"
#include "qksort.h"

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
test_median3(void)
{
  int one = 1;
  int two = 2;
  int three = 3;
  mu_test_equal("123", &two, (int *) median3(&one, &two, &three, comp), MU_NO_CLEANUP);
  mu_test_equal("321", &two, (int *) median3(&three, &two, &one, comp), MU_NO_CLEANUP);
  mu_test_equal("213", &two, (int *) median3(&two, &one, &three, comp), MU_NO_CLEANUP);
  mu_test_equal("231", &two, (int *) median3(&two, &three, &one, comp), MU_NO_CLEANUP);
  mu_test_equal("132", &two, (int *) median3(&one, &three, &two, comp), MU_NO_CLEANUP);
  mu_test_equal("312", &two, (int *) median3(&three, &one, &two, comp), MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort1(void)
{
  int data[] = {5, 4, 3, 2, 1};
  qksort(data, 5, sizeof(int), comp);
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
  qksort(data, 5, sizeof(int), comp);
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
  qksort(data, 5, sizeof(int), comp);
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
  qksort(data, 5, sizeof(int), comp);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[1], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[2], MU_NO_CLEANUP);
  mu_test_equal("", 4, data[3], MU_NO_CLEANUP);
  mu_test_equal("", 5, data[4], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_small1(void)
{
  int data[] = {2, 1};
  qksort(data, 2, sizeof(int), comp);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[1], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_small2(void)
{
  int data[] = {1, 2};
  qksort(data, 2, sizeof(int), comp);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  mu_test_equal("", 2, data[1], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_very_small(void)
{
  int data[] = {1};
  qksort(data, 1, sizeof(int), comp);
  mu_test_equal("", 1, data[0], MU_NO_CLEANUP);
  return NULL;
}

char *
test_sort_empty(void)
{
  int data[] = {};
  qksort(data, 0, sizeof(int), comp);
  return NULL;
}
void
run_tests(void)
{
  mu_run_test(test_median3);
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
}

int
main(void)
{
  mu_main(run_tests);
  return 0;
}
