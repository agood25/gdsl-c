#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>

#include "ds_def.h"

enum { STACK_INIT_CAPACITY = 10 };

typedef struct stack {
    stack_data *values;
    size_t size;
    size_t capacity;

} stack;

int stack_clear(stack *s);
int stack_destroy(stack *s);
int stack_init(stack *s, size_t capacity);
int stack_push(stack *s, stack_data new_data);
int stack_pop(stack *s);
int stack_reserve(stack *s, size_t capacity);
stack_data * stack_top(stack *s);


#endif