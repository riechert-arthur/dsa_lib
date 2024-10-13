#include "arraylist_test.h"

ArrayList *generate_test_arraylist(size_t capacity) {

  ArrayList *arr = create_arraylist(capacity);

  for (size_t i = 0; i < capacity - 1; ++i) {
    int *temp = malloc(sizeof(int));
    if (temp == NULL) {
      perror("Failed to allocate memory");
      exit(EXIT_FAILURE);
    }
    *temp = i;
    arr->backing_array[i] = temp;
  }

  arr->size = capacity - 1;

  return arr;
}

void free_arraylist_data(ArrayList *arr) {
  if (arr == NULL) {
    return;
  }
  for (size_t i = 0; i < arr->size; ++i) {
    free(arr->backing_array[i]);
  }
}

void test_create_arraylist(void) {
 
  size_t capacity = 1;
  size_t size = 0; 

  ArrayList *arr = create_arraylist(capacity);
  assert(arr != NULL);
  assert(arr->backing_array != NULL);
  assert(arr->capacity == capacity);
  assert(arr->size == size);

  free(arr->backing_array);
  free(arr);
  arr = NULL;

  printf("Passed Test: CREATE ARRAYLIST\n");

}

void test_destroy_arraylist(void) {

  size_t capacity = 1;

  ArrayList *arr = create_arraylist(capacity);
  destroy_arraylist(arr);
  arr = NULL;


  printf("Passed Test: DESTROY ARRAYLIST\n");

}

void test_create_arraylist_cap_0(void) {

  size_t capacity = 0;

  ArrayList *arr = create_arraylist(capacity);
  assert(arr == NULL);
  assert(errno == EINVAL);
  
  printf("Passed Test: CREATE ARRAYLIST CAP 0\n");

}

void test_insert_arraylist(void) {

  int test_idx = 4;
  int test_value = 100;
  size_t capacity = 10;

  ArrayList* arr = generate_test_arraylist(capacity);


  insert_arraylist(arr, &test_value, test_idx);
  assert(arr->backing_array[test_idx] == &test_value);

  destroy_arraylist(arr);
  arr = NULL;

  printf("Passed Test: INSERT ARRAYLIST\n");

}

void test_append_arraylist(void) {

  int test_value = 100;
  size_t capacity = 10;

  ArrayList* arr = generate_test_arraylist(capacity);

  append_arraylist(arr, &test_value);
  assert(arr->backing_array[arr->size - 1] == &test_value);

  destroy_arraylist(arr);
  arr = NULL;

  printf("Passed Test: APPEND ARRAYLIST\n");

}

void test_resize_arraylist_arr_null(void) {
    int_fast8_t result = resize_arraylist(NULL);

    assert(result == FAILURE);

    printf("Passed Test: RESIZE ARRAYLIST NULL ARRAYLIST\n");
}

void test_insert_arraylist_value_null(void) {

  void *test_value = NULL;
    size_t capacity = 10;
    size_t test_idx = 4;

    ArrayList* arr = generate_test_arraylist(capacity);
    int_fast8_t result = insert_arraylist(arr, test_value, test_idx);

    assert(result == FAILURE);

    free_arraylist_data(arr);
    destroy_arraylist(arr);

    printf("Passed Test: INSERT ARRAYLIST NULL VALUE\n");

}


void test_insert_arraylist_over_cap(void) {

  int test_value = 100;
  size_t capacity = 5;

  ArrayList* arr = generate_test_arraylist(capacity);

  int *new_value = malloc(sizeof(int));
  *new_value = test_value;
  append_arraylist(arr, new_value);

  int *another_value = malloc(sizeof(int));
  *another_value = 200;
  int_fast8_t result = insert_arraylist(arr, another_value, arr->size);

  assert(result == SUCCESS);
  assert(arr->capacity >= capacity * 2);
  assert(arr->backing_array[arr->size - 1] == another_value);

  free_arraylist_data(arr);
  destroy_arraylist(arr);

  printf("Passed Test: INSERT ARRAYLIST OVER CAPACITY\n");

}



void test_append_arraylist_value_null(void) {

  void *test_value = NULL;
  size_t capacity = 10;

  ArrayList* arr = generate_test_arraylist(capacity);
  int_fast8_t result = append_arraylist(arr, test_value);

  assert(result == FAILURE);

  free_arraylist_data(arr);
  destroy_arraylist(arr);

  printf("Passed Test: APPEND ARRAYLIST NULL VALUE\n");

}

