#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>

#include "ds_def.h"

enum { VEC_INIT_CAPACITY = 10 };

typedef struct vector {
    vec_data *values;
    void (*free_vec_data)(vec_data *); // optional function pointer to define how to free the data held in values 
    size_t size;
    size_t capacity;

} vector;

int vec_clear(vector *vec);
void vec_destroy(vector *vec);
int vec_erase_elem(vector *vec, size_t pos);
int vec_init(vector *vec, size_t capacity, void (*free_function) (vec_data *));
int vec_pop_back(vector *vec);
int vec_push_back(vector *vec, vec_data new_data);
int vec_reserve(vector *vec, size_t capacity);
int vec_swap_elem(vector *vec, size_t pos1, size_t pos2);
vec_data * vec_val_at(vector *vec, size_t pos);


#endif