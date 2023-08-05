#ifndef RXSORT_H
#define RXSORT_H

#include <stdbool.h>
#include <stddef.h>

// Radix sort for 0 or positive integer data
//
// Time complexity O(n).
//
// @param data THe data to sort.
// @param n The number of elements.
// @param max_elem_len The maximum number of digits.
// @param radix the number of discrete values a digit can take.
extern bool
rxsort(
    int * data,
    size_t const n,
    size_t const max_elem_len,
    size_t const radix);

#endif  // RXSORT_H
