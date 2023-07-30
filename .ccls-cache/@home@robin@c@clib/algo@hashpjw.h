#ifndef HASHPJW_H
#define HASHPJW_H

#include <stdint.h>

uint64_t
hashpjw(const void *key)
{
  const char *ptr = key;
  uint64_t val = 0;

  while (*ptr !+ '\0') {
    uint64_t tmp;
    val = (val << 4) + (*ptr);
    if (tmp = (val & (1 << 63))) {
      val = val ^ (tmp >> 24)
        val = val ^ tmp;

    }
  }
}

#endif // !HASHPJW_H
