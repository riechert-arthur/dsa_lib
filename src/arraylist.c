#include "arraylist.h"

ArrayList *create_arraylist(size_t capacity) {

  if (capacity == 0) {
    errno = EINVAL;
    return NULL;
  }

  ArrayList *arr;
  
  if (!(arr = (ArrayList*) malloc(sizeof(ArrayList)))) {
    fprintf(stderr, "Memory allocation failed for arraylist struct: %s\n", strerror(errno)); 
    return NULL; 
  }

  if (!(arr->backing_array = (void**) calloc(capacity, sizeof(void*)))) {
    fprintf(stderr, "Memory allocation failed for arraylist backing array: %s\n", strerror(errno));
    free(arr);
    return NULL;
  }

  arr->capacity = capacity;
  arr->size = 0;

  return arr; 
}

int_fast8_t insert_arraylist(ArrayList *arr, void *value, size_t idx) {

  if (arr == NULL || value == NULL) {
    errno = EINVAL;
    fprintf(stderr, "Passed a null pointer to insert function: %s\n", strerror(errno));
    return FAILURE;
  }

  if (idx > arr->size) {
    errno = EINVAL; 
    fprintf(stderr, "Passed an out of bounds index to insert function: %s\n", strerror(errno));
    return FAILURE;
  }

  if (arr->size == arr->capacity) {
    if (resize_arraylist(arr) < 0) {
      fprintf(stderr, "Failure during a resize: %s\n", strerror(errno));
      return FAILURE;
    }
  }

  for (size_t i = arr->size; i > idx; --i) {
    arr->backing_array[i] = arr->backing_array[i - 1];
  }

  arr->backing_array[idx] = value;
  ++arr->size;

  return SUCCESS;
}

int_fast8_t append_arraylist(ArrayList *arr, void *value) {
  
  if (arr == NULL || value == NULL) {
    errno = EINVAL;
    fprintf(stderr, "Passed a null pointer to append function: %s\n", strerror(errno));
    return FAILURE;
  }

  if (arr->size == arr->capacity) {
    if (resize_arraylist(arr) < 0) {
      fprintf(stderr, "Failure during a resize: %s\n", strerror(errno));
      return FAILURE;
    }
  }

  arr->backing_array[arr->size] = value;
  ++arr->size;

  return SUCCESS;
}

void *remove_arraylist(ArrayList* arr, size_t idx) {
  if (arr == NULL) {
    errno = EINVAL;
    fprintf(stderr, "Passed a null pointer to remove function: %s\n", strerror(errno));
    return NULL;
  }

  if (idx >= arr->size) {
    errno = EINVAL;
    fprintf(stderr, "Passed an out of bounds index to remove function: %s\n", strerror(errno));
    return NULL;
  }

  void *temp = arr->backing_array[idx];
  for (size_t i = idx; i < arr->size - 1; ++i) {
    arr->backing_array[i] = arr->backing_array[i + 1];
  }
  arr->backing_array[arr->size - 1] = NULL;
  --arr->size;

  return temp;
}

void *pop_arraylist(ArrayList* arr) {
  if (arr == NULL) {
    errno = EINVAL;
    fprintf(stderr, "Passed a null pointer to pop function: %s\n", strerror(errno));
    return NULL;
  }

  if (arr->size == 0) {
    errno = EINVAL;
    fprintf(stderr, "Cannot pop from an empty arraylist: %s\n", strerror(errno));
    return NULL;
  }

  void *temp = arr->backing_array[arr->size - 1];
  arr->backing_array[arr->size - 1] = NULL;
  --arr->size;

  return temp;
}

int_fast8_t destroy_arraylist(ArrayList *arr) {

  if (arr != NULL) {
    free(arr->backing_array);
  }
  free(arr);

  return SUCCESS;
}

int_fast8_t resize_arraylist(ArrayList *arr) {
 
  if (arr == NULL) {
    errno = EINVAL;
    fprintf(stderr, "Passed a null pointer to resize function: %s\n", strerror(errno));
    return FAILURE;
  }

  void** temp; 
  if (!(temp = (void**) realloc(arr->backing_array, 2 * arr->capacity * sizeof(void*)))) {
    fprintf(stderr, "Memory allocation failed for arraylist backing array: %s\n", strerror(errno));
    return FAILURE; 
  }

  arr->backing_array = temp;
  arr->capacity *= 2;

  return SUCCESS;
}
