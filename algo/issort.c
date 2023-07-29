#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "issort.h"

void
swap(void * const a, void * const b, void * const temp, size_t const size)
{
  memcpy(temp, a, size);
  memcpy(a, b, size);
  memcpy(b, temp, size);
}

bool
issort(
    void * data, 
    size_t n,
    size_t size,
    int (* comp)(void const * a, void const * b))
{
  if (n < 2) return true;
  char * arr = (char *) data;
  void * temp = malloc(size);
  if (temp == NULL) return false;
  for (size_t i = 1; i < n; ++i) {
    if (i > 0 && comp(arr + (i * size), arr + (i - 1) * size) < 0) {
      swap(arr + (i * size), arr + (i - 1) * size, temp, size);
      i -= 2;
      continue;
    }
  }
  free(temp);
  return true;
}
