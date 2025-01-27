#ifndef BIGINT_H
#define BIGINT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct BigUint {
  size_t sz;
  uint64_t * bits;
};

// Constructors
struct BigUint * biguint_from_uint(uint64_t const);
struct BigUint * biguint_from_str(char const * const);
struct BigUint * biguint_from_bstr(char const * const);

// Destructor
void biguint_delete(struct BigUint * const);

// Formatting
void biguint_format_decimal(char * const, struct BigUint const * const);
void biguint_format_binary(char * const, struct BigUint const * const);

// Bit operations
bool biguint_ilsh(struct BigUint * const, size_t const);
bool biguint_irshhift_right(struct BigUint * const, size_t const);
struct BigUint * biguint_lsh(struct BigUint const * const, size_t const);
struct BigUint * biguint_rsh(struct BigUint const * const, size_t const);

// Low level
size_t biguint_highest_bit(struct BigUint const * const);

#endif // BIGINT_H
