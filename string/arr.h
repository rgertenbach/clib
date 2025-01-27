#ifndef STRING_ARR_H
#define STRING_ARR_H

#include <stdlib.h>
#include <stdbool.h>

// Finds the index of first occurrence of s in arr or returns -1.
//
// @param s The string to find.
// @param arr The array to find s in.
// @param n The number of elements in arr.
// @return The index of the first occurrence.
int strfind(char const * const s,
            char const * const * const arr,
            size_t const n);

// Whether a string is in an array of strings.
//
// @param s The string to find.
// @param arr The array to find s in.
// @param n The number of elements in arr.
// @return Whether s is in arr.
bool strin(char const * const s,
           char const * const * const arr,
           size_t const n);

#endif

