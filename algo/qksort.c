#include <stdio.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "qksort.h"

static void
swap(void * const a, void * const b, void * const temp, size_t const size)
{
  memcpy(temp, a, size);
  memcpy(a, b, size);
  memcpy(b, temp, size);
}

extern void *
median3(
    void * const a, 
    void * const b,
    void * const c,
    int (*comp)(void const * a, void const * b))
{
  int const avb = comp(a, b);
  int const avc = comp(a, c);
  int const bvc = comp(b, c);
  // Any tie clearly identifiers a median of 3,
  if (avb == 0) return a;
  if (avc == 0) return a;
  if (bvc == 0) return b;

  if (avb < 0) {
    if (bvc < 0) return b;
    if (avc < 0) return c;
    return a;
  }
  if (avc < 0) return a;
  if (bvc < 0) return c;
  return b;
}


static void *
find_pivot3(
    void const * const data,
    size_t n,
    size_t size,
    int (*comp)(void const * a, void const * b))
{
  size_t i2 = (size_t) (rand() % n);
  size_t i1 = (size_t) (rand() % n);
  size_t i3 = (size_t) (rand() % n);
  char const * const bytes = (char *) data;

  void * const a = (void *) (bytes + (i1 * size));
  void * const b = (void *) (bytes + (i2 * size));
  void * const c = (void *) (bytes + (i3 * size));
  return median3(a, b, c, comp);
}

static bool
partition(
    char * bytes, 
    size_t n,
    size_t size,
    int (* comp)(void const * a, void const * b),
    size_t * const pivot_point)
{
  if (n <= 1) return true;
  size_t i = 0;
  size_t k = n - 1;
  void * temp = malloc(size);
  if (temp == NULL) return false;
  void * const pivot = find_pivot3(bytes, n, size, comp);
  while (i < k) {
    while (comp(bytes + (k * size), pivot) > 0) k--;
    while (comp(bytes + (i * size), pivot) < 0) i++;
    if (k == i || comp(bytes + (i * size), bytes + (k * size)) == 0) break;
    swap(bytes + (i * size), bytes + (k * size), temp, size);
  }
  free(temp);
  *pivot_point = k;
  return true;
}

extern bool
qksort(
    void * data, 
    size_t n,
    size_t size,
    int (* comp)(void const * a, void const * b))
{
  if (n < 2) return true;
  void * temp = malloc(size);
  if (temp == NULL) return false;
  char * bytes = (char *) data;
  size_t pivot_point;
  if (!partition(data, n, size, comp, &pivot_point)) goto failure;
  if (!qksort(bytes, pivot_point, size, comp)) goto failure;
  if (!qksort(bytes + (pivot_point * size), n - pivot_point, size, comp)) goto failure;
  free(temp);
  return true;

failure:
  free(temp);
  return false;
}
