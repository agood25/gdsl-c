#ifndef HASHMAP_H
#define HASHMAP_H

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "gdsl_def.h"

enum { HASHMAP_INIT_CAPACITY = 10 };
static const float HASHMAP_LOAD_FACTOR = 0.75;

typedef struct hashmap_key_val {
    char* key;
    hashmap_data value;

} hashmap_key_val;

typedef struct hashmap {
    hashmap_key_val* key_values;
    size_t size;
    size_t capacity;
    int (*val_free_func)(hashmap_data** data);
    int (*val_copy_func)(hashmap_data* dst, hashmap_data* src);

} hashmap;

int hashmap_clear(hashmap** hm);
int hashmap_destroy(hashmap** hm);
int hashmap_erase_elem(hashmap* hm, const char* key);
hashmap_key_val* hashmap_find(hashmap* hm, const char* key);
hashmap* hashmap_init(size_t capacity, int (*val_free_func)(hashmap_data** data), int (*val_copy_func)(hashmap_data* dst, hashmap_data* src));
int hashmap_insert(hashmap** hm, hashmap_key_val hmkv);
int hashmap_reserve(hashmap** hm, size_t capacity);

static size_t hashmap_get_hash(const char* key);
static int hashmap_swap_key_val(hashmap_key_val* hmvk1, hashmap_key_val* hmkv2);
static int hashmap_destroy_key_val(hashmap** hm);

#endif