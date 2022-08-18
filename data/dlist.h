#ifndef DLIST_H
#define DLIST_H

#include <stdbool.h>

struct DlistElement {
  void *data;
  struct DlistElement *prev;
  struct DlistElement *next;
};

struct Dlist {
  unsigned int size;
  void (*destroy)(void *data);
  struct DlistElement *head;
  struct DlistElement *tail;
};

// Initializes the doubly linked list. 
//
// Must be called before the list can be used
//
// The complexity is O(1).
//
// @param list A pointer to a doubly linked list.
// @param destory method to free the value of a list. For plain pointers this
//   may be free, for more complex data the data type's destructor, for data
//   that should not be free it should be NULL.
void dlist_init(struct Dlist *list, void (*destoy)(void *data));

// Deallocates a doubly linked list and possibly the members.
//
// The complexity is O(n) where n is the number of elements in the list.
//
// @param list The doubly linked list to deallocate.
void dlist_destroy(struct Dlist *list);

// Inserts a new element just after element
//
// The complexity is O(1).
//
// @param list The doubly linked list to insert the element into.
// @param element The element to insert after. If NULL then the inserted element
//   will be the new head.
// @param data A void pointer to the new data.
// @return Whether the operation was a success or not.
bool dlist_insert_after(struct Dlist *list,
                        struct DlistElement *element,
                        void *data);

// Inserts a new element just before element
//
// The complexity is O(1).
//
// @param list The doubly linked list to insert the element into.
// @param element The element to insert before. If NULL then the inserted element
//   will be the new tail.
// @param data A void pointer to the new data.
// @return Whether the operation was a success or not.
bool dlist_insert_before(struct Dlist *list,
                         struct DlistElement *element,
                         void *data);

// Deletes the element.
//
// The complexity is O(1)
//
// @param list The doubly linked list to remove the element from.
// @param element The element to be deleted.
// @param data will point to the element that was removed. Use NULL if the data
//  should not be accessed.
// @return Whether the operation was a success or not.
bool dlist_remove(struct Dlist *list,
                  struct DlistElement *element,
                  void **data);

// The number of elements in the doubly linked list.
//
// The complexity is O(1).
//
// @param list The doubly linked list we want the length of.
// @return The size of the list.
unsigned int dlist_size(const struct Dlist *list);

// Returns the head of the linked doubly linked list.
//
// Complexity: O(1)
//
// @param list The doubly linked list we want the head of.
// @return A pointer to the element containing the value at the head.
struct DlistElement *dlist_head(struct Dlist *list);


// Returns the tail of the doubly linked list.
//
// Complexity: O(1)
//
// @param list The doubly linked list we want the tail of.
// @return A pointer to the element containing the value at the tail.
struct DlistElement *dlist_tail(struct Dlist *list);

// Whether the element is at the head of a doubly linked list.
//
// Complexity: O(1)
// 
// @param element: The Element to check.
// @return Whether the element is at the head of its doubly linked list.
bool dlist_is_head(struct DlistElement *element);

// Whether the element is at the tail of a doubly linked list.
//
// Complexity: O(1)
// 
// @param element: The ELement to check.
// @return Whether the element is at the tail of its doubly linked list.
bool dlist_is_tail(struct DlistElement *element);

// Extracts the value contained by a doubly linked List element.
//
// COmplexity: O(1)
//
// @param element: The element to extract the value from.
// @return A void pointer to the value.
void *dlist_data(struct DlistElement *element);

// The next element of a doubly linked list after the element.
//
// Complexity: O(1)
//
// @param element The element of which we want the successor.
// @return A pointer to the element following it.
struct DlistElement *dlist_next(struct DlistElement *element);

// The previous element of a doubly linked list before the element.
//
// Complexity: O(1)
//
// @param element The element of which we want the successor.
// @return A pointer to the element following it.
struct DlistElement *dlist_prev(struct DlistElement *element);

#endif
