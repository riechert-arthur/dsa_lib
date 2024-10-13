#ifndef ARRAYLIST_TEST_H
#define ARRAYLIST_TEST_H

#include "arraylist.h"

#include <assert.h>

ArrayList *generate_test_arraylist(size_t capacity);
void free_arraylist_data(ArrayList *arr);

void test_create_arraylist(void);
void test_destroy_arraylist(void);
void test_create_arraylist_cap_0(void);
void test_destroy_arraylist_arr_null(void);
void test_insert_arraylist(void);
void test_insert_arraylist_value_null(void);
void test_insert_arraylist_invalid_index(void);
void test_insert_arraylist_over_cap(void);
void test_append_arraylist(void);
void test_append_arraylist_value_null(void);
void test_append_arraylist_over_cap(void);
void test_remove_arraylist(void);
void test_remove_arraylist_invalid_index(void);
void test_pop_arraylist(void);
void test_pop_arraylist_empty(void);
void test_resize_arraylist(void);
void test_resize_arraylist_arr_null(void);

#endif
