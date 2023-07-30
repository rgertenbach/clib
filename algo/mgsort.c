#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "mgsort.h"

static bool
merge(
    void * const _left, 
    size_t const n_left, 
    void * const _right, 
    size_t const n_right, 
    size_t const size, 
    int (* comp)(void const * a, void const * b))
{
  char * left = (char *) _left;
  char * right = (char *) _right;
  size_t const n = n_left + n_right;
  char * temp = malloc(n * size);
  if (temp == NULL) return false;
  size_t i_left = 0; 
  size_t i_right = 0;
  size_t i_out = 0;
  while (i_left < n_left && i_right < n_right) {
    if (comp(left + i_left * size, right + i_right * size) < 0) {
      memcpy(temp + i_out++ * size, left + i_left++ * size, size);
    } else {
      memcpy(temp + i_out++ * size, right + i_right++ * size, size);
    }
  }
  while (i_left < n_left) memcpy(temp + i_out++ * size, left + i_left++ * size, size);
  while (i_right < n_right) memcpy(temp + i_out++ * size, right + i_right++ * size, size);
  memcpy(left, temp, n * size);
  free(temp);
  return true;
}

extern bool
mgsort(
    void * data, 
    size_t n,
    size_t size,
    int (* comp)(void const * a, void const * b))
{
  if (n <= 1) return true;
  char * bytes = (char *) data;
  size_t const n_left = n / 2;
  size_t const n_right = n - n / 2;
  if(!mgsort(bytes, n_left, size, comp)) return false;
  if(!mgsort(bytes + n_left * size, n_right, size, comp)) return false;
  return merge(bytes, n_left, bytes + n_left * size, n_right, size, comp);
}
