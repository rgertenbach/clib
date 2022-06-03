#include <stdlib.h>
#include "linked_list.h"
#include "minunit.h"


// Tests accessing the Data structure's internals.
#define cleanup() do { \
  linked_list_destroy(list); \
  free(list); \
} while (0)

char *test_init_works(void)
{
  struct LinkedList *list = malloc(sizeof(struct LinkedList));
  linked_list_init(list, NULL);
  mu_test("List should have size 0", linked_list_size(list) == 0, cleanup);
  mu_test("List's head should be NULL", linked_list_head(list) == NULL, cleanup);
  mu_test("List's tail should be NULL", linked_list_tail(list) == NULL, cleanup);
  cleanup();
  return NULL;
}

char *test_append_works(void)
{
  struct LinkedList *list = malloc(sizeof(struct LinkedList));
  linked_list_init(list, NULL);
  int *value = malloc(sizeof(int));
  *value = 69;
  linked_list_insert_after(list, linked_list_head(list), value);
  mu_test("Head is 69", *((int *)(list->head->data)) == 69, cleanup);
  cleanup();
  return NULL;
}

void all_tests(void)
{
  mu_run_test(test_init_works);
  mu_run_test(test_append_works);
}

int main(void)
{
  mu_main(all_tests);
}
