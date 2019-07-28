#include "vector.h"

int vec_clear(vector* vec)
{
    if (NULL == vec || vec->size == 0) { return 0; }

    if (vec->capacity > VEC_INIT_CAPACITY)
    {
        vec->values = (vec_data*) realloc(vec->values, VEC_INIT_CAPACITY);
        if(NULL == vec->values) { return -1; }
    }

    vec->capacity = VEC_INIT_CAPACITY;
    if (vec->size > vec->capacity) { vec->size = vec->capacity; }
    
    size_t i;
    for (i = 0; i < vec->size; ++i)
    {
        memset(&vec->values[i], 0, sizeof(vec_data));
    }

    vec->size = 0;

    return 0;
}

void vec_erase_elem(vector* vec, size_t pos)
{
    if (NULL == vec->values || pos >= vec->size) { return; }

    // move the desired pos value to the end of our vector
    size_t i;
    for(i = pos; i < vec->size-1; ++i)
    {
        vec_swap_elem(vec, pos, pos+1);
    }

    // remove the last element in the vector as it now holds to desired value to remove
    vec_pop_back(vec);
}

int vec_init(vector* vec, size_t capacity)
{
    if (capacity == 0) { vec->capacity = VEC_INIT_CAPACITY; }
    else { vec->capacity = capacity; }
    
     vec->values = (vec_data*) malloc(capacity*sizeof(vec_data));

     if (NULL == vec->values) { return -1; }
 
     vec->size = 0;
     return 0;
}

void vec_pop_back(vector* vec)
{
    if (NULL == vec || vec->size == 0) { return; }
    vec->size--;
    memset(&vec->values[vec->size], 0, sizeof(vec_data));
}

int vec_push_back(vector* vec, vec_data* new_data)
{
    if (NULL == vec->values) 
    { 
        if (vec_init(vec, 0) == -1) { return -1; }
    }
    else if(vec->capacity == vec->size)
    {
        vec->capacity *=2;
        vec->values = (vec_data*) realloc(vec->values, vec->capacity*sizeof(vec_data));
        if(NULL == vec->values) { return -1; }
    }

    vec->values[vec->size] = *new_data;
    vec->size++;

    return 0;
}

int vec_reserve(vector* vec, size_t capacity)
{
    if (NULL == vec->values) { return vec_init(vec, capacity); }
    if (capacity <= vec->capacity) { return 0; }

    vec->capacity = capacity;
    vec->values = (vec_data*) realloc(vec->values, vec->capacity*sizeof(vec_data));
    if (NULL == vec->values) { return -1; }

    return 0;
}

void vec_swap_elem(vector* vec, size_t pos1, size_t pos2)
{
    if (NULL == vec->values || pos1 >= vec->size || pos2 >= vec->size) { return; }

    vec_data temp = vec->values[pos1];
    vec->values[pos1] = vec->values[pos2];
    vec->values[pos2] = temp;
}

vec_data* vec_val_at(vector* vec, size_t pos)
{
    if (NULL == vec->values || pos >= vec->size) { return NULL; }

    return &vec->values[pos];
}