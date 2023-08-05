#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "rxsort.h"

extern bool
rxsort(
    int * data,
    size_t const n,
    size_t const max_elem_len,
    size_t const radix)
{
  size_t * hist = malloc(radix * sizeof(size_t));
  if (hist == NULL) return false;
  int *temp = malloc(n * sizeof(int));
  if (temp == NULL) return false;

  for (size_t nth = 0; nth < max_elem_len; ++nth) {
    memset(hist, 0, radix * sizeof(size_t));
    size_t pval = (size_t) pow((double) radix, (double) nth);
    for (size_t i = 0; i < n; ++i) hist[(data[i] / pval) % radix]++;
    for (size_t i = 1; i < radix; ++i) hist[i] += hist[i - 1];  // Cumssum
    for (size_t i = n; i-- > 0;) {
       size_t index = (data[i] / pval) % radix;
       temp[hist[index] - 1] = data[i];
       hist[index]--;
    }
    memcpy(data, temp, n * sizeof(int));
  }

  free(hist);
  free(temp);
  return true;
}

