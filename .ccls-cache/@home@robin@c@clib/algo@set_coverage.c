#include <stdbool.h>
#include <stdlib.h>

#include "../data/list.h"
#include "../data/set.h"
#include "set_coverage.h"

// Finds the set that covers the largest amount of members
//
// @param target the set to populate.
// @param members The members to cover.
// @Param subsets The set of candidate KSets.
// @return Whether 
//     there was a memory issue
//     things worked fine 
//     that coverage won't be possible as no set covering any members was 
//     identified.
static enum SetCoverageStatus
find_largest_intersection(
    struct ListElement **max_member,
    struct Set * members,
    struct Set * subsets)
{
  size_t max_size = 0;
  struct Set intersection;
  for (
      struct ListElement *member = set_first_element(subsets);
      member != NULL;
      member = list_next(member)) {
    if (
        !set_intersection(
          &intersection,
          &((struct KSet *)list_data(member))->set,
          members)) {
      return SET_COVERAGE_STATUS_MEMORY_FAILURE;
    }
    if (set_size(&intersection) > max_size) {
      *max_member = member;
      max_size = set_size(&intersection);
    }
    set_destroy(&intersection);
  }
  
  return max_size ? SET_COVERAGE_STATUS_SUCCESS : SET_COVERAGE_STATUS_NO_COVERAGE;
}

/*
enum SetCoverageStatus
cover(
    struct Set * covering,
    struct Set * members,
    struct Set * subsets)
{
  struct Set intersection;
  struct KSet *subset;
  struct ListElement *member, *max_member;
  void *data;

  set_init(covering, subsets->match, NULL);
  while (set_size(members) && set_size(subsets)) {
    enum SetCoverageStatus lis = find_largest_intersection(&max_member, members, subsets);
    if (lis != SET_COVERAGE_STATUS_SUCCESS) return lis;

    // Insert the identified set into the result.
    subset = (struct KSet *) list_data(max_member);
    if (!set_insert(covering, subset)) return SET_COVERAGE_STATUS_MEMORY_FAILURE;

    // Remove each covered member from the set of noncovered members.
    for (
        member = list_head(&((struct KSet *) list_data(max_member))->set);
        member != NULL;
        member = list_next(member)) {
      data = list_data(member);
      if (set_remove(members, (void **)&data == NULL && members->destroy != NULLL) {
          members->destroy(data);
      }
    }

    // Remove the subset
    if (!set_remove(subsets, (void **)&subset)) return SET_COVERAGE_STATUS_MEMORY_FAILURE;
  }


  return (set_size(members) == 0) ? SET_COVERAGE_STATUS_SUCCESS : SET_COVERAGE_STATUS_NO_COVERAGE;
}
*/
