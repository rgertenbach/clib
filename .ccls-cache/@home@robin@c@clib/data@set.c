#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "set.h"

typedef struct Set Set;
typedef struct List List;
typedef struct ListElement LE;

static List *
lst(Set * set)
{
  return &(set->list);
}

static List const *
clst(Set const * const set)
{
  return (List const *) &(set->list);
}


 
void
set_init(
    Set * set,
    bool (*match) (const void *key1, const void *key2),
    void (*destroy) (void *data))
{
  set->match = match;  
  list_init(lst(set), destroy);
}

void
set_destroy(Set *set)
{
  list_destroy(lst(set));
}

bool
set_insert(Set * const set, void *data)
{
  if (set_is_member(set, data)) return true;
  return list_insert_after(lst(set), list_tail((List *) set), data); 
}

bool
set_remove(Set * const set, void **data)
{
  LE *member;
  LE *prev = NULL;
  for (member = list_head(lst(set)); member != NULL; member = list_next(member)) {
    if (set->match(*data, list_data(member))) break;
    prev = member;
  }
  if (member == NULL) return false;  // Not found.
  return list_remove_after(lst(set), prev, data);
}

bool
set_union(
    Set * const set_u,
    Set const * const set1,
    Set const * const set2)
{
  LE *member;
  void *data;
  set_init(set_u, set1->match, NULL);
  for (member = list_head(clst(set1)); member != NULL; member = list_next(member)) {
    data = list_data(member);
    if (!list_insert_after(lst(set_u), list_tail(lst(set_u)), data)) {
      set_destroy(set_u); return false;
    }
  }
  for (member = list_head(clst(set2)); member != NULL; member = list_next(member)) {
    if (set_is_member(set1, list_data(member))) continue;
    data = list_data(member);
    if (!list_insert_after(lst(set_u), list_tail(lst(set_u)), data)) {
      set_destroy(set_u); return false;
    }
  }
  return true;
};

bool
set_intersection(
    Set * const set_i,
    Set const * const set1,
    Set const * const set2)
{
  set_init(set_i, set1->match, NULL);
  LE *member;
  for (member = list_head(clst(set1)); member != NULL; member = list_next(member)) {
    if (set_is_member(set2, list_data(member))) {
      if (!set_insert(set_i, list_data(member))) {
        set_destroy(set_i);
        return false;
      }
    }
  }
  return true;
}

bool
set_difference(
    Set * const set_d,
    Set const * const set1,
    Set const * const set2)
{
  set_init(set_d, set1->match, NULL);
  LE *member;
  for (member = list_head(clst(set1)); member != NULL; member = list_next(member)) {
    if (!set_is_member(set2, list_data(member))) {
      if (!set_insert(set_d, list_data(member))) {
        set_destroy(set_d);
        return false;
      }
    }
  }
  return true;
}

bool
set_is_member(Set const * const set, void const *data)
{
  LE *member;
  for (member = list_head((List *) set); member != NULL; member = list_next(member)) {
    if (set->match(list_data(member), data)) return true;
  }
  return false;
}

bool
set_is_subset(Set const *set1, Set const * const set2)
{
  if (set_size(set2) > set_size(set1)) return false;
  LE *member;
  for (member = list_head(clst(set2)); member != NULL; member = list_next(member)) {
    if (!set_is_member(set1, list_data(member))) return false;
  }
  return true;
}

bool
set_is_equal(Set const *set1, Set const * const set2)
{
  if (set_size(set1) != set_size(set2)) return false;
  LE *member;
  for (member = list_head(clst(set1)); member != NULL; member = list_next(member)) {
    if (!set_is_member(set2, list_data(member))) return false;
  }
  return true;
}

unsigned int
set_size(Set const * const set)
{
  return list_size((List *) set);
}

List *
set_extract_list(Set * const set)
{
  return &(set->list);
}

struct ListElement *
set_first_element(Set * const set)
{
  return list_head(set_extract_list(set));
}

