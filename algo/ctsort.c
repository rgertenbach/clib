#include <stdbool.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "ctsort.h"

bool
ctsort(
    int * data,
    size_t const n,
    int const max)
{
  size_t const histsz = max + 1;
  size_t * hist = malloc(histsz * sizeof(size_t));
  memset(hist, 0, histsz * sizeof(size_t));
  if (hist == NULL) return false;
  int * out = malloc(n * sizeof(int));
  if (out == NULL) return false;

  for (size_t i = 0; i < n; ++i) hist[data[i]]++;
  for (size_t i = 1; i < histsz; ++i) hist[i] += hist[i - 1];
  for (size_t i = n; i-- > 0;) {
    int const val = data[i];
    out[--hist[val]] = val;
  }
  memcpy(data, out, n * sizeof(int));
  free(hist);
  free(out);
  return true;
}

