#ifndef STR_H
#define STR_H

#include <stdbool.h>
#include <stddef.h>

bool str_starts_with(char const * const s, char const * const prefix);
bool str_ends_with(char const * const s, char const * const prefix);
bool str_contains(char const * const s, char const * const substr);
bool str_containc(char const * s, char const c);

size_t str_lstrip(char * const s, char const * const cs); 
size_t str_rstrip(char * const s, char const * const cs); 
size_t str_strip(char * const s, char const * const cs); 

bool str_remove_suffix(char * const s, char const * const suffix);
bool str_remove_prefix(char * const s, char const * const prefix);

#endif  // STR_H
