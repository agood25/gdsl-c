#include "hashmap.h"

// djb2 hashing algorithm
static size_t hashmap_get_hash(const char* key)
{
    if (NULL == key) { return SIZE_MAX; }

    size_t hash = 5381;
    int c;

    while ((c = *key++)) { hash = ((hash << 5) + hash) + c; } // hash * 33 + c

    return hash;
}

static int hashmap_swap_key_val(hashmap_key_val* hmkv1, hashmap_key_val* hmkv2)
{
    if (NULL == hmkv1 || NULL == hmkv2) { return -1; }

    hashmap_key_val temp = *hmkv1;

    hmkv1->value = hmkv2->value;
    hmkv1->key = hmkv2->key;

    hmkv2->value = temp.value;
    hmkv2->key = temp.key;

    return 0;
}

static int hashmap_destroy_key_val(hashmap* hm)
{
    if (NULL == hm ) { return -1; }

    if(NULL != hm->key_values) 
    {
        uint32_t i;
        for (i = 0; i < hm->capacity; ++i)
        {
            if (NULL == hm->key_values[i].key) { continue; }
            
            free(hm->key_values[i].key);
            hm->key_values[i].key = NULL;

            if (NULL == (*hm->val_free_func)) { continue; }
            hashmap_data* curr_val = &hm->key_values[i].value;
            (*hm->val_free_func) (&curr_val);
        }

        free(hm->key_values); 
        hm->key_values = NULL;
    }

    return 0;
}

static int hashmap_destroy_ext(hashmap** hm, bool destroy_kv)
{
    if (destroy_kv) { if (-1 == hashmap_destroy_key_val(*hm)) { return -1; } }
    
    free(*hm);
    *hm = NULL;

    return 0;
}

static int hashmap_copy_and_free_kv(hashmap* hm, hashmap_key_val* dst, hashmap_key_val* src)
{
    if (NULL == hm || NULL == dst || NULL == src) { return -1; }

    // copy the old value
    if(NULL == hm->val_copy_func) { dst->value = src->value; }
    else { ((*hm->val_copy_func)(&dst->value, &src->value)); }

    // free the old value if neccesary
    if (NULL != (*hm->val_free_func)) 
    {   
        hashmap_data* rm_data = &src->value; 
        (*hm->val_free_func) (&rm_data); 
    }

    // copy the old key
    dst->key = (char*) calloc(strlen(src->key) + 1, sizeof(char));
    if (NULL == dst->key) { return -1; }
    strncpy(dst->key, src->key, strlen(src->key) + 1);

    // free the old key
    free(src->key);
    src->key = NULL;

    return 0;
}

int hashmap_clear(hashmap* hm)
{
    if (NULL == hm || NULL == hm->key_values || hm->size == 0) { return 0; }

    hashmap_destroy_key_val(hm);

    if (hm->capacity > HASHMAP_INIT_CAPACITY)
    {
        hashmap_key_val* temp = (hashmap_key_val*) calloc(HASHMAP_INIT_CAPACITY, sizeof(hashmap_key_val));
        if(NULL == temp) { return -1; }

        hm->key_values = temp;
    }

    hm->capacity = HASHMAP_INIT_CAPACITY;
    hm->size = 0;

    return 0;
}

int hashmap_destroy(hashmap** hm)
{
    return hashmap_destroy_ext(hm, true);
}

int hashmap_erase_elem(hashmap* hm, const char* key)
{
    if (NULL == hm || NULL == hm->key_values) { return -1; }
    if (0 == hm->size) { return 0; }

    hashmap_key_val* kv = hashmap_find(hm, key);

    if (NULL == kv) { return 0; }

    size_t hash_val = hashmap_get_hash(key) % hm->capacity;
    hashmap_key_val* curr_hmkv = &hm->key_values[hash_val];

    // we're using open addressing, so check if any of the adjacent key_values have the same hash
    size_t next_hash_val = (hash_val+1) % hm->capacity;
    hashmap_key_val* next_hmkv = &hm->key_values[next_hash_val];

    while(NULL != next_hmkv->key)
    {
        // check for colliding hashes
        if (hashmap_get_hash(next_hmkv->key) % hm->capacity == hash_val)
        {
            // swap curr with next
            if (-1 == hashmap_swap_key_val(curr_hmkv, next_hmkv)) { return -1; }

            curr_hmkv = next_hmkv;
        }

        next_hash_val = (next_hash_val + 1) % hm->capacity;

        // break if we've gone around the whole hashmap; this shouldn't be possible
        if (next_hash_val == hash_val) { break; } 
    }

    memset(curr_hmkv, 0, sizeof(hashmap_key_val));

    return 0;
}

