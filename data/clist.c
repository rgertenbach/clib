#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "clist.h"

void clist_init(struct CList *list, void (*destroy)(void *data))
{
  list->size = 0;
  list->destroy = destroy;
  list->curr = NULL;
}

void clist_destroy(struct CList *list)
{
  if (list == NULL) return;
  void *data = NULL;
  struct CListElement *curr = list->curr;
  struct CListElement *next = NULL;
  // force an end
  if (curr != NULL) {
    next = curr->next;
    curr->next = NULL;
  }

  while (next != NULL) {
    curr = next;
    next = curr->next;
    curr->next = NULL;
    data = curr->data;
    if (list->destroy != NULL) 
      list->destroy(data);
  }
  memset(list, 0, sizeof(*list));
}

unsigned int clist_size(struct CList const * const list)
{
  return list->size;
}

struct CListElement *clist_current(struct CList *list)
{
  return list->curr;
}

bool clist_is_current(struct CList *list,
                      struct CListElement *element)
{
  return element == list->curr;
}

bool clist_insert_after(struct CList *list, 
                        struct CListElement *after,
                        void *data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL");
    return false;
  }
  struct CListElement *new = malloc(sizeof(struct CListElement));
  if (new == NULL) {
    fprintf(stderr, "No space to allocate new element");
    return false;
  }
  if (list->size == 0 && after != NULL) {
    fprintf(stderr, "List is empty but after is not NULL.");
    return false;
  }
  if (list->size > 0 && after == NULL) {
    fprintf(stderr, "after may only be NULL if the list is empty.");
    return false;
  }

  new->data = data;
  if (after == NULL) {
    new->next = new;
    list->curr = new;
  } else {
    new->next = after->next;
    after->next = new;
  }
  list->size++;
  return true;
}

bool clist_remove_after(struct CList *list,
                        struct CListElement *after,
                        void **data)
{
  if (list == NULL) {
    fprintf(stderr, "List must not be NULL\n");
    return false;
  }
  if (list->size == 0) {
    fprintf(stderr, "List must not be empty\n");
    return false;
  }
  if (list == NULL && clist_size(list) > 0) {
    fprintf(stderr, "List has elements, after must not be NULL\n");
    return false;
  }
  struct CListElement *target;
  target = after->next;
  if (clist_size(list) == 1) {
    list->curr = NULL;
  } else {
    after->next = target->next;
  }
  *data = target->data;
  if (target == list->curr) list->curr = after;
  free(target);
  list->size--;
  return true;
}

void *clist_data(struct CListElement *element)
{
  return element->data;
}

struct CListElement *clist_next(struct CListElement *element)
{
  return element->next;
}
