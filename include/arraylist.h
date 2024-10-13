#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

typedef struct { 
  size_t capacity;
  size_t size;
  void** backing_array;
} ArrayList;

#define SUCCESS 1
#define FAILURE -1

ArrayList *create_arraylist(size_t);
int_fast8_t destroy_arraylist(ArrayList*);
int_fast8_t insert_arraylist(ArrayList*, void*, size_t);
int_fast8_t append_arraylist(ArrayList*, void*);
void *remove_arraylist(ArrayList*, size_t);
void *pop_arraylist(ArrayList*);
int_fast8_t resize_arraylist(ArrayList*);

#endif 
