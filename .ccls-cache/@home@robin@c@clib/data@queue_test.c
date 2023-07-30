#include <stdlib.h>
#include "list.h"
#include "queue.h"
#include "../test/minunit.h"

typedef struct List Stack;

// Tests accessing the Data structure's internals.
#define cleanup() do { \
  queue_destroy(queue); \
  free(queue); \
} while (0)

char *test_init_works(void)
{
  Stack *queue = malloc(sizeof(Stack));
  queue_init(queue, NULL);
  mu_test("List should have size 0", queue_size(queue) == 0, cleanup);
  mu_test("List's head should be NULL", list_head(queue) == NULL, cleanup);
  mu_test("List's tail should be NULL", list_tail(queue) == NULL, cleanup);
  cleanup();  // Cleanup of empty list works.
  return NULL;
}

char *test_enqueue_dequeue_works(void)
{
  struct List *queue = malloc(sizeof(struct List));
  queue_init(queue, NULL);
  int value = 69;
  queue_enqueue(queue, &value);
  mu_test("Head is 69", *(int *)queue->head->data == 69, cleanup);
  mu_test("Size is 1", queue_size(queue) == 1, cleanup);
  mu_test("Tail is head", queue->tail == queue->head, cleanup);
  mu_test("Peek returns 69", *(int *) queue_peek(queue) == 69, cleanup);
  
  // Inserting at tail.
  int value2 = 70;
  queue_enqueue(queue, &value2);
  mu_test("Head is still 60", *(int *)queue->head->data == 69, cleanup);
  mu_test("Size is 2", queue_size(queue) == 2, cleanup);
  mu_test("Tail is now 70", *((int *)queue->tail->data) == 70, cleanup);
  mu_test("Peek returns 69", *(int *) queue_peek(queue) == 69, cleanup);

  // Pop top
  int *pop1 = 0, *pop2 = 0;
  mu_test("Queue is now size 2", queue_size(queue) == 2, cleanup);

  queue_dequeue(queue, (void *) &pop1);
  mu_test("First qeuue is 69", *pop1 == 69, cleanup);
  mu_test("Queue is now size 1", queue_size(queue) == 1, cleanup);

  queue_dequeue(queue, (void *) &pop2);
  mu_test("Second dequeue is 70", *pop2 == 70, cleanup);
  mu_test("Queue is now empty", queue_size(queue) == 0, cleanup);

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
  mu_run_test(test_enqueue_dequeue_works);
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
