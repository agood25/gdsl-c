#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "gdsl_def.h"

START_TEST(test_vec_clear)
{
    vector vec = {0};

    int i;
    for (i = 0; i < 10; ++i)
    {
        vec_data new_data = {0};
        new_data.i = i;
        ck_assert_int_eq(vec_push_back(&vec, new_data), 0);
    }

    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (i = 0; i < 10; ++i)
    {
        ck_assert_int_eq(vec.values[i].i, expected[i]);
    }

    ck_assert_int_eq(vec_clear(&vec), 0);

    ck_assert_uint_eq(vec.size, 0);
    ck_assert_uint_eq(vec.capacity, VEC_INIT_CAPACITY);

    ck_assert_int_eq(vec.values[0].i, 0);
    vec_destroy(&vec);
}
END_TEST

START_TEST(test_vec_erase_elem)
{
    vector vec = {0};
    
    int i;
    for (i = 0; i < 20; ++i)
    {
        vec_data new_data = {0};
        new_data.i = i;
        ck_assert_int_eq(vec_push_back(&vec, new_data), 0);
    }

    ck_assert_int_eq(vec_erase_elem(&vec, 5), 0);
    ck_assert_int_eq(vec_erase_elem(&vec, 7), 0);
    ck_assert_int_eq(vec_erase_elem(&vec, 14), 0);

    ck_assert_int_eq(vec_erase_elem(&vec, 20), -1);

    int expected[] = {0, 1, 2, 3, 4, 6, 7, 9, 10, 11, 12, 13, 14, 15, 17, 18, 19};

    for (i = 0; i < 17; ++i)
    {
        ck_assert_int_eq(vec.values[i].i, expected[i]);
    }

    ck_assert_uint_eq(vec.size, 17);

    vec_destroy(&vec);
}
END_TEST

START_TEST(test_vec_init)
{
    vector vec = {0};
    ck_assert_ptr_eq(vec.values, NULL);

    ck_assert_int_eq(vec_init(&vec, 0), 0);
    ck_assert_ptr_ne(vec.values, NULL);
    ck_assert_uint_eq(vec.capacity, VEC_INIT_CAPACITY);
    ck_assert_uint_eq(vec.size, 0);

    vector vec2 = {0};

    ck_assert_int_eq(vec_init(&vec2, 1235), 0);
    ck_assert_uint_eq(vec2.capacity, 1235);
    ck_assert_uint_eq(vec2.size, 0);

    vec_destroy(&vec);
    vec_destroy(&vec2);
}
END_TEST

START_TEST(test_vec_pop_back)
{
    vector vec = {0};

    ck_assert_int_eq(vec_pop_back(&vec), -1);
    
    int i;
    for (i = 0; i < 20; ++i)
    {
        vec_data new_data = {0};
        new_data.i = i;
        ck_assert_int_eq(vec_push_back(&vec, new_data), 0);
    }

    ck_assert_int_eq(vec_pop_back(&vec), 0);
    ck_assert_int_eq(vec_pop_back(&vec), 0);
    ck_assert_int_eq(vec_pop_back(&vec), 0);
    ck_assert_int_eq(vec_pop_back(&vec), 0);

    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    for (i = 0; i < 16; ++i)
    {
        ck_assert_int_eq(vec.values[i].i, expected[i]);
    }

    ck_assert_uint_eq(vec.size, 16);

    vec_destroy(&vec);
}
END_TEST

START_TEST(test_vec_push_back)
{
    vector vec = {0};
    
    int i;
    for (i = 0; i < 20; ++i)
    {
        vec_data new_data = {0};
        new_data.i = i;
        ck_assert_int_eq(vec_push_back(&vec, new_data), 0);
    }

    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    for (i = 0; i < 20; ++i)
    {
        ck_assert_int_eq(vec.values[i].i, expected[i]);
    }

    ck_assert_uint_eq(vec.size, 20);

    vec_destroy(&vec);
}
END_TEST

START_TEST(test_vec_reserve)
{
    vector vec = {0};

    ck_assert_int_eq(vec_reserve(&vec, 20), 0);

    ck_assert_uint_eq(vec.capacity, 20);

    int i;
    for (i = 0; i < 20; ++i)
    {
        vec_data new_data = {0};
        new_data.i = i;
        ck_assert_int_eq(vec_push_back(&vec, new_data), 0);
    }

    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    for (i = 0; i < 20; ++i)
    {
        ck_assert_int_eq(vec.values[i].i, expected[i]);
    }

    ck_assert_uint_eq(vec.size, 20);

    vec_destroy(&vec);
}
END_TEST

START_TEST(test_vec_swap_elem)
{
    vector vec = {0};

    int i;
    for (i = 0; i < 20; ++i)
    {
        vec_data new_data = {0};
        new_data.i = i;
        ck_assert_int_eq(vec_push_back(&vec, new_data), 0);
    }

    int expected[] = {11, 1, 2, 16, 4, 19, 6, 7, 8, 9, 10, 0, 12, 13, 14, 15, 3, 17, 18, 5};

    ck_assert_int_eq(vec_swap_elem(&vec, 0, 11), 0);
    ck_assert_int_eq(vec_swap_elem(&vec, 3, 16), 0);
    ck_assert_int_eq(vec_swap_elem(&vec, 5, 19), 0);
    
    ck_assert_int_eq(vec_swap_elem(&vec, 20, 2), -1);

    for (i = 0; i < 20; ++i)
    {
        ck_assert_int_eq(vec.values[i].i, expected[i]);
    }

    ck_assert_uint_eq(vec.capacity, VEC_INIT_CAPACITY*2);
    ck_assert_uint_eq(vec.size, 20);

    vec_destroy(&vec);
}
END_TEST

START_TEST(test_vec_val_at)
{
    vector vec = {0};

    int i;
    for (i = 0; i < 20; ++i)
    {
        vec_data new_data = {0};
        new_data.i = i;
        ck_assert_int_eq(vec_push_back(&vec, new_data), 0);
    }

    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    for (i = 0; i < 20; ++i)
    {
        vec_data* data = vec_val_at(&vec, i);
        ck_assert_ptr_ne(data, NULL);
        ck_assert_int_eq(data->i, expected[i]);
    }

    ck_assert_ptr_eq(vec_val_at(&vec, 20), NULL);

    ck_assert_uint_eq(vec.capacity, VEC_INIT_CAPACITY*2);
    ck_assert_uint_eq(vec.size, 20);

    vec_destroy(&vec);
}
END_TEST

Suite* vec_suite(void)
{
    Suite* s;
    TCase* tc_core;
    s = suite_create("Vector");
    
    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_vec_clear);
    tcase_add_test(tc_core, test_vec_erase_elem);
    tcase_add_test(tc_core, test_vec_init);
    tcase_add_test(tc_core, test_vec_pop_back);
    tcase_add_test(tc_core, test_vec_push_back);
    tcase_add_test(tc_core, test_vec_reserve);
    tcase_add_test(tc_core, test_vec_swap_elem);
    tcase_add_test(tc_core, test_vec_val_at);

    
    
    
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = vec_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
} 
