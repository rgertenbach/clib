#ifndef ISSORT_H
#define ISSORT_H

#include "stddef.h"
#include "stdbool.h"

// Insertion sort
//
// Sorts in place.
// Time Complexity: O(n^2).
//
// @param data The array to sort
// @n The number of elements
// @size The size of each element.
// @comp A function comparing two elements of the array. 
//     If a is greater than b the result should be positive.
//     If a is less than b the result should be negative.
//     If a is equal to b the result should be 0.
bool
issort(
    void * data, 
    size_t n,
    size_t size,
    int (* comp)(void const * a, void const * b));
#endif  // ISSORT_H

