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
  cleanup();  // Cleanup of empty list works.
  return NULL;
}

char *test_append_works(void)
{
  struct LinkedList *list = malloc(sizeof(struct LinkedList));
  linked_list_init(list, NULL);
  int value = 69;
  linked_list_insert_after(list, linked_list_head(list), &value);
  mu_test("Head is 69", *(int *)list->head->data == 69, cleanup);
  mu_test("Size is 1", linked_list_size(list) == 1, cleanup);
  mu_test("Tail is head", list->tail == list->head, cleanup);
  int value2 = 70;
  
  // Inserting at tail.
  linked_list_insert_after(list, linked_list_tail(list), &value2);
  mu_test("Head is still 69", *(int *)list->head->data == 69, cleanup);
  mu_test("Size is 2", linked_list_size(list) == 2, cleanup);
  mu_test("Tail 70", *((int *)list->tail->data) == 70, cleanup);

  // Inserting at tail again.
  int value3 = 71;
  linked_list_insert_after(list, linked_list_tail(list), &value3);
  mu_test("Head is still 69", *(int *)list->head->data == 69, cleanup);
  mu_test("Size is 3", linked_list_size(list) == 3, cleanup);
  mu_test("Tail 71", *((int *)list->tail->data) == 71, cleanup);

  // Inserting at head.
  int value4 = 68;
  linked_list_insert_after(list, NULL, &value4);
  mu_test("Head is now 68", *(int *)list->head->data == 68, cleanup);
  mu_test("Size is 4", linked_list_size(list) == 4, cleanup);
  mu_test("Tail 71", *((int *)list->tail->data) == 71, cleanup);

  // Inserting in middle.
  double value5 = 69.5;
  linked_list_insert_after(list, list->head->next, &value5);
  mu_test("Head is still 68", *(int *)list->head->data == 68, cleanup);
  mu_test("New element is at pos", 
          *(double *)list->head->next->next->data == 69.5, 
          cleanup);
  mu_test("Size is 5", linked_list_size(list) == 5, cleanup);
  mu_test("Tail 71", *(int *)list->tail->data == 71, cleanup);
  cleanup();  // Cleanup of filled list works.
  return NULL;
}

char *test_remove_works(void)
{
  int nums[] = {1, 2, 3, 4, 5};
  struct LinkedList *list = malloc(sizeof(struct LinkedList));
  linked_list_init(list, NULL);
  for (size_t i = 0; i < 5; ++i) 
    linked_list_insert_after(list, linked_list_tail(list), &nums[i]);
  int *val;

  linked_list_remove_after(list, NULL, (void **) &val);
  mu_test("Head is 1", *val == 1, cleanup);
  mu_test("New head is 2", *(int *)list->head->data == 2, cleanup);

  linked_list_remove_after(list, 
                           linked_list_next(linked_list_head(list)), 
                           (void **) &val);
  mu_test("After middle is 4", *val == 4, cleanup);

  linked_list_remove_after(list, 
                           linked_list_next(linked_list_head(list)), 
                           (void **) &val);
  mu_test("Tail is 5", *val == 5, cleanup);
  mu_test("New Tail is 3", 
          *(int *)linked_list_data(linked_list_tail(list)) == 3, 
          cleanup);

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
  mu_run_test(test_append_works);
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
