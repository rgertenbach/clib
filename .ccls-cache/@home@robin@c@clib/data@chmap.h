// A hashmap using linked lists to resolve conflicts.
//
// The data inserted should usually be some sort of key-value struct.
// This means hash and eq need to work usually on the key part.

#ifndef CHMAP_H
#define CHMAP_H

#include <stdlib.h>
#include <stdint.h>

#include "list.h"

struct CHMap {
  size_t sz;
  size_t n_buckets;
  size_t (*hash)(void const * data);
  struct List **buckets;
  bool (*match)(void const * a, void const * b);
};

// Initializes the chained hash map. Must be called before the it can be used.
//
// The complexity is O(n) for the size of the buckets.
//
// @param map The hashmap to initialize.
// @param buckets The number of hash buckets.
// @param hash The hashing function for the keys.
// @param eq A function for exact comparison of two keys.
// @param destroy The destructor for data stored in the chains.
//     Pass NULL if the data should not be freed.
void
chmap_init(
    struct CHMap *map,
    size_t buckets,
    size_t (*hash)(void const * data),
    bool (*match)(void const *a, void const *b),
    void (*destroy)(void *data));

// Destroys the hash map and its contents.
// 
// The complexity is O(n) for the number of buckets.
//
// @param map The hashmap to deallocate.
void
chmap_destroy(struct CHMap *map);

// Inserts or overwrites the value.
bool
chmap_insert(
    struct CHMap *map, 
    void const * data,
    void * value);

// Readsvalue of a key.
bool
chmap_read(
    struct CHMap *map, 
    void const * data,
    void ** value);

#endif // !CHMAP_H
