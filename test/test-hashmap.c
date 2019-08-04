#include <stdbool.h>
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"
#include "gdsl_def.h"

char* get_key_from_uint32(uint32_t uint32_key)
{
    uint32_t MAX_UINT32_STR_LEN = 10;
    char* key = (char*) malloc(MAX_UINT32_STR_LEN + 1);
    if(NULL == key) { return NULL; }

    snprintf(key, MAX_UINT32_STR_LEN+1, "%u", uint32_key);

    return key;
}

START_TEST(test_hm_clear)
{
    hashmap hm = {0};

    uint32_t i;
    for (i = 0; i < 10; ++i)
    {
        hashmap_data new_data = {0};
        new_data.i = i;
        char* key = get_key_from_uint32(i);
        if (NULL == key) { ck_assert(false); }

        hashmap_key_val kv = {0};
        kv.value = new_data;
        kv.key = key;

        ck_assert_int_eq(hashmap_insert(&hm, kv), 0);
    }

    ck_assert_int_eq(hashmap_clear(&hm), 0);

    ck_assert_int_eq(hm.size, 0);
    ck_assert_int_eq(hm.capacity, HASHMAP_INIT_CAPACITY);
}
END_TEST

// START_TEST(test_hm_erase_elem)
// {
//     hashmap hm = {0};
    
//     int i;
//     for (i = 0; i < 20; ++i)
//     {
//         hashmap_data new_data = {0};
//         new_data.i = i;
//         ck_assert_int_eq(hm_push_back(&hm, new_data), 0);
//     }

//     ck_assert_int_eq(hm_erase_elem(&hm, 5), 0);
//     ck_assert_int_eq(hm_erase_elem(&hm, 7), 0);
//     ck_assert_int_eq(hm_erase_elem(&hm, 14), 0);

//     ck_assert_int_eq(hm_erase_elem(&hm, 20), -1);

//     int expected[] = {0, 1, 2, 3, 4, 6, 7, 9, 10, 11, 12, 13, 14, 15, 17, 18, 19};

//     for (i = 0; i < 17; ++i)
//     {
//         ck_assert_int_eq(hm.values[i].i, expected[i]);
//     }

//     ck_assert_uint_eq(hm.size, 17);

//     hm_destroy(&hm);
// }
// END_TEST

// START_TEST(test_hm_init)
// {
//     hashmap hm = {0};
//     ck_assert_ptr_eq(hm.values, NULL);

//     ck_assert_int_eq(hm_init(&hm, 0), 0);
//     ck_assert_ptr_ne(hm.values, NULL);
//     ck_assert_uint_eq(hm.capacity, hm_INIT_CAPACITY);
//     ck_assert_uint_eq(hm.size, 0);

//     hashmap hm2 = {0};

//     ck_assert_int_eq(hm_init(&hm2, 1235), 0);
//     ck_assert_uint_eq(hm2.capacity, 1235);
//     ck_assert_uint_eq(hm2.size, 0);

//     hm_destroy(&hm);
//     hm_destroy(&hm2);
// }
// END_TEST

// START_TEST(test_hm_pop_back)
// {
//     hashmap hm = {0};

//     ck_assert_int_eq(hm_pop_back(&hm), -1);
    
//     int i;
//     for (i = 0; i < 20; ++i)
//     {
//         hashmap_data new_data = {0};
//         new_data.i = i;
//         ck_assert_int_eq(hm_push_back(&hm, new_data), 0);
//     }

//     ck_assert_int_eq(hm_pop_back(&hm), 0);
//     ck_assert_int_eq(hm_pop_back(&hm), 0);
//     ck_assert_int_eq(hm_pop_back(&hm), 0);
//     ck_assert_int_eq(hm_pop_back(&hm), 0);

//     int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

//     for (i = 0; i < 16; ++i)
//     {
//         ck_assert_int_eq(hm.values[i].i, expected[i]);
//     }

//     ck_assert_uint_eq(hm.size, 16);

//     hm_destroy(&hm);
// }
// END_TEST

// START_TEST(test_hm_push_back)
// {
//     hashmap hm = {0};
    
//     int i;
//     for (i = 0; i < 20; ++i)
//     {
//         hashmap_data new_data = {0};
//         new_data.i = i;
//         ck_assert_int_eq(hm_push_back(&hm, new_data), 0);
//     }

//     int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

