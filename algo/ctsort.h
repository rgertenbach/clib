#ifndef CTSORT_H
#define CTSORT_H

#include <stdbool.h>
#include <stddef.h>

// Counting sort for 0 or positive integer data
//
// Time complexity O(n).
bool
ctsort(
    int * data,
    size_t const n,
    int const max);

#endif
