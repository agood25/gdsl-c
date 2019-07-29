#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "ds_def.h"

START_TEST(test_vec_clear)
{
    vector vec = {0};
    

    int i;
    for (i = 0; i < 10; ++i)
    {
        vec_data new_data = {0};
        new_data.i = i;
        vec_push_back(&vec, new_data);
    }

    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (i = 0; i < 10; ++i)
    {
        ck_assert_int_eq(vec.values[i].i, expected[i]);
    }

    vec_clear(&vec);

    ck_assert_int_eq(vec.size, 0);
    ck_assert_int_eq(vec.capacity, VEC_INIT_CAPACITY);

    ck_assert_int_eq(vec.values[0].i, 0);
    free(vec.values);
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

    free(vec.values);
    free(vec2.values);
}
END_TEST

Suite* vec_suite(void)
{
    Suite* s;
    TCase* tc_core;
    s = suite_create("Vector");
    
    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_vec_init);
    tcase_add_test(tc_core, test_vec_clear);
    
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
