#ifndef BINSEARCH_H
#define BINSEARCH_H

#include <stddef.h>

// Binary search for a target value.
//
// @param A sorted dataset.
// @param n The number of elements.
// @param size The size of each elements in bytes.
// @param target The target element to find.
// @param comp A function taking two elements and compares them.
//     If a is "less" than b it should return a negative number.
//     If a is "more" than b it should return a positive number.
//     If a is "equal" to b it should return 0.
// @return A pointer to the found element or NULL if no match is found.
void *
binsearch(
    void const * const data,
    size_t const n,
    size_t const size,
    void const * const target,
    int (*comp)(void const * const a, void const * const b));

#endif // BINSEARCH_H
