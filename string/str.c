#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "str.h"

bool str_starts_with(char const * s, char const * prefix)
{
    while (*prefix != '\0') {
	if (*s++ != *prefix++) { return false; }
    }
    return *prefix == '\0';
}

bool str_ends_with(char const * const s, const char * const suffix)
{
    size_t n1 = strlen(s);
    size_t n2 = strlen(suffix);
    if (n2 > n1) { return false; }
    return strncmp(s + n1 - n2, suffix, n2) == 0;

}

bool str_contains(char const * const s, const char *const substr)
{
    size_t n1 = strlen(s);
    size_t n2 = strlen(substr);
    if (n2 > n1) { return false; }
    for (size_t i = 0; i < n1 - n2 + 1; ++i) {
	if (strncmp(s + i, substr, n2) == 0) { return true; }
    }
    return false;
}

bool str_containc(char const * s, const char c)
{
    while (*s != '\0') {
	if (*s == c) { return true; }
	s++;
    }
    return false;
}

size_t str_lstrip(char * const s, char const * const cs)
{
    size_t offset = 0;
    while (str_containc(cs, s[offset])) { offset++; }
    strcpy(s, s + offset);
    return offset;
}

size_t str_rstrip(char * const s, char const * const cs)
{
    size_t n = strlen(s);
    size_t off = 0;
    while (str_containc(cs, s[n - 1 - off])) { off++; }
    s[n - off] = '\0';
    return off;
}

size_t str_strip(char * const s, char const * const cs)
{
    size_t moved = 0;
    moved += str_lstrip(s, cs);
    moved += str_rstrip(s, cs);
    return moved;
}

bool str_remove_suffix(char * const s, char const * const suffix)
{
    size_t n1 = strlen(s);
    size_t n2 = strlen(suffix);
    if (n2 <= n1 && strncmp(s + n1 - n2, suffix, n2) == 0) {
	s[n1 - n2] = '\0';
	return true;
    }
    return false;
}

bool str_remove_prefix(char * const s, char const * const prefix)
{
    size_t n1 = strlen(s);
    size_t n2 = strlen(prefix);
    if (n2 <= n1 && strncmp(s, prefix, n2) == 0) {
	strcpy(s, s + n2);
	return true;
    }
    return false;

}
