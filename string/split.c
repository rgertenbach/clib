#include <limits.h>
#include <string.h>

#include "split.h"

static bool
starts_with(char const * s, char const * prefix)
{
  while (*prefix != '\0') {
    if (*s == '\0' || *s != *prefix) {
      return false;
    }
    prefix++;
    s++;
  }
  return true;
}

extern size_t
strsplit(char ** const dest, char const * const s, char const * const delim)
{
  return strnsplit(dest, s, delim, SSIZE_MAX, SSIZE_MAX);
}

static size_t
strsplitcs(char ** const dest, char const * const s, size_t const maxelem)
{

  size_t nout = 0;
  for (size_t i = 0; i < maxelem && s[i] != '\0'; ++i) {
    dest[nout][0] = s[i];
    dest[nout++][1] = '\0';
  }
  return nout;
}

extern size_t
strnsplit(char ** const dest, char const * const s, char const * const delim,
          size_t const maxelem, size_t const maxlen)
{
  size_t const delim_len = strlen(delim);
  size_t const s_len = strlen(s);
  if (s_len == 0 || maxelem == 0 || maxelem == 0) {
    return 0;
  }
  if (delim_len == 0) {
    return strsplitcs(dest, s, maxelem);
  }
  size_t n_elems = 0;
  size_t elem_len = 0;
  size_t i = 0;
  while (i < s_len) {
    if (n_elems == maxelem) {
      break;
    }
    if (starts_with(s + i, delim)) {
      dest[n_elems++][elem_len] = '\0';
      elem_len = 0;
      i += delim_len;
      continue;
    }
    if (elem_len == maxlen - 1) {
      dest[n_elems++][elem_len] = '\0';
      elem_len = 0;
      while (i < s_len && !starts_with(s + i, delim)) {
        i++;
      }
      i += delim_len;
      continue;
    }
    dest[n_elems][elem_len++] = s[i++];
  }
  if (n_elems < maxelem && elem_len && s[i] == '\0') {
    dest[n_elems++][elem_len] = '\0';
  }
  return n_elems;
}
