#ifndef CLIST_H
#define CLIST_H

#include <stdbool.h>

struct CListElement {
  void *data;
  struct CListElement *next;
};

struct CList {
  unsigned int size;
  void (*destroy)(void *data);
  struct CListElement *curr;
};

// Initializes the circular linked list.
//
// Must be called before the list can be used.
// The complexity is O(1).
//
// @param list A pointer to a linked list.
// @param destory method to free the value of a list. For plain pointers this
//   may be free, for more complex data the data type's destructor, for data
//   that should not be free it should be NULL.
void clist_init(struct CList *list, void (*destroy)(void *data));

// Deallocates a linked list and possibly the members.
//
// The complexity is O(n) where n is the number of elements in the list.
//
// @param list The linked list to deallocate.
void clist_destroy(struct CList *list);

// Returns the current element of the circular list.
//
// The complexity is O(1).
//
// @param list The list from which to get the current element.
// @return The current element of the list.
struct CListElement *clist_current(struct CList *list);

// Whether element is the current element of the circular list.
//
// The complexity is O(1).
//
// @param list The list against which to check.
// @param element The element to check for currency.
// @return Wheter element is the current element of list.
bool clist_is_current(struct CList *list, struct CListElement *element);

// Inserts a new element just after element
//
// The complexity is O(1).
//
// @param list The list to insert the element into.
// @param element The element to insert after. May only be NULL if the list is
//   empty.
// @param data A void pointer to the new data.
// @return Whether the operation was a success or not.
bool clist_insert_after(struct CList *list, 
                        struct CListElement *element, 
                        void *data);

// Deletes the element just after element.
//
// If the removed element is the current element of the circular list then after
// becomes the new current element.
// The complexity is O(1)
//
// @param list The list to remove the element from.
// @param element The element preceding the element to be deleted.
// @param data will point to the element that was removed. Use NULL if the data
//  should not be accessed.
// @return Whether the operation was a success or not.
bool clist_remove_after(struct CList *list,
                        struct CListElement *element,
                        void **data);

// The number of elements in the list.
//
// The complexity is O(1).
//
// @param list The list we want the length of.
// @return THe size of the list.
unsigned int clist_size(const struct CList *list);

// Extracts the value contained by a Linked List element.
//
// COmplexity: O(1)
//
// @param element: The element to extract the value from.
// @return A void pointer to the value.
void *clist_data(struct CListElement *element);

// The next element of a linked list after the element.
//
// Complexity: O(1)
//
// @param element The element of which we want the successor.
// @return A pointer to the element following it.
struct CListElement *clist_next(struct CListElement *element);

#endif