void test_append_arraylist_over_cap(void) {

  int test_value = 100;
  size_t capacity = 5;

  ArrayList* arr = generate_test_arraylist(capacity);

  int *new_value = malloc(sizeof(int));
  *new_value = test_value;
  append_arraylist(arr, new_value);

  int *another_value = malloc(sizeof(int));
  *another_value = 200;
  int_fast8_t result = append_arraylist(arr, another_value);

  assert(result == SUCCESS);
  assert(arr->capacity >= capacity * 2);
  assert(arr->backing_array[arr->size - 1] == another_value);

  free_arraylist_data(arr);
  destroy_arraylist(arr);

  printf("Passed Test: APPEND ARRAYLIST OVER CAPACITY\n");

}

void test_remove_arraylist(void) {

  size_t capacity = 5;
  ArrayList* arr = generate_test_arraylist(capacity);

  size_t remove_idx = 2;
  void* removed_value = remove_arraylist(arr, remove_idx);

  assert(removed_value != NULL);
  assert(*(int*)removed_value == (int)remove_idx);

  free(removed_value);
  assert(arr->size == capacity - 2);

  free_arraylist_data(arr);
  destroy_arraylist(arr);

  printf("Passed Test: REMOVE ARRAYLIST\n");

}

void test_remove_arraylist_invalid_index(void) {

  size_t capacity = 5;
  ArrayList* arr = generate_test_arraylist(capacity);

  size_t invalid_index = arr->size + 10;
  void* removed_value = remove_arraylist(arr, invalid_index);

  assert(removed_value == NULL);
  assert(arr->size == capacity - 1);

  free_arraylist_data(arr);
  destroy_arraylist(arr);

  printf("Passed Test: REMOVE ARRAYLIST INVALID INDEX\n");

}

void test_pop_arraylist(void) {

  size_t capacity = 5;
  ArrayList* arr = generate_test_arraylist(capacity);

  void* popped_value = pop_arraylist(arr);

  assert(popped_value != NULL);
  assert(*(int*)popped_value == (int)(capacity - 2));

  free(popped_value);
  assert(arr->size == capacity - 2);

  free_arraylist_data(arr);
  destroy_arraylist(arr);

  printf("Passed Test: POP ARRAYLIST\n");

}


void test_insert_arraylist_invalid_index(void) {

  int test_value = 100;
  size_t capacity = 5;

  ArrayList* arr = generate_test_arraylist(capacity);

  size_t invalid_index = arr->size + 10;
  int_fast8_t result = insert_arraylist(arr, &test_value, invalid_index);

  assert(result == FAILURE);
  assert(arr->size == capacity - 1);

  free_arraylist_data(arr);
  destroy_arraylist(arr);

  printf("Passed Test: INSERT ARRAYLIST INVALID INDEX\n");

}

void test_pop_arraylist_empty(void) {

  size_t capacity = 5;
  ArrayList* arr = create_arraylist(capacity);

  void* popped_value = pop_arraylist(arr);

  assert(popped_value == NULL);
  assert(arr->size == 0);

  destroy_arraylist(arr);

  printf("Passed Test: POP ARRAYLIST EMPTY\n");

}

void test_destroy_arraylist_arr_null(void) {

  int_fast8_t result = destroy_arraylist(NULL);

  assert(result == SUCCESS);

  printf("Passed Test: DESTROY ARRAYLIST NULL ARRAYLIST\n");

}


void test_resize_arraylist(void) {

  size_t initial_capacity = 2;
  ArrayList* arr = create_arraylist(initial_capacity);
  assert(arr != NULL);
  assert(arr->capacity == initial_capacity);
  assert(arr->size == 0);

  int *val1 = malloc(sizeof(int));
  int *val2 = malloc(sizeof(int));
  *val1 = 10;
  *val2 = 20;
  assert(append_arraylist(arr, val1) == SUCCESS);
  assert(append_arraylist(arr, val2) == SUCCESS);
  assert(arr->size == 2);
  assert(arr->capacity == initial_capacity);

  int *val3 = malloc(sizeof(int));
  *val3 = 30;
  assert(append_arraylist(arr, val3) == SUCCESS);
  assert(arr->size == 3);
  assert(arr->capacity == initial_capacity * 2);  // Should have resized

  free(val1);
  free(val2);
  free(val3);
  destroy_arraylist(arr);

  printf("Passed Test: RESIZE_ARRAYLIST\n");

}

int main(int argc, char *argv[]) {

  test_create_arraylist();
  test_destroy_arraylist();
  test_create_arraylist_cap_0();
  test_destroy_arraylist_arr_null();
  test_insert_arraylist();
  test_insert_arraylist_value_null();
  test_insert_arraylist_invalid_index();
  test_insert_arraylist_over_cap();
  test_append_arraylist();
  test_append_arraylist_value_null();
  test_append_arraylist_over_cap();
  test_remove_arraylist();
  test_remove_arraylist_invalid_index();
  test_pop_arraylist();
  test_pop_arraylist_empty();
  test_resize_arraylist();
  test_resize_arraylist_arr_null();

  printf("All tests passed successfully!\n");
  return 0;

}

