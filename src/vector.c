#include "vector.h"

int vec_init(vector* vec, int capacity)
{
    if (0 == capacity) { vec->capacity = 10; }
    else { vec->capacity = capacity; }
    
     vec->values = (vec_data*) malloc(capacity*sizeof(vec_data));

     if (NULL == vec->values) { return -1; }
 
     vec->size = 0;
     return 0;
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
        vec = (vector*) realloc(vec, vec->capacity*sizeof(vec_data));
        if(NULL == vec) { return -1; }
    }

    vec->values[vec->size] = *new_data;
    vec->size++;

    return 0;
}
