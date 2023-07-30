#ifndef MGSORT_H
#define MGSORT_H

#include "stddef.h"
#include "stdbool.h"

// Merge sort
//
// Time Complexity: O(n log n).
//
// @param data The array to sort
// @n The number of elements
// @size The size of each element.
// @comp A function comparing two elements of the array. 
//     If a is greater than b the result should be positive.
//     If a is less than b the result should be negative.
//     If a is equal to b the result should be 0.
bool
mgsort(
    void * data, 
    size_t n,
    size_t size,
    int (* comp)(void const * a, void const * b));
#endif  // MGSORT_H

