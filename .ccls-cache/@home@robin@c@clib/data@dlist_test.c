#include <stdlib.h>
#include "dlist.h"
#include "../test/minunit.h"

// Tests accessing the Data structure's internals.
#define cleanup() do { \
  dlist_destroy(list); \
  free(list); \
} while (0)

char *test_init_works(void)
{
  struct Dlist *list = malloc(sizeof(struct Dlist));
  dlist_init(list, NULL);
  mu_test("List should have size 0", dlist_size(list) == 0, cleanup);
  mu_test("List's head should be NULL", dlist_head(list) == NULL, cleanup);
  mu_test("List's tail should be NULL", dlist_tail(list) == NULL, cleanup);
  cleanup();  // Cleanup of empty list works.
  return NULL;
}

char *test_insert_after_works(void)
{
  struct Dlist *list = malloc(sizeof(struct Dlist));
  dlist_init(list, NULL);
  int value = 69;
  dlist_insert_after(list, dlist_head(list), &value);
  mu_test("Head is 69", *(int *)list->head->data == 69, cleanup);
  mu_test("Size is 1", dlist_size(list) == 1, cleanup);
  mu_test("Tail is head", list->tail == list->head, cleanup);
  
  // Inserting at tail.
  int value2 = 70;
  dlist_insert_after(list, dlist_tail(list), &value2);
  mu_test("Head is still 69", *(int *)list->head->data == 69, cleanup);
  mu_test("Size is 2", dlist_size(list) == 2, cleanup);
  mu_test("Tail 70", *((int *)list->tail->data) == 70, cleanup);

  // Inserting at tail again.
  int value3 = 71;
  dlist_insert_after(list, dlist_tail(list), &value3);
  mu_test("Head is still 69", *(int *)list->head->data == 69, cleanup);
  mu_test("Size is 3", dlist_size(list) == 3, cleanup);
  mu_test("Tail 71", *((int *)list->tail->data) == 71, cleanup);

  // Inserting at head.
  int value4 = 68;
  dlist_insert_after(list, NULL, &value4);
  mu_test("Head is now 68", *(int *)list->head->data == 68, cleanup);
  mu_test("Size is 4", dlist_size(list) == 4, cleanup);
  mu_test("Tail 71", *((int *)list->tail->data) == 71, cleanup);

  // Inserting in middle.
  double value5 = 69.5;
  dlist_insert_after(list, list->head->next, &value5);
  mu_test("Head is still 68", *(int *)list->head->data == 68, cleanup);
  mu_test("New element is at pos", 
          *(double *)list->head->next->next->data == 69.5, 
          cleanup);
  mu_test("Size is 5", dlist_size(list) == 5, cleanup);
  mu_test("Tail 71", *(int *)list->tail->data == 71, cleanup);
  cleanup();  // Cleanup of filled list works.
  return NULL;
 
  // Order checks
  mu_test("Head is 68", *(int *)list->head->data == 68, cleanup);
  mu_test("E1 is 69", *(int *)list->head->next->data == 69, cleanup);
  mu_test("E2 is 69.5", *(double *)list->head->next->next->data == 69.5, cleanup);
  mu_test("E3 is 70", *(int *)list->head->next->next->next->data == 70, cleanup);
  mu_test("E4 is 71", *(int *)list->head->next->next->next->next->data == 71, cleanup);
}

char *test_insert_before_works(void)
{
  struct Dlist *list = malloc(sizeof(struct Dlist));
  dlist_init(list, NULL);
  int value = 69;
  dlist_insert_before(list, dlist_head(list), &value);
  mu_test("Head is 69", *(int *)list->head->data == 69, cleanup);
  mu_test("Size is 1", dlist_size(list) == 1, cleanup);
  mu_test("Tail is head", list->tail == list->head, cleanup);
  
  // Inserting at tail.
  int value2 = 70;
  dlist_insert_before(list, NULL, &value2);
  mu_test("Head is still 69", *(int *)list->head->data == 69, cleanup);
  mu_test("Size is 2", dlist_size(list) == 2, cleanup);
  mu_test("Tail 70", *((int *)list->tail->data) == 70, cleanup);

  // Inserting at tail again.
  int value3 = 71;
  dlist_insert_before(list, NULL, &value3);
  mu_test("Head is still 69", *(int *)list->head->data == 69, cleanup);
  mu_test("Size is 3", dlist_size(list) == 3, cleanup);
  mu_test("Tail 71", *((int *)list->tail->data) == 71, cleanup);

  // Inserting at head.
  int value4 = 68;
  dlist_insert_before(list, dlist_head(list), &value4);
  mu_test("Head is now 68", *(int *)list->head->data == 68, cleanup);
  mu_test("Size is 4", dlist_size(list) == 4, cleanup);
  mu_test("Tail 71", *((int *)list->tail->data) == 71, cleanup);

  // Inserting in middle.
  double value5 = 69.5;
  dlist_insert_before(list, list->head->next->next, &value5);
  mu_test("Head is still 68", *(int *)list->head->data == 68, cleanup);
  mu_test("New element is at pos", 
          *(double *)list->head->next->next->data == 69.5, 
          cleanup);
  mu_test("Size is 5", dlist_size(list) == 5, cleanup);
  mu_test("Tail 71", *(int *)list->tail->data == 71, cleanup);
  
  // Order checks
  mu_test("Head is 68", *(int *)list->head->data == 68, cleanup);
  mu_test("E1 is 69", *(int *)list->head->next->data == 69, cleanup);
  mu_test("E2 is 69.5", *(double *)list->head->next->next->data == 69.5, cleanup);
  mu_test("E3 is 70", *(int *)list->head->next->next->next->data == 70, cleanup);
  mu_test("E4 is 71", *(int *)list->head->next->next->next->next->data == 71, cleanup);
  cleanup();  // Cleanup of filled list works.
  return NULL;
}

char *test_remove_works(void)
{
  int nums[] = {1, 2, 3, 4, 5};
  struct Dlist *list = malloc(sizeof(struct Dlist));
  dlist_init(list, NULL);
  for (size_t i = 0; i < 5; ++i) 
    dlist_insert_after(list, dlist_tail(list), &nums[i]);
  int *val;

  dlist_remove(list, dlist_head(list), (void **) &val);
  mu_test("Head is 1", *val == 1, cleanup);
  mu_test("New head is 2", *(int *)list->head->data == 2, cleanup);

  dlist_remove(list, dlist_next(dlist_next(dlist_head(list))), (void **) &val);
  mu_test("After middle is 4", *val == 4, cleanup);

  dlist_remove(list, dlist_next(dlist_next(dlist_head(list))), (void **) &val);
  mu_test("Tail is 5", *val == 5, cleanup);
  mu_test("New Tail is 3", *(int *) dlist_data(dlist_tail(list)) == 3, cleanup);

  cleanup();
  return NULL;
}

char *test_destructor_works(void)
{
  return NULL;
}

void all_tests(void)
{
  mu_run_test(test_init_works);
  mu_run_test(test_insert_after_works);
  mu_run_test(test_insert_before_works);
  mu_run_test(test_remove_works);
  mu_run_test(test_destructor_works);
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
