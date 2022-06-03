#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linked_list.h"

void linked_list_init(struct LinkedList *list, void (*destroy)(void *data))
{
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;
}

void linked_list_destroy(struct LinkedList *list)
{
  if (list == NULL) return;
  void *data = NULL;

  while (linked_list_size(list) > 0) {
    if (linked_list_remove_after(list, NULL, &data) && list->destroy != NULL) 
      list->destroy(data);
  }
  memset(list, 0, sizeof(*list));
}

unsigned int linked_list_size(struct LinkedList const * const list)
{
  return list->size;
}

struct LinkedListElement *linked_list_head(struct LinkedList *list)
{
  return list->head;
}

struct LinkedListElement *linked_list_tail(struct LinkedList *list)
{
  return list->tail;
}

bool linked_list_insert_after(struct LinkedList *list, 
                              struct LinkedListElement *after,
                              void *data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL");
    return false;
  }
  struct LinkedListElement *new = malloc(sizeof(struct LinkedListElement));
  if (new == NULL) {
    fprintf(stderr, "No space to allocate new element");
    return false;
  }
  new->data = data;
  if (after == NULL) {
    new->next = list->head;
    list->head=new;
  } else {
    new->next = after->next;
    after->next = new;
  }
  if (after == list->tail) list->tail = new;
  list->size++;
  return true;
}

bool linked_list_remove_after(struct LinkedList *list,
                              struct LinkedListElement *after,
                              void **data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL\n");
    return false;
  }
  struct LinkedListElement *target;
  if (after == NULL) {  // Remove head.
    target = list->head;
    if (target != NULL) list->head = target->next;
  } else {  // Remove non-head.
    if (after->next == NULL) {
      fprintf(stderr, "No element after\n");
      return false;
    }
    target = after->next;
    if (target != NULL) after->next = target->next;
  }
  if (target == list->tail) list->tail = after;
  *data = target->data;
  free(target);
  list->size--;
  return true;
}

bool linked_list_is_tail(struct LinkedListElement *element)
{
  return element->next == NULL;
}
                      
bool linked_list_is_head(struct LinkedList *list,
                         struct LinkedListElement *element)
{
  return element == list->head;
}

void *linked_list_data(struct LinkedListElement *element)
{
  return element->data;
}

struct LinkedListElement *linked_list_next(struct LinkedListElement *element)
{
  return element->next;
}
