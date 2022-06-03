#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
#include "minunit.h"


// Tests accessing the Data structure's internals.

void test_init_works(void)
{
  struct LinkedList *list = malloc(sizeof(struct LinkedList));
  linked_list_init(list, NULL);
  mu_test("List should have size 0", linked_list_size(list) == 0);
  mu_test("List's head should be NULL", linked_list_head(list) == NULL);
  mu_test("List's tail should be NULL", linked_list_tail(list) == NULL);
  linked_list_destroy(list);
  free(list);
}

void test_append_works(void)
{
  struct LinkedList *list = malloc(sizeof(struct LinkedList));
  linked_list_init(list, NULL);
  int *value = malloc(sizeof(int));
  *value = 69;
  linked_list_insert_after(list, linked_list_head(list), value);
  mu_test("Head is 69", *((int *)(list->head->value)) == 69);
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
