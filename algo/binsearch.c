#include <stddef.h>
#include <stdint.h>

#include "binsearch.h"


void *
binsearch(
    void const * const data,
    size_t const n,
    size_t const size,
    void const * const target,
    int (*comp)(void const * const a, void const * const b))
{
  char const * const bytes = (char *) data;
  if (n == 0) return NULL;
  size_t lo = 0;
  size_t hi = n - 1;
  size_t guess;
  int result;
  while (lo <= hi) {
    guess = lo + (hi - lo) / 2;
    result = comp(bytes + guess * size, target);
    
    if (result == 0) return (void *) (bytes + guess * size);

    if (result > 0) {
      if (guess == 0) break;
      hi = guess - 1;
    } else if (result < 0) {
      if (guess == SIZE_MAX) break;
      lo = guess + 1;
    }
  }
  return NULL;
}
