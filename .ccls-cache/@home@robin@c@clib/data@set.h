// A general set abstraction on lists. 
//
// Doesn't use hashing so the time is not ideal.
// It should therefore only be used on small data.

#ifndef SET_H
#define SET_H

#include <stdbool.h>

#include "list.h"

struct Set {
  struct List list;  // Keep this as the first member.
  bool (*match)(void const * const a, void const * const b);
};

// Initializes the set.
//
// The complexity is O(1).
//
// @param set The set to initialize.
// @param match A function to determine whether to members match.
// @param destory method to free the value of a set. For plain pointers this
//   may be free, for more complex data the data type's destructor, for data
//   that should not be freed it should be NULL.
void
set_init(
    struct Set * set,
    bool (*match) (void const * const key1, void const * const key2),
    void (*destroy) (void *data));

// Deallocates a set and possibly the members.
//
// The complexity is O(n) where n is the number of elements in the set.
//
// @param set The set to deallocate.
void
set_destroy(struct Set *set);

// Inserts an element into the set.
//
// The complexity is O(n) where n is the number of elements in the set.
//
// @param set The set to insert into.
// @param data The data to insert.
// @return Whether the operation succeded.
bool
set_insert(struct Set * const set, void *data);

// Deletes an element from the set.
//
// The complexity is O(n) where n is the number of elements in the set.
//
// @param set The set to delete from.
// @param data The data to delete. The caller will need to free the data.
// @return Whether the operation succeded.
bool
set_remove(struct Set * const set, void **data);

// Creates the union of two sets.
//
// Note that the data must remain allocated until all sets are done working
// with the data. So freeing set1 after the union and then working with
// set_union will lead to trouble.
// The complexity is O(nm) where n and m are the sizes of set1 and set2.
//
// @param set_u The set to store the result of the union.
// @param set1 The first set to union.
// @param set2 The second set to union.
bool
set_union(
    struct Set * const set_u,
    struct Set const * const set1,
    struct Set const * const set2);

// Creates the intersection of two sets.
//
// Note that the data must remain allocated until all sets are done working
// with the data. So freeing set1 after the intersection and then working with
// set_intersection will lead to trouble.
// The complexity is O(nm) where n and m are the sizes of set1 and set2.
//
// @param set_i The set to store the result of the intersection.
// @param set1 The first set to intersect.
// @param set2 The second set to intersect.
bool
set_intersection(
    struct Set * const set_i,
    struct Set const * const set1,
    struct Set const * const set2);

// Creates the difference of two sets.
//
// Note that the data must remain allocated until all sets are done working
// with the data. So freeing set1 after the difference and then working with
// set_difference will lead to trouble.
// The complexity is O(nm) where n and m are the sizes of set1 and set2.
//
// @param set_d The set to store the result of the difference.
// @param set1 The superset.
// @param set2 The set to subtract.
bool
set_difference(
    struct Set * const set_d,
    struct Set const * const set1,
    struct Set const * const set2);


// Whether data is a member of set.
//
// The complexity is O(n) where n is the number of elements in the set.
//
// @param set The set to check presence in.
// @param data The data to check whether it is in set.
// @return Whether data is in set or not.
bool
set_is_member(struct Set const * const set, void const *data);

// Whether set2 is a subset of set1.
//
// The complexity is O(nm) where n and m are the number of elements.
//
// @param set1 The set to check presence in.
// @param set2 The set to check whether it is a subset of set1.
// @return Whether set2 is a subset of set1.
bool
set_is_subset(struct Set const *set1, struct Set const * const set2);

// Whether set2 is equivalent to set1
//
// The complexity is O(nm) where n and m are the number of elements.
//
// @param set1 The set to compare to.
// @param set2 The set to check whether it is equivalent.
// @return Whether set2 is a subset of set1.
bool
set_is_equal(struct Set const *set1, struct Set const * const set2);

// How many elements the set has.
//
// The complexity is O(1).
unsigned int
set_size(struct Set const * const set);

// Retrieves the first element of the set to iterate over.
//
// Time complexity: O(1).
//
// @param set The set to extract the first element of.
// @return The first element as a ListElement.
struct ListElement *
set_first_element(struct Set * const set);

// Returns the underlying list of the set.
//
// Time complexity: O(1).
//
// @param set The set.
//
struct List *
set_extract_list(struct Set * const set);