//     for (i = 0; i < 20; ++i)
//     {
//         ck_assert_int_eq(hm.values[i].i, expected[i]);
//     }

//     ck_assert_uint_eq(hm.size, 20);

//     hm_destroy(&hm);
// }
// END_TEST

// START_TEST(test_hm_reserve)
// {
//     hashmap hm = {0};

//     ck_assert_int_eq(hm_reserve(&hm, 20), 0);

//     ck_assert_uint_eq(hm.capacity, 20);

//     int i;
//     for (i = 0; i < 20; ++i)
//     {
//         hashmap_data new_data = {0};
//         new_data.i = i;
//         ck_assert_int_eq(hm_push_back(&hm, new_data), 0);
//     }

//     int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

//     for (i = 0; i < 20; ++i)
//     {
//         ck_assert_int_eq(hm.values[i].i, expected[i]);
//     }

//     ck_assert_uint_eq(hm.size, 20);

//     hm_destroy(&hm);
// }
// END_TEST

// START_TEST(test_hm_swap_elem)
// {
//     hashmap hm = {0};

//     int i;
//     for (i = 0; i < 20; ++i)
//     {
//         hashmap_data new_data = {0};
//         new_data.i = i;
//         ck_assert_int_eq(hm_push_back(&hm, new_data), 0);
//     }

//     int expected[] = {11, 1, 2, 16, 4, 19, 6, 7, 8, 9, 10, 0, 12, 13, 14, 15, 3, 17, 18, 5};

//     ck_assert_int_eq(hm_swap_elem(&hm, 0, 11), 0);
//     ck_assert_int_eq(hm_swap_elem(&hm, 3, 16), 0);
//     ck_assert_int_eq(hm_swap_elem(&hm, 5, 19), 0);
    
//     ck_assert_int_eq(hm_swap_elem(&hm, 20, 2), -1);

//     for (i = 0; i < 20; ++i)
//     {
//         ck_assert_int_eq(hm.values[i].i, expected[i]);
//     }

//     ck_assert_uint_eq(hm.capacity, hm_INIT_CAPACITY*2);
//     ck_assert_uint_eq(hm.size, 20);

//     hm_destroy(&hm);
// }
// END_TEST

// START_TEST(test_hm_val_at)
// {
//     hashmap hm = {0};

//     int i;
//     for (i = 0; i < 20; ++i)
//     {
//         hashmap_data new_data = {0};
//         new_data.i = i;
//         ck_assert_int_eq(hm_push_back(&hm, new_data), 0);
//     }

//     int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

//     for (i = 0; i < 20; ++i)
//     {
//         hashmap_data* data = hm_val_at(&hm, i);
//         ck_assert_ptr_ne(data, NULL);
//         ck_assert_int_eq(data->i, expected[i]);
//     }

//     ck_assert_ptr_eq(hm_val_at(&hm, 20), NULL);

//     ck_assert_uint_eq(hm.capacity, hm_INIT_CAPACITY*2);
//     ck_assert_uint_eq(hm.size, 20);

//     hm_destroy(&hm);
// }
// END_TEST

Suite* hm_suite(void)
{
    Suite* s;
    TCase* tc_core;
    s = suite_create("hashmap");
    
    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_hm_clear);
    // tcase_add_test(tc_core, test_hm_erase_elem);
    // tcase_add_test(tc_core, test_hm_init);
    // tcase_add_test(tc_core, test_hm_pop_back);
    // tcase_add_test(tc_core, test_hm_push_back);
    // tcase_add_test(tc_core, test_hm_reserve);
    // tcase_add_test(tc_core, test_hm_swap_elem);
    // tcase_add_test(tc_core, test_hm_val_at);

    
    
    
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    hashmap hm = {0};

    uint32_t i;
    for (i = 0; i < 10; ++i)
    {
        hashmap_data new_data = {0};
        new_data.i = i;
        char* key = get_key_from_uint32(i);

        hashmap_key_val kv = {0};
        kv.value = new_data;
        kv.key = key;
        hashmap_insert(&hm, kv);
    }
    
    hashmap_clear(&hm);

    // int number_failed;
    // Suite* s;
    // SRunner* sr;

    // s = hm_suite();
    // sr = srunner_create(s);

    // srunner_run_all(sr, CK_NORMAL);
    // number_failed = srunner_ntests_failed(sr);
    // srunner_free(sr);
    // return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
} 
