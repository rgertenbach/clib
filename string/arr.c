#include <string.h>

#include "arr.h"

int strfind(char const * const s,
            char const * const * const arr,
            size_t const n)
{
  for (size_t i = 0; i < n; ++i) if (!strcmp(s, arr[i])) return i;
  return -1;
}

bool strin(char const * const s,
           char const * const * const arr,
           size_t const n)
{
  return strfind(s, arr, n) >= 0;
}
