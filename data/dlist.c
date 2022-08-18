#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dlist.h"

void dlist_init(struct Dlist *list, void (*destroy)(void *data))
{
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;
}

void dlist_destroy(struct Dlist *list)
{
  if (list == NULL) return;
  void *data = NULL;

  while (dlist_size(list) > 0) {
    if (dlist_remove(list, dlist_head(list), &data) && list->destroy != NULL) 
      list->destroy(data);
  }
  memset(list, 0, sizeof(*list));
}

unsigned int dlist_size(struct Dlist const * const list)
{
  return list->size;
}

struct DlistElement *dlist_head(struct Dlist *list)
{
  return list->head;
}

struct DlistElement *dlist_tail(struct Dlist *list)
{
  return list->tail;
}

bool dlist_is_tail(struct DlistElement *element)
{
  return element->next == NULL;
}
                      
bool dlist_is_head(struct DlistElement *element)
{
  return element->prev == NULL;
}

void *dlist_data(struct DlistElement *element)
{
  return element->data;
}

struct DlistElement *dlist_next(struct DlistElement *element)
{
  return element->next;
}


bool dlist_insert_after(struct Dlist *list, 
                        struct DlistElement *after,
                        void *data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL");
    return false;
  }
  struct DlistElement *new = malloc(sizeof(struct DlistElement));
  if (new == NULL) {
    fprintf(stderr, "No space to allocate new element");
    return false;
  }
  new->data = data;
  new->prev = after;
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

bool dlist_insert_before(struct Dlist *list, 
                         struct DlistElement *before,
                         void *data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL");
    return false;
  }
  struct DlistElement *new = malloc(sizeof(struct DlistElement));
  if (new == NULL) {
    fprintf(stderr, "No space to allocate new element");
    return false;
  }
  new->data = data;
  new->next = before;
  if (before == NULL) {
    new->prev = list->tail;
    if (list->tail != NULL) list->tail->next = new;
    list->tail = new;
  } else {
    new->prev = before->prev;
    before->prev = new;
    if (new->prev != NULL) new->prev->next = new;
  }
  if (before == list->head) list->head = new;
  list->size++;
  return true;
}
 
bool dlist_remove(struct Dlist *list, 
                  struct DlistElement *element, 
                  void **data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL\n");
    return false;
  }
  if (element == NULL) {
    fprintf(stderr, "Element must not be NULL\n");
    return false;
  }
  *data = element->data;
  
  if (dlist_is_head(element)) {
    list->head = element->next;
    if (list->head != NULL) list->head->prev = NULL;
  } else {
    element->prev->next = element->next;
  }

  if (dlist_is_tail(element)) {
    list->tail = element->prev;
    if (list->tail != NULL) list->tail->next = NULL;
  } else {
    element->next->prev = element->prev;
  }

  free(element);
  list->size--;
  return true;
}

