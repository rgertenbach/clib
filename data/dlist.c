#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dlist.h"

typedef struct Dlist Dlist;
typedef struct DlistElement DlistElement;

void dlist_init(Dlist *list, void (*destroy)(void *data))
{
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;
}

void dlist_destroy(Dlist *list)
{
  if (list == NULL) return;
  void *data = NULL;

  while (dlist_size(list) > 0) {
    if (dlist_remove(list, dlist_head(list), &data) && list->destroy != NULL) 
      list->destroy(data);
  }
  memset(list, 0, sizeof(*list));
}

unsigned int dlist_size(Dlist const * const list)
{
  return list->size;
}

DlistElement *dlist_head(Dlist *list)
{
  return list->head;
}

DlistElement *dlist_tail(Dlist *list)
{
  return list->tail;
}

bool dlist_is_tail(DlistElement *element)
{
  return element->next == NULL;
}
                      
bool dlist_is_head(DlistElement *element)
{
  return element->prev == NULL;
}

void *dlist_data(DlistElement *element)
{
  return element->data;
}

DlistElement *dlist_next(DlistElement *element)
{
  return element->next;
}


bool dlist_insert_after(Dlist *list, 
                        DlistElement *after,
                        void *data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL");
    return false;
  }
  DlistElement *new = malloc(sizeof(DlistElement));
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

bool dlist_insert_before(Dlist *list, 
                         DlistElement *before,
                         void *data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL");
    return false;
  }
  DlistElement *new = malloc(sizeof(DlistElement));
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
 
bool dlist_remove(Dlist *list, 
                  DlistElement *element, 
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

