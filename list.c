#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"

void list_init(struct List *list, void (*destroy)(void *data))
{
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;
}

void list_destroy(struct List *list)
{
  if (list == NULL) return;
  void *data = NULL;

  while (list_size(list) > 0) {
    if (list_remove_after(list, NULL, &data) && list->destroy != NULL) 
      list->destroy(data);
  }
  memset(list, 0, sizeof(*list));
}

unsigned int list_size(struct List const * const list)
{
  return list->size;
}

struct ListElement *list_head(struct List *list)
{
  return list->head;
}

struct ListElement *list_tail(struct List *list)
{
  return list->tail;
}

bool list_insert_after(struct List *list, 
                       struct ListElement *after,
                       void *data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL");
    return false;
  }
  struct ListElement *new = malloc(sizeof(struct ListElement));
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

bool list_remove_after(struct List *list,
                       struct ListElement *after,
                       void **data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL\n");
    return false;
  }
  struct ListElement *target;
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

bool list_is_tail(struct ListElement *element)
{
  return element->next == NULL;
}
                      
bool list_is_head(struct List *list,
                  struct ListElement *element)
{
  return element == list->head;
}

void *list_data(struct ListElement *element)
{
  return element->data;
}

struct ListElement *list_next(struct ListElement *element)
{
  return element->next;
}
