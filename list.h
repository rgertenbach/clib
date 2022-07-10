#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>

struct ListElement {
  void *data;
  struct ListElement *next;
};

struct List {
  unsigned int size;
  void (*destroy)(void *data);
  struct ListElement *head;
  struct ListElement *tail;
};

// Initializes the linked list. Must be called before the list can be used.
//
// The complexity is O(1).
//
// @param list A pointer to a linked list.
// @param destory method to free the value of a list. For plain pointers this
//   may be free, for more complex data the data type's destructor, for data
//   that should not be free it should be NULL.
void list_init(struct List *list, void (*destroy)(void *data));

// Deallocates a linked list and possibly the members.
//
// The complexity is O(n) where n is the number of elements in the list.
//
// @param list The linked list to deallocate.
void list_destroy(struct List *list);

// Inserts a new element just after element
//
// The complexity is O(1).
//
// @param list The list to insert the element into.
// @param element The element to insert after. If NULL then the inserted element
//   will be the new head.
// @param data A void pointer to the new data.
// @return Whether the operation was a success or not.
bool list_insert_after(struct List *list, 
                       struct ListElement *element, 
                       void *data);

// Deletes the element just after element.
//
// The complexity is O(1)
//
// @param list The list to remove the element from.
// @param element The element preceding the element to be deleted.
// @param data will point to the element that was removed. Use NULL if the data
//  should not be accessed.
// @return Whether the operation was a success or not.
bool list_remove_after(struct List *list,
                       struct ListElement *element,
                       void **data);

// The number of elements in the list.
//
// The complexity is O(1).
//
// @param list The list we want the length of.
// @return THe size of the list.
unsigned int list_size(const struct List *list);

// Returns the head of the linked list.
//
// Complexity: O(1)
//
// @param list The linked list we want the head of.
// @return A pointer to the element containing the value at the head.
struct ListElement *list_head(struct List *list);


// Returns the tail of the linked list.
//
// Complexity: O(1)
//
// @param list The linked list we want the tail of.
// @return A pointer to the element containing the value at the tail.
struct ListElement *list_tail(struct List *list);

// Whether the element is at the head of a linked list.
//
// Complexity: O(1)
// 
// @param list: The list to check for head-ness.
// @param element: The Element to check.
// @return Whether the element is at the head of its linked list.
bool list_is_head(struct List *list, 
                  struct ListElement *element);

// Whether the element is at the tail of a linked list.
//
// Complexity: O(1)
// 
// @param element: The ELement to check.
// @return WHether the element is at the tail of its linked list.
bool list_is_tail(struct ListElement *element);

// Extracts the value contained by a Linked List element.
//
// COmplexity: O(1)
//
// @param element: The element to extract the value from.
// @return A void pointer to the value.
void *list_data(struct ListElement *element);

// The next element of a linked list after the element.
//
// Complexity: O(1)
//
// @param element The element of which we want the successor.
// @return A pointer to the element following it.
struct ListElement *list_next(struct ListElement *element);

#endif
