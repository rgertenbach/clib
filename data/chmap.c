#include <stdlib.h>
#include <string.h>

#include "chmap.h"
#include "list.h"

void
chmap_init(
    struct CHMap *map,
    size_t const buckets,
    size_t (*hash)(void const *key),
    bool (*match)(void const *a, void const *b),
    void (*destroy)(void *data))
{
  map->n_buckets = buckets;
  map->buckets = malloc(buckets * sizeof(struct List *));
  for (size_t i = 0; i < buckets; ++i) {
    map->buckets[i] = malloc(sizeof(struct List));
    list_init(map->buckets[i], destroy);
  }
  map->hash = hash;
  map->match = match;
  map->sz = 0;
}

void
chmap_destroy(struct CHMap *map)
{
  for (size_t i = 0; i < map->n_buckets; ++i) list_destroy(map->buckets[i]);
  free(map->buckets);
  memset(map, 0, sizeof(struct CHMap));
}

bool
chmap_read(
    struct CHMap *map, 
    void const * target, 
    void **data)
{
  size_t const bucket = map->hash(target) % map->n_buckets;
  struct ListElement * le = list_head(map->buckets[bucket]);
  while (le != NULL) {
    void * ld = list_data(le);
    if (map->match(ld, target)) {
      *data = ld;
      return true;
    }
  }
  return false;
}

bool
chmap_insert(struct CHMap *map, void * data)
{
  size_t const bucket = map->hash(data) % map->n_buckets;
  return list_insert_after(map->buckets[bucket], NULL, data);
}
