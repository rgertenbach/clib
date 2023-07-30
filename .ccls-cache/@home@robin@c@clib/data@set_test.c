#include <stdbool.h>
#include <stdlib.h>
#include "set.h"
#include "../test/minunit.h"

#define cleanup() do { \
  set_destroy(&set); \
} while (0)


bool
match(void const * const a, void const * const b)
{
  return *(int *)a == *(int *)b;
}

char *
test_init_works(void)
{
  struct Set set;
  set_init(&set, match, NULL);
  mu_test_equal("Set should be empty", set_size(&set), 0, cleanup);
  cleanup();
  return NULL;
}

char *
test_match_works(void)
{
  int a = 4, b = 4, c = 5;
  mu_test("a should equal b", match(&a, &b), MU_NO_CLEANUP);
  mu_test("a should not equal c", !match(&a, &c), MU_NO_CLEANUP);
  return NULL;
}

char *
test_operations_work(void)
{
  struct Set set;
  set_init(&set, match, NULL);
  int value = 4;
  int * value_ref = &value;
  int other_value = 5;
  mu_test("Set should not contain anything", !set_is_member(&set, &value), cleanup);
  mu_test("Insertion works", set_insert(&set, (void *) &value), cleanup);
  mu_test("Set should contain 4", set_is_member(&set, &value), cleanup);
  mu_test("Set should not contain 5", !set_is_member(&set, &other_value), cleanup);
  mu_test("Removal works", set_remove(&set, (void *) &value_ref), cleanup);
  mu_test("Set should not contain 4 anymore", !set_is_member(&set, &value), cleanup);
  cleanup();
  return NULL;
}

#undef cleanup
#define cleanup() do { \
  set_destroy(&set1); \
  set_destroy(&set2); \
  set_destroy(&set3); \
} while (0)

char *
test_union_works(void)
{
  struct Set set1, set2, set3;
  set_init(&set1, match, NULL);
  set_init(&set2, match, NULL);
  set_init(&set3, match, NULL);
  int nums[] = {1, 2, 3, 4, 5};

  set_insert(&set1, nums + 0);
  set_insert(&set1, nums + 1);
  set_insert(&set1, nums + 2);
  set_insert(&set2, nums + 3);
  set_insert(&set2, nums + 4);

  mu_test("Union runs", set_union(&set3, &set1, &set2), cleanup);
  mu_test("Union contains 1", set_is_member(&set3, nums + 0), cleanup);
  mu_test("Union contains 2", set_is_member(&set3, nums + 1), cleanup);
  mu_test("Union contains 3", set_is_member(&set3, nums + 2), cleanup);
  mu_test("Union contains 4", set_is_member(&set3, nums + 3), cleanup);
  mu_test("Union contains 5", set_is_member(&set3, nums + 4), cleanup);

  cleanup();
  return NULL;
}

char *
test_intersection_works(void)
{
  struct Set set1, set2, set3;
  set_init(&set1, match, NULL);
  set_init(&set2, match, NULL);
  set_init(&set3, match, NULL);
  int nums[] = {1, 2, 3, 4, 5};

  set_insert(&set1, nums + 0);
  set_insert(&set1, nums + 1);
  set_insert(&set1, nums + 2);
  set_insert(&set1, nums + 3);
  set_insert(&set1, nums + 4);
  set_insert(&set2, nums + 0);
  set_insert(&set2, nums + 2);
  set_insert(&set2, nums + 4);

  mu_test("intersection runs", set_intersection(&set3, &set1, &set2), cleanup);
  mu_test("inters contains 1", set_is_member(&set3, nums + 0), cleanup);
  mu_test("inters does not contain 2", !set_is_member(&set3, nums + 1), cleanup);
  mu_test("inters contains 3", set_is_member(&set3, nums + 2), cleanup);
  mu_test("inters does not contain 4", !set_is_member(&set3, nums + 3), cleanup);
  mu_test("inters contains 5", set_is_member(&set3, nums + 4), cleanup);

  cleanup();
  return NULL;
}

char *
test_difference_works(void)
{
  struct Set set1, set2, set3;
  set_init(&set1, match, NULL);
  set_init(&set2, match, NULL);
  set_init(&set3, match, NULL);
  int nums[] = {1, 2, 3, 4, 5};

  set_insert(&set1, nums + 0);
  set_insert(&set1, nums + 1);
  set_insert(&set1, nums + 2);
  set_insert(&set1, nums + 3);
  set_insert(&set1, nums + 4);
  set_insert(&set2, nums + 1);
  set_insert(&set2, nums + 3);

  mu_test("difference runs", set_difference(&set3, &set1, &set2), cleanup);
  mu_test("diff contains 1", set_is_member(&set3, nums + 0), cleanup);
  mu_test("diff does not contain 2", !set_is_member(&set3, nums + 1), cleanup);
  mu_test("diff contains 3", set_is_member(&set3, nums + 2), cleanup);
  mu_test("diff does not contain 4", !set_is_member(&set3, nums + 3), cleanup);
  mu_test("diff contains 5", set_is_member(&set3, nums + 4), cleanup);

  cleanup();
  return NULL;
}

void all_tests(void)
{
  mu_run_test(test_init_works);
  mu_run_test(test_match_works);
  mu_run_test(test_operations_work);
  mu_run_test(test_union_works);
  mu_run_test(test_intersection_works);
  mu_run_test(test_difference_works);
}

int main(int argc, char **argv)
{
  if (argc > 1) {
    fprintf(stderr, "Too many arguments supplied\n");
    exit(1);
  }
  printf("%s\n", argv[0]);
  mu_main(all_tests);
}
