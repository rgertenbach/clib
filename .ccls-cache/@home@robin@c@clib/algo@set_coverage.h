#ifndef SET_COVERAGE_H 
#define SET_COVERAGE_H

#include <stdbool.h>
#include "../data/set.h"

enum SetCoverageStatus {
  SET_COVERAGE_STATUS_MEMORY_FAILURE = -1,
  SET_COVERAGE_STATUS_NO_COVERAGE = 0,
  SET_COVERAGE_STATUS_SUCCESS = 1
};

struct KSet{
  void *key;
  struct Set set;
};

// Greedily calculates the smallest set of sets covering members.
//
// Runtime Complexity is O(m^3).
//
// @param covering The output that will contain the sets that cover members.
//     Must be malloced by caller.
// @param members The members that need to be covered.
//     Must be managed by caller.
// @param subsets The subsets containing the sets of elements.
//     Must be managed by caller.
enum SetCoverageStatus
set_coverage_cover(
    struct Set * covering,
    struct Set * members,
    struct Set * subsets);


#endif // !SET_COVERAGE_H
