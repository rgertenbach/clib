// The queue is just a view on a list.

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "list.h"

// Initializes the queue. Must be called before the queue can be used.
//
// The complexity is O(1).
//
// @param queue A pointer to a queue.
// @param destory method to free the value of a queue. For plain pointers this
//   may be free, for more complex data the data type's destructor, for data
//   that should not be freed it should be NULL.
void queue_init(struct List *queue, void (*destroy) (void *data));

// Deallocates a queue and possibly the members.
//
// The complexity is O(n) where n is the number of elements in the queue.
//
// @param list The queue to deallocate.
void queue_destroy(struct List *queue);

// Inserts a new element at the top of the queue.
//
// The complexity is O(1).
//
// @param queue The queue to insert the element into.
// @param data A void pointer to the new data.
// @return Whether the operation was a success or not.
bool queue_enqueue(struct List *queue, void *data);

// Pops the top item of the queue.
//
// The complexity is O(1)
//
// @param queue The queue to remove the element from.
// @param data will point to the element that was removed. Use NULL if the data
//  should not be accessed.
// @return Whether the operation was a success or not.
bool queue_dequeue(struct List *queue, void **data);

// Returns the value of the top item of the queue.
//
// @param queue The queue whose top we want to peek.
// @return A pointer to the top element. NULL if empty.
void *queue_peek(struct List *queue);

// The number of elements in the queue.
//
// The complexity is O(1).
//
// @param queue The queue we want the length of.
// @return The size of the queue.
unsigned int queue_size(struct List const * const queue);

#endif  // STACK_H
