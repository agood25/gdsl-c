#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "ds_def.h"

START_TEST(test_stack_clear)
{
    stack s = {0};

    ck_assert_int_eq(stack_clear(&s), 0);

    int i;
    for (i = 0; i < 10; ++i)
    {
        stack_data new_data = {0};
        new_data.i = i;
        ck_assert_int_eq(stack_push(&s, new_data), 0);
    }

    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (i = 0; i < 10; ++i)
    {
        ck_assert_int_eq(s.values[i].i, expected[i]);
    }

    ck_assert_int_eq(stack_clear(&s), 0);

    ck_assert_uint_eq(s.size, 0);
    ck_assert_uint_eq(s.capacity, STACK_INIT_CAPACITY);

    ck_assert_int_eq(s.values[0].i, 0);
    stack_destroy(&s);
}
END_TEST

START_TEST(test_stack_init)
{
    stack s = {0};
    ck_assert_ptr_eq(s.values, NULL);

    ck_assert_int_eq(stack_init(&s, 0), 0);
    ck_assert_ptr_ne(s.values, NULL);
    ck_assert_uint_eq(s.capacity, STACK_INIT_CAPACITY);
    ck_assert_uint_eq(s.size, 0);

    stack s2 = {0};

    ck_assert_int_eq(stack_init(&s2, 1235), 0);
    ck_assert_uint_eq(s2.capacity, 1235);
    ck_assert_uint_eq(s2.size, 0);

    stack_destroy(&s);
    stack_destroy(&s2);
}
END_TEST

START_TEST(test_stack_pop)
{
    stack s = {0};

    ck_assert_int_eq(stack_pop(&s), -1);
    
    int i;
    for (i = 0; i < 20; ++i)
    {
        stack_data new_data = {0};
        new_data.i = i;
        ck_assert_int_eq(stack_push(&s, new_data), 0);
    }

    ck_assert_int_eq(stack_pop(&s), 0);
    ck_assert_int_eq(stack_pop(&s), 0);
    ck_assert_int_eq(stack_pop(&s), 0);
    ck_assert_int_eq(stack_pop(&s), 0);

    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    for (i = 0; i < 16; ++i)
    {
        ck_assert_int_eq(s.values[i].i, expected[i]);
    }

    ck_assert_uint_eq(s.size, 16);

    stack_destroy(&s);
}
END_TEST

START_TEST(test_stack_push)
{
    stack s = {0};
    
    int i;
    for (i = 0; i < 20; ++i)
    {
        stack_data new_data = {0};
        new_data.i = i;
        ck_assert_int_eq(stack_push(&s, new_data), 0);
    }

    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    for (i = 0; i < 20; ++i)
    {
        ck_assert_int_eq(s.values[i].i, expected[i]);
    }

    ck_assert_uint_eq(s.size, 20);

    stack_destroy(&s);
}
END_TEST

START_TEST(test_stack_reserve)
{
    stack s = {0};

    ck_assert_int_eq(stack_reserve(&s, 20), 0);

    ck_assert_uint_eq(s.capacity, 20);

    int i;
    for (i = 0; i < 20; ++i)
    {
        stack_data new_data = {0};
        new_data.i = i;
        ck_assert_int_eq(stack_push(&s, new_data), 0);
    }

    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    for (i = 0; i < 20; ++i)
    {
        ck_assert_int_eq(s.values[i].i, expected[i]);
    }

    ck_assert_uint_eq(s.size, 20);

    stack_destroy(&s);
}
END_TEST

START_TEST(test_stack_top)
{
    stack s = {0};
    
    int i;
    for (i = 0; i < 20; ++i)
    {
        stack_data new_data = {0};
        new_data.i = i;
        ck_assert_int_eq(stack_push(&s, new_data), 0);
    }

    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    for (i = 19; i > -1; --i)
    {
        ck_assert_int_eq(stack_top(&s)->i, expected[i]);
        ck_assert_int_eq(stack_pop(&s), 0);
    }

    ck_assert_uint_eq(s.size, 0);

    stack_destroy(&s);
}
END_TEST

Suite* stack_suite(void)
{
    Suite* s;
    TCase* tc_core;
    s = suite_create("stack");
    
    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_stack_clear);
    tcase_add_test(tc_core, test_stack_init);
    tcase_add_test(tc_core, test_stack_pop);
    tcase_add_test(tc_core, test_stack_push);
    tcase_add_test(tc_core, test_stack_reserve);
    tcase_add_test(tc_core, test_stack_top);
    
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = stack_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
} 
