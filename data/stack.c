#include <stdbool.h>
#include <stdlib.h>

#include "list.h"
#include "stack.h"

typedef struct List Stack;

void stack_init(Stack *stack, void (*destroy)(void *data))
{
  list_init(stack, destroy);
}

void stack_destroy(Stack * stack)
{
  list_destroy(stack);
}

unsigned int stack_size(Stack const * const stack)
{
  return list_size(stack);
}

void *stack_peek(Stack *stack)
{
  return list_data(list_head(stack));
}

bool stack_push(Stack *stack, void *data)
{
  return list_insert_after(stack, NULL, data);
}

bool stack_pop(Stack *stack, void **data)
{
  return list_remove_after(stack, NULL, data);
}

