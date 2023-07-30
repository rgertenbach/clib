#include <stdbool.h>
#include <stdlib.h>
#include "clist.h"
#include "../test/minunit.h"


// Tests accessing the Data structure's internals.
#define cleanup() do { \
  clist_destroy(list); \
  free(list); \
} while (0)

bool clist_equals(struct CList * list,
                  int const * const expected,
                  size_t const n)
{
  struct CListElement *head = clist_current(list);
  struct CListElement *current = clist_current(list);
  if (clist_size(list) != n) return false;
  for (size_t i = 0; i < n; ++i) {
    if (*(int *)clist_data(current) != expected[i]) return false;
    if (i && current == head) return false;
    current = current->next;
  }
  return current == head;
}

char *test_init_works(void)
{
  struct CList *list = malloc(sizeof(struct CList));
  clist_init(list, NULL);
  mu_test("List is []", clist_equals(list, NULL, 0), cleanup);
  cleanup();  // Cleanup of empty list works.
  return NULL;
}

char *test_append_works(void)
{
  int expected[10] = {69, 70, 71, 68};
  struct CList *list = malloc(sizeof(struct CList));
  clist_init(list, NULL);
  int value = 69;
  clist_insert_after(list, clist_current(list), &value);
  mu_test("List is [69]", clist_equals(list, expected, 1), cleanup);
  
  // Inserting at current.
  int value2 = 70;
  clist_insert_after(list, clist_current(list), &value2);
  mu_test("List is [69,70]", clist_equals(list, expected, 2), cleanup);

  // Inserting at tail.
  int value3 = 71;
  clist_insert_after(list, clist_current(list)->next, &value3);
  mu_test("List is [69,70,71]", clist_equals(list, expected, 3), cleanup);

  // // Inserting at tail.
  int value4 = 68;
  clist_insert_after(list, list->curr->next->next, &value4);
  mu_test("List is [69,70,71,68]", clist_equals(list, expected, 4), cleanup);

  cleanup();  // Cleanup of filled list works.
  return NULL;
}

char *test_remove_works(void)
{
  int nums[] = {1, 5, 4, 3, 2};
  int expected[] = {1, 2, 3, 4, 5};
  int *val = NULL;
  struct CList *list = malloc(sizeof(struct CList));
  clist_init(list, NULL);

  mu_test("Remove from empty fails", !clist_remove_after(list, NULL, (void **)(&val)), cleanup);

  for (size_t i = 0; i < 5; ++i) 
    clist_insert_after(list, clist_current(list), (void *) &nums[i]);

  mu_test("List is [1,2,3,4,5]", clist_equals(list, expected, 5), cleanup);

  clist_remove_after(list, clist_current(list)->next->next->next, (void **)(&val));
  mu_test("val is 1", *val == 5, cleanup);
  mu_test("list is [1,2,3,4,5]", clist_equals(list, expected, 4), cleanup);

  cleanup();
  return NULL;
}

void all_tests(void)
{
  mu_run_test(test_init_works);
  mu_run_test(test_append_works);
  mu_run_test(test_remove_works);
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
