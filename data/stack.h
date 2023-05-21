// The stack is just a view on a list.

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "list.h"

// Initializes the stack. Must be called before the stack can be used.
//
// The complexity is O(1).
//
// @param stack A pointer to a stack.
// @param destory method to free the value of a stack. For plain pointers this
//   may be free, for more complex data the data type's destructor, for data
//   that should not be freed it should be NULL.
void stack_init(struct List *stack, void (*destroy) (void *data));

// Deallocates a stack and possibly the members.
//
// The complexity is O(n) where n is the number of elements in the stack.
//
// @param list The stack to deallocate.
void stack_destroy(struct List *stack);

// Inserts a new element at the top of the stack.
//
// The complexity is O(1).
//
// @param stack The stack to insert the element into.
// @param data A void pointer to the new data.
// @return Whether the operation was a success or not.
bool stack_push(struct List *stack, void *data);

// Pops the top item of the stack.
//
// The complexity is O(1)
//
// @param stack The stack to remove the element from.
// @param data will point to the element that was removed. Use NULL if the data
//  should not be accessed.
// @return Whether the operation was a success or not.
bool stack_pop(struct List *stack, void **data);

// Returns the value of the top item of the stack.
//
// @param stack The stack whose top we want to peek.
// @return A pointer to the top element. NULL if empty.
void *stack_peek(struct List *stack);

// The number of elements in the stack.
//
// The complexity is O(1).
//
// @param stack The stack we want the length of.
// @return The size of the stack.
unsigned int stack_size(struct List const * const stack);

#endif  // STACK_H
