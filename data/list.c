#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"

typedef struct List List;
typedef struct ListElement ListElement;

void list_init(List *list, void (*destroy)(void *data))
{
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;
}

void list_destroy(List *list)
{
  if (list == NULL) return;
  void *data = NULL;

  while (list_size(list) > 0) {
    if (list_remove_after(list, NULL, &data) && list->destroy != NULL) 
      list->destroy(data);
  }
  memset(list, 0, sizeof(*list));
}

unsigned int list_size(List const * const list)
{
  return list->size;
}

ListElement *list_head(List *list)
{
  return list->head;
}

ListElement *list_tail(List *list)
{
  return list->tail;
}

bool list_insert_after(List *list, 
                       ListElement *after,
                       void *data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL");
    return false;
  }
  ListElement *new = malloc(sizeof(ListElement));
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

bool list_remove_after(List *list,
                       ListElement *after,
                       void **data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL\n");
    return false;
  }
  ListElement *target;
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

bool list_is_tail(ListElement *element)
{
  return element->next == NULL;
}
                      
bool list_is_head(List *list,
                  ListElement *element)
{
  return element == list->head;
}

void *list_data(ListElement *element)
{
  return element->data;
}

ListElement *list_next(ListElement *element)
{
  return element->next;
}
