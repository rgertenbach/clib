#ifndef LSTACK_H
#define LSTACK_H

#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

// Treats a list like a stack, requires list.h and list.c

void lstack_init(struct List *stack, void (*destroy)(void *data))
{
  list_init(stack, destroy);
}

void lstack_destroy(struct List *stack)
{
  list_destroy(stack);
}

bool lstack_push(struct List *stack, void *data)
{
  return list_insert_after(stack, NULL, data);
}

bool lstack_pop(struct List *stack, void **data)
{
  return list_remove_after(stack, NULL, data);
}

bool lstack_peek(struct List *stack, void **data)
{
  struct ListElement *top = list_tail(stack);
  if (top == NULL) return false;
  *data = list_data(top);
  return true;
}

size_t lstack_size(struct List *stack)
{
  return stack->size;
}
#endif
