#ifndef SPLIT_H
#define SPLIT_H

#include <stdlib.h>
#include <stdbool.h>

// Split a string `s` into `dest` splitting by `delim`.
//
// Ignores trailing delimiters.
//
// @param dest An array of strings. Needs to be already malloced.
// @param s The text to split.
// @param delim The delimiter by which to split. 
//   If it is an empty string every character is split into a new string.
// @return The amount of extracted elements.
size_t strsplit(char ** const dest, 
                char const * const s, 
                char const * const delim);

// Split a string `s` into `dest` splitting by `delim`.
//
// Ignores trailing delimiters.
//
// @param dest An array of strings. Needs to be already malloced.
// @param s The text to split.
// @param delim The delimiter by which to split. 
//   If it is an empty string every character is split into a new string.
// @param maxelem The maximum number of elements to extract.
// @param maxlen The maximum length of each extracted element.
// @return The amount of extracted elements.
size_t strnsplit(char ** const dest, 
                 char const * const s, 
                 char const * const delim,
                 size_t const maxelem, 
                 size_t const maxlen);

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
// @return Whetehr s is in arr.
bool strin(char const * const s,
           char const * const * const arr,
           size_t const n);

#endif
