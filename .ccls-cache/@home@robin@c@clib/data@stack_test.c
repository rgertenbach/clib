#include <stdlib.h>
#include "list.h"
#include "stack.h"
#include "../test/minunit.h"

typedef struct List Stack;

// Tests accessing the Data structure's internals.
#define cleanup() do { \
  stack_destroy(stack); \
  free(stack); \
} while (0)

char *test_init_works(void)
{
  Stack *stack = malloc(sizeof(Stack));
  stack_init(stack, NULL);
  mu_test("List should have size 0", stack_size(stack) == 0, cleanup);
  mu_test("List's head should be NULL", list_head(stack) == NULL, cleanup);
  mu_test("List's tail should be NULL", list_tail(stack) == NULL, cleanup);
  cleanup();  // Cleanup of empty list works.
  return NULL;
}

char *test_push_pop_works(void)
{
  struct List *stack = malloc(sizeof(struct List));
  stack_init(stack, NULL);
  int value = 69;
  stack_push(stack, &value);
  mu_test("Head is 69", *(int *)stack->head->data == 69, cleanup);
  mu_test("Size is 1", stack_size(stack) == 1, cleanup);
  mu_test("Tail is head", stack->tail == stack->head, cleanup);
  mu_test("Peek returns 69", *(int *) stack_peek(stack) == 69, cleanup);
  
  // Inserting at tail.
  int value2 = 70;
  stack_push(stack, &value2);
  mu_test("Head is now 70", *(int *)stack->head->data == 70, cleanup);
  mu_test("Size is 2", stack_size(stack) == 2, cleanup);
  mu_test("Tail is 69", *((int *)stack->tail->data) == 69, cleanup);
  mu_test("Peek returns 70", *(int *) stack_peek(stack) == 70, cleanup);

  // Pop top
  int *pop1 = 0, *pop2 = 0;
  mu_test("Stack is now size 2", stack_size(stack) == 2, cleanup);

  stack_pop(stack, (void *) &pop1);
  mu_test("First pop is 70", *pop1 == 70, cleanup);
  mu_test("Stack is now size 1", stack_size(stack) == 1, cleanup);

  stack_pop(stack, (void *) &pop2);
  mu_test("Second pop is 69", *pop2 == 69, cleanup);
  mu_test("Stack is now empty", stack_size(stack) == 0, cleanup);

  cleanup();  // Cleanup of filled list works.
  return NULL;
}

char *test_destructor_works(void)
{
  return NULL;
}

void all_tests(void)
{
  mu_run_test(test_init_works);
  mu_run_test(test_push_pop_works);
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