hashmap_key_val* hashmap_find(hashmap* hm, const char* key)
{
    if (NULL == hm || NULL == hm->key_values || 0 == hm->size) { return NULL; }

    size_t hash_val = hashmap_get_hash(key) % hm->capacity;
    size_t init_val = hash_val;

    while(NULL != hm->key_values[hash_val].key)
    {
        if (0 == strncmp(key, hm->key_values[hash_val].key, strlen(key)))
        {
            return &hm->key_values[hash_val];
        }

        hash_val = (hash_val + 1) % hm->capacity;

        // break if we've gone around the whole hashmap; this shouldn't be possible
        if (hash_val == init_val) { break; }
    }

    return NULL;
}

hashmap* hashmap_init(size_t capacity, int (*val_free_func)(hashmap_data** data), int (*val_copy_func)(hashmap_data* dst, hashmap_data* src))
{
    hashmap* ret = (hashmap*) malloc(sizeof(hashmap));
    if (NULL == ret) { return NULL; }

    if (capacity == 0) { ret->capacity = (size_t) ceilf(HASHMAP_INIT_CAPACITY); }
    else { ret->capacity = (size_t) ceilf(capacity); }
    
    ret->key_values = (hashmap_key_val*) calloc(ret->capacity, sizeof(hashmap_key_val));

    if (NULL == ret->key_values) { return NULL; }

    if (NULL == *val_free_func) { ret->val_free_func = NULL; }
    else { ret->val_free_func = val_free_func; }

    if (NULL == *val_copy_func) { ret->val_copy_func = NULL; }
    else { ret->val_copy_func = val_copy_func; }
 
    ret->size = 0;

    return ret;
}

int hashmap_insert(hashmap** hm, hashmap_key_val hmkv)
{
    // hashmap must be initialized via hashmap_init 
    if (NULL == hm || NULL == *hm || NULL == (*hm)->key_values)  { return -1; }

    // resize the hashmap if the size exceeds the capacity * the load factor
    if((*hm)->size+1 > (size_t) (*hm)->capacity*HASHMAP_LOAD_FACTOR)
    {
        // resize the key_values and re-insert all of the values currently in the hash map
        if (-1 == hashmap_reserve(hm, (*hm)->capacity*(*hm)->capacity)) { return -1; }
    }

    size_t hash_val = hashmap_get_hash(hmkv.key) % (*hm)->capacity;

    // find the next available slot to insert our key value
    while(NULL != (*hm)->key_values[hash_val].key) { hash_val = (hash_val + 1) % (*hm)->capacity; }
    
    (*hm)->key_values[hash_val] = hmkv;
    (*hm)->size++;

    return 0;
}

int hashmap_reserve(hashmap** hm, size_t capacity)
{
    if (NULL == hm || NULL == *hm || NULL == (*hm)->key_values || 0 == capacity) { return -1; }

     // resize the key_values and re-insert all of the values currently in the hash map
    hashmap* temp_hashmap = hashmap_init(capacity, (*hm)->val_free_func, (*hm)->val_copy_func);
    if (NULL == temp_hashmap) { return -1; }

    size_t i;
    for (i = 0; i < (*hm)->capacity; ++i)
    {
        hashmap_key_val* curr_kv = &(*hm)->key_values[i];

        // ignore all empty entries
        if(NULL == curr_kv->key) { continue; }

        hashmap_key_val temp_kv = {0};
        if (-1 == hashmap_copy_and_free_kv(*hm, &temp_kv, curr_kv)) { return -1; }

        // re-insert values into the temporary hashmap
        if (-1 == hashmap_insert(&temp_hashmap, temp_kv)) { return -1; }
    }

    // after resizeing, destroy the old hashmap and set it to the temp hashmap
    if (-1 == hashmap_destroy_ext(hm, true)) { return -1; }
    
    *hm = temp_hashmap;

    return 0;
}
