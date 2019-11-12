#include "stack.h"

int stack_clear(stack *s)
{
    if (!s || !s->values || s->size == 0) { return 0; }

    if (s->capacity > STACK_INIT_CAPACITY)
    {
        stack_data *temp = (stack_data*) realloc(s->values, STACK_INIT_CAPACITY);
        if(NULL == temp) { return -1; }

        s->values = temp;
    }

    s->capacity = STACK_INIT_CAPACITY;
    if (s->size > s->capacity) { s->size = s->capacity; }
    
    size_t i;
    for (i = 0; i < s->size; ++i)
    {
        memset(&s->values[i], 0, sizeof(stack_data));
    }

    s->size = 0;

    return 0;
}

int stack_destroy(stack *s)
{
    if (!s) { return -1; }

    if(NULL != s->values) 
    { 
        free(s->values); 
        s->values = NULL;
    }

    memset(s, 0, sizeof(stack));

    return 0;
}

int stack_init(stack *s, size_t capacity)
{
    if (!s) { return -1; }

    if (capacity == 0) { s->capacity = STACK_INIT_CAPACITY; }
    else { s->capacity = capacity; }
    
    s->values = (stack_data *) malloc(s->capacity*sizeof(stack_data));

    if (NULL == s->values) { return -1; }
 
    s->size = 0;
    return 0;
}

int stack_push(stack *s, stack_data new_data)
{
    if (!s) { return -1; }

    if (NULL == s->values) 
    { 
        if (stack_init(s, 0) == -1) { return -1; }
    }

    else if(s->capacity == s->size)
    {
        s->capacity *=2;
        stack_data *temp = (stack_data *) realloc(s->values, s->capacity*sizeof(stack_data));
        if(NULL == temp) { return -1; }

        s->values = temp;
    }

    s->values[s->size] = new_data;
    s->size++;

    return 0; 
}

int stack_pop(stack *s)
{
    if (!s || !s->values || s->size == 0) { return -1; }
    s->size--;
    memset(&s->values[s->size], 0, sizeof(stack_data));

    return 0;
}

int stack_reserve(stack *s, size_t capacity)
{
    if (!s || !s->values) { return stack_init(s, capacity); }
    if (capacity <= s->capacity) { return 0; }

    s->capacity = capacity;
    stack_data *temp = (stack_data *) realloc(s->values, s->capacity*sizeof(stack_data));
    if (NULL == temp) { return -1; }

    s->values = temp;

    return 0;
}

stack_data * stack_top(stack *s)
{
    if (!s || !s->values || s->size == 0) { return NULL; }

    return &s->values[s->size-1];
}