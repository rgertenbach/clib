#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdlib.h>

struct LinkedListElement {
  void *data;
  struct LinkedListElement *next;
};

struct LinkedList {
  unsigned int size;
  // ???
  int (*match)(const void *key1, const void *key2);

  void (*destroy)(void *data);
  struct LinkedListElement *head;
  struct LinkedListElement *tail;
};

// Initializes the linked list. Must be called before the list can be used.
//
// The complexity is O(1).
//
// @param list A pointer to a linked list.
// @param destory method to free the value of a list. For plain pointers this
//   may be free, for more complex data the data type's destructor, for data
//   that should not be free it should be NULL.
void linked_list_init(struct LinkedList *list, void (*destroy)(void *data));

// Deallocates a linked list and possibly the members.
//
// The complexity is O(n) where n is the number of elements in the list.
//
// @param list The linked list to deallocate.
void linked_list_destroy(struct LinkedList *list);

// Inserts a new element just after element
//
// The complexity is O(1).
//
// @param list The list to insert the element into.
// @param element The element to insert after. If NULL then the inserted element
//   will be the new head.
// @param data A void pointer to the new data.
// @return Whether the operation was a success or not.
bool linked_list_insert_after(struct LinkedList *list, 
                              struct LinkedListElement *element, 
                              void *data);

// Deletes the element just afte element.
//
// The complexity is O(1)
//
// @param list The list to remove the element from.
// @param element The element preceding the element to be deleted.
// @param data will point to the element that was removed. Use NULL if the data
//  should not be accessed.
// @return Whether the operation was a success or not.
bool linked_list_remove_after(struct LinkedList *list,
                              struct LinkedListElement *element,
                              void **data);

// The number of elements in the list.
//
// The complexity is O(1).
//
// @param list The list we want the length of.
// @return THe size of the list.
unsigned int linked_list_size(const struct LinkedList *list);

// Returns the head of the linked list.
//
// Complexity: O(1)
//
// @param list The linked list we want the head of.
// @return A pointer to the element containing the value at the head.
struct LinkedListElement *linked_list_head(struct LinkedList *list);


// Returns the tail of the linked list.
//
// Complexity: O(1)
//
// @param list The linked list we want the tail of.
// @return A pointer to the element containing the value at the tail.
struct LinkedListElement *linked_list_tail(struct LinkedList *list);

// Whether the element is at the head of a linked list.
//
// Complexity: O(1)
// 
// @param list: The list to check for head-ness.
// @param element: The Element to check.
// @return Whether the element is at the head of its linked list.
bool linked_list_is_head(struct LinkedList *list, 
                         struct LinkedListElement *element);

// Whether the element is at the tail of a linked list.
//
// Complexity: O(1)
// 
// @param element: The ELement to check.
// @return WHether the element is at the tail of its linked list.
bool linked_list_is_tail(struct LinkedListElement *element);

// Extracts the value contained by a Linked List element.
//
// COmplexity: O(1)
//
// @param element: The element to extract the value from.
// @return A void pointer to the value.
void *linked_list_data(struct LinkedListElement *element);

// The next element of a linked list after the element.
//
// Complexity: O(1)
//
// @param element The element of which we want the successor.
// @return A pointer to the element following it.
struct LinkedListElement *linked_list_next(struct LinkedListElement *element);

#endif
