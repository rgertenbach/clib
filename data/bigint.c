#include "./bigint.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint64_t
biguint_bit_at(struct BigUint const * const x, size_t const i)
{
  uint64_t const bits = x->bits[i / 64];
  uint64_t const mask = 1 << (i % 64);
  return !!(bits & mask);
}

static void
biguint_set_bit_at(struct BigUint const * const x, size_t i,
                   uint64_t const val)
{
  uint64_t offmask = ~(1 << (i % 64));
  uint64_t valmask = !!val << (i % 64);
  x->bits[i / 64] &= offmask;
  x->bits[i / 64] |= valmask;
}

static struct BigUint *
biguint_new(size_t const length)
{
  struct BigUint * out = malloc(sizeof(struct BigUint));
  if (out == NULL) {
    return out;
  }
  out->bits = calloc(length, sizeof(uint64_t));
  out->sz = length;
  return out;
}

static bool
biguint_resize(struct BigUint * const x, size_t const newsize)
{
  uint64_t * new = calloc(newsize, sizeof(uint64_t));
  if (new == NULL) {
    return false;
  }
  memcpy(new, x->bits, x->sz * sizeof(uint64_t));
  memset(x->bits, 0, x->sz * sizeof(uint64_t));
  free(x->bits);
  x->bits = new;
  x->sz = newsize;
  return true;
}

extern void
biguint_delete(struct BigUint * const x)
{
  memset(x->bits, 0, x->sz * sizeof(uint64_t));
  free(x);
}

extern struct BigUint *
biguint_from_uint(uint64_t const x)
{
  struct BigUint * out = biguint_new(1);
  out->bits[0] = x;
  return out;
}

// How many entries of `bits` are actually used.
static size_t
biguint_utilization(struct BigUint const * const x)
{
  for (size_t i = x->sz; i-- > 0;) {
    if (x->bits[i] > 0) {
      return i + 1;
    }
  }
  return 1; // It's 0 but that takes 1 bit of information.
}

// How many bits are actualy used.
extern size_t
biguint_highest_bit(struct BigUint const * const x)
{
  size_t current_bits = biguint_utilization(x);
  uint64_t bits = x->bits[current_bits - 1];
  size_t shifts = 1;
  while (bits >> shifts) {
    shifts++;
  }
  return shifts;
}

void
biguint_format_decimal(char * dest, struct BigUint const * const x)
{
  /*size_t current_bit = biguint_highest_bit(x);*/
  (void)dest;
  (void)x;
}

void
biguint_format_binary(char * dest, struct BigUint const * const x)
{
  size_t highest_bit = biguint_highest_bit(x);
  size_t bit = 0;
  for (; bit < highest_bit; ++bit) {
    dest[highest_bit - bit - 1]
        = (x->bits[bit / 64] & (1 << (bit % 64))) ? '1' : '0';
  }
  dest[bit] = '\0';
}

bool
biguint_ilsh(struct BigUint * const x, const size_t n)
{
  size_t highest_bit = biguint_highest_bit(x);
  size_t target_bit = highest_bit + n;
  if (highest_bit + n > 64 * x->sz && !biguint_resize(x, target_bit / 64)) {
    return false;
  }
  if (n > 2) {
    fprintf(stderr,
            "before move: bits[1]: %lu bits[0]: %lu target_bit: %zu %zu\n",
            x->bits[1], x->bits[0], target_bit, highest_bit);
  }
  while (highest_bit > 0) {
    highest_bit--;
    target_bit--;
    biguint_set_bit_at(x, target_bit, biguint_bit_at(x, highest_bit));
  }
  if (n > 2) {
    fprintf(stderr, "after move: %lu %lu %zu %zu\n", x->bits[1], x->bits[0],
            target_bit, highest_bit);
  }
  // Somehow this part deletes all data.
  while (target_bit-- > 0) {
    biguint_set_bit_at(x, target_bit, 0);
    if (n > 2) {
      fprintf(stderr, "during 0: %lu %lu %zu %zu\n", x->bits[1], x->bits[0],
              target_bit, highest_bit);
    }
  }
  if (n > 2) {
    fprintf(stderr, "after 0 resize: %lu %lu\n", x->bits[1], x->bits[0]);
  }
  return true;
}
