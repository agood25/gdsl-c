#ifndef DS_DEF_H
#define DS_DEF_H

typedef union hashmap_data {
    int i;
    double d;
    char* c;
} hashmap_data;

typedef union stack_data {
    int i;
    double d;
    char* c;
} stack_data;

typedef union vec_data {
    int i;
    double d;
    char* c;
} vec_data;

#endif