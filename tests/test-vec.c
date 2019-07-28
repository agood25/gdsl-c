#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

START_TEST(test_vec_init)
{
    vector vec = {0};

    ck_assert_int_eq(vec_init(&vec, 10), 0);
    ck_assert_uint_eq(vec.capacity, 10);
    ck_assert_uint_eq(vec.size, 0);

    vector vec2 = {0};

    ck_assert_int_eq(vec_init(&vec2, 1235), 0);
    ck_assert_uint_eq(vec2.capacity, 1235);
    ck_assert_uint_eq(vec2.size, 0);

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

// int main()
// {
//     vector vec = {0};
//     vec_data var = {0};
//     var.c = "Hello World";

//     vec_push_back(&vec, &var);

//     size_t i;
//     for (i = 0; i < vec.size; ++i)
//     {
//         printf("%s\n",  vec.values[i].c);
//     }

//     return 0;
// }