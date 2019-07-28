#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef union vec_data {
    int i;
    double d;
    char* c;
} vec_data;

typedef struct vector {
    vec_data* values;
    int size;
    int capacity;

} vector;

int vec_init(vector* vec, int capacity);
int vec_push_back(vector* vec, vec_data* new_data);

#endif