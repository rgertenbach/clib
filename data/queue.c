#include <stdbool.h>
#include <stdlib.h>

#include "list.h"
#include "queue.h"

typedef struct List Stack;

void queue_init(Stack *queue, void (*destroy)(void *data))
{
  list_init(queue, destroy);
}

void queue_destroy(Stack * queue)
{
  list_destroy(queue);
}

unsigned int queue_size(Stack const * const queue)
{
  return list_size(queue);
}

void *queue_peek(Stack *queue)
{
  return list_data(list_head(queue));
}

bool queue_enqueue(Stack *queue, void *data)
{
  return list_insert_after(queue, list_tail(queue), data);
}

bool queue_dequeue(Stack *queue, void **data)
{
  return list_remove_after(queue, NULL, data);
}

