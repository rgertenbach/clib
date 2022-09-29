#include <string.h>
#include <limits.h>

#include "split.h"

size_t strsplit(char ** const dest, 
                char const * const s, 
                char const * const delim)
{
  return strnsplit(dest, s, delim, SSIZE_MAX, SSIZE_MAX);
}

size_t strnsplit(char ** const dest,
                 char const * const s,
                 char const * const delim,
                 size_t const maxelem,
                 size_t const maxlen)
{
  if (*s == '\0' || maxelem == 0) return 0;
  size_t n = 0;
  size_t len = 0;
  size_t const delim_len = strlen(delim);
  size_t i = 0;

  for (; s[i] != '\0'; ++i) {
    if (len == maxlen - 1 || (len && strncmp(s + i, delim, delim_len) == 0)) {
      dest[n++][len] = '\0';
      len = 0;              
      // If we ran out of string length we move to the delimiter.
      // Very inefficient!  
      while (s[i] != '\0' && strncmp(s + i, delim, delim_len)) ++i;  
      i += delim_len - 1;
      if (n == maxelem) break;
    } else {
      dest[n][len++] = s[i];
    }
  }
  if (len && s[i] == '\0') dest[n++][len] = '\0';
  return n;
}
