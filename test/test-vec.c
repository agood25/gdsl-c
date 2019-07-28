#include <stdio.h>

#include "vector.h"

int main()
{
    vector vec = {0};
    vec_data var = {0};
    var.c = "Hello World";

    vec_push_back(&vec, &var);

    size_t i;
    for (i = 0; i < vec.size; ++i)
    {
        printf("%s\n",  vec.values[i].c);
    }

    return 0;
}